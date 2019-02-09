#include "pch/stdafx.h"
#include "squawk/SquawkGenerator.h"
#include "helper/HelperFunctions.h"
#include "flightplan/StoredFlightplan.h"
#include "api/ApiException.h"
#include "api/ApiNotFoundException.h"
#include "api/ApiInterface.h"
#include "controller/ControllerPosition.h"
#include "flightplan/StoredFlightplanCollection.h"
#include "squawk/SquawkAssignment.h"
#include "controller/ActiveCallsignCollection.h"
#include "euroscope/EuroScopeCFlightPlanInterface.h"
#include "euroscope/EuroScopeCRadarTargetInterface.h"
#include "squawk/ApiSquawkAllocation.h"
#include "squawk/ApiSquawkAllocationHandler.h"

using UKControllerPlugin::Api::ApiInterface;
using UKControllerPlugin::Euroscope::EuroScopeCFlightPlanInterface;
using UKControllerPlugin::Euroscope::EuroScopeCRadarTargetInterface;
using UKControllerPlugin::TaskManager::TaskRunnerInterface;
using UKControllerPlugin::HelperFunctions;
using UKControllerPlugin::Flightplan::StoredFlightplanCollection;
using UKControllerPlugin::Flightplan::StoredFlightplan;
using UKControllerPlugin::Squawk::SquawkAssignment;
using UKControllerPlugin::Api::ApiException;
using UKControllerPlugin::Api::ApiNotFoundException;
using UKControllerPlugin::Controller::ControllerPosition;
using UKControllerPlugin::Squawk::ApiSquawkAllocation;
using UKControllerPlugin::Squawk::ApiSquawkAllocationHandler;

namespace UKControllerPlugin {
    namespace Squawk {

        SquawkGenerator::SquawkGenerator(
            const ApiInterface & api,
            TaskRunnerInterface * const taskRunner,
            const UKControllerPlugin::Squawk::SquawkAssignment & assignmentRules,
            const UKControllerPlugin::Controller::ActiveCallsignCollection & activeCallsigns,
            const UKControllerPlugin::Flightplan::StoredFlightplanCollection & storedFlightplans,
            const std::shared_ptr<ApiSquawkAllocationHandler> allocations
        )
            : api(api), taskRunner(taskRunner), assignmentRules(assignmentRules), activeCallsigns(activeCallsigns),
            storedFlightplans(storedFlightplans), allocations(allocations)
        {
        }

        /*
            Assigns circuit squawks where appropriate.
        */
        bool SquawkGenerator::AssignCircuitSquawkForAircraft(
            EuroScopeCFlightPlanInterface & flightplan,
            EuroScopeCRadarTargetInterface & radarTarget
        ) const
        {
            if (this->assignmentRules.disabled || !assignmentRules.CircuitAssignmentNeeded(flightplan, radarTarget)) {
                return false;
            }

            LogInfo("Assigned circuit squawk to " + flightplan.GetCallsign());
            flightplan.SetSquawk("7010");
            return true;
        }

        /*
            Forces a squawk to be assigned for the given aircraft
        */
        bool SquawkGenerator::ForceGeneralSquawkForAircraft(
            EuroScopeCFlightPlanInterface & flightplan,
            EuroScopeCRadarTargetInterface & radarTarget
        ) {
            if (this->assignmentRules.disabled) {
                return false;
            }

            if (!this->assignmentRules.ForceAssignmentAllowed(flightplan)) {
                return false;
            }

            if (!this->StartSquawkUpdate(flightplan)) {
                return false;
            }

            // Request squawk update - copy some flightplan data locally incase it goes away.
            std::string callsign = flightplan.GetCallsign();
            std::string origin = flightplan.GetOrigin();
            std::string destination = flightplan.GetDestination();

            this->taskRunner->QueueAsynchronousTask([this, callsign, origin, destination]() {
                this->CreateGeneralSquawkAssignment(callsign, origin, destination);
                this->EndSquawkUpdate(callsign);
            });
            return true;
        }

        /*
            Forces the a local squawk update for the given aircraft.
        */
        bool SquawkGenerator::ForceLocalSquawkForAircraft(
            EuroScopeCFlightPlanInterface & flightplan,
            EuroScopeCRadarTargetInterface & radarTarget
        ) {
            if (this->assignmentRules.disabled) {
                return false;
            }

            if (!this->assignmentRules.ForceAssignmentAllowed(flightplan)) {
                return false;
            }

            if (!this->StartSquawkUpdate(flightplan)) {
                return false;
            }

            // Get some data incase the flightplan goes away
            std::string callsign = flightplan.GetCallsign();
            std::string unit = this->activeCallsigns.GetUserCallsign().GetNormalisedPosition().GetUnit();
            std::string flightRules = flightplan.GetFlightRules();

            // Make the request
            this->taskRunner->QueueAsynchronousTask([this, callsign, unit, flightRules]() {
                this->CreateLocalSquawkAssignment(callsign, unit, flightRules);
                this->EndSquawkUpdate(callsign);
            });
            return true;
        }

        /*
            If an aircraft has a previously assigned squawk but it's gone somewhere (e.g. disconnect), reassign it.
        */
        bool SquawkGenerator::ReassignPreviousSquawkToAircraft(
            EuroScopeCFlightPlanInterface & flightplan,
            EuroScopeCRadarTargetInterface & radarTarget
        ) const {
            if (this->assignmentRules.disabled) {
                return false;
            }

            if (!this->assignmentRules.PreviousSquawkNeedsReassignment(flightplan, radarTarget)) {
                return false;
            }

            flightplan.SetSquawk(
                this->storedFlightplans.GetFlightplanForCallsign(
                    flightplan.GetCallsign()
                ).GetPreviouslyAssignedSquawk()
            );

            return true;
        }

        /*
            Assign a general squawk (not tied to a particular unit) to a given aircraft. Do this out of sync
            so that we don't hold the plugin up waiting for HTTP requests.
        */
        bool SquawkGenerator::RequestGeneralSquawkForAircraft(
            EuroScopeCFlightPlanInterface & flightplan,
            EuroScopeCRadarTargetInterface & radarTarget
        ) {
            if (this->assignmentRules.disabled) {
                return false;
            }

            if (!this->assignmentRules.GeneralAssignmentNeeded(flightplan, radarTarget)) {
                return false;
            }

            if (!this->StartSquawkUpdate(flightplan)) {
                return false;
            }

            // Request squawk update - copy some flightplan data locally incase it goes away.
            std::string callsign = flightplan.GetCallsign();
            std::string origin = flightplan.GetOrigin();
            std::string destination = flightplan.GetDestination();

            // Force update required.
            if (this->assignmentRules.ForceAssignmentNeeded(flightplan)) {
                this->taskRunner->QueueAsynchronousTask([this, callsign, origin, destination]() {
                    this->CreateGeneralSquawkAssignment(callsign, origin, destination);
                    this->EndSquawkUpdate(callsign);
                });
                return true;
            }

            // Search for an existing assignment, create if necessary
            this->taskRunner->QueueAsynchronousTask([this, callsign, origin, destination]() {
                if (!this->GetSquawkAssignment(callsign)) {
                    this->CreateGeneralSquawkAssignment(callsign, origin, destination);
                }
                this->EndSquawkUpdate(callsign);
            });
            return true;
        }

        /*
            Assign a local squawk (to a particular unit) to a given aircraft. Do this out of sync
            so that we don't hold the plugin up waiting for HTTP requests.
        */
        bool SquawkGenerator::RequestLocalSquawkForAircraft(
            EuroScopeCFlightPlanInterface & flightplan,
            EuroScopeCRadarTargetInterface & radarTarget
        ) {
            if (this->assignmentRules.disabled) {
                return false;
            }

            if (!this->assignmentRules.LocalAssignmentNeeded(flightplan, radarTarget)) {
                return false;
            }

            if (!this->StartSquawkUpdate(flightplan)) {
                return false;
            }

            // Get the variables out now, just incase anything goes away.
            std::string callsign = flightplan.GetCallsign();
            std::string unit = this->activeCallsigns.GetUserCallsign().GetNormalisedPosition().GetUnit();
            std::string flightRules = flightplan.GetFlightRules();

            // Check for existing squawk assignment, create if necessary
            this->taskRunner->QueueAsynchronousTask([this, callsign, unit, flightRules]() {
                if (!this->GetSquawkAssignment(callsign)) {
                    this->CreateLocalSquawkAssignment(callsign, unit, flightRules);
                }
                this->EndSquawkUpdate(callsign);
            });
            return true;
        }

        /*
            Checks for a squawk assignment on the API for the given aircraft. Returns true after assigning the squawk
            if one is found, false otherwise.

            THIS FUNCTION SHOULD ONLY BE USED ON AN ASYNCHRONOUS THREAD.
        */
        bool SquawkGenerator::GetSquawkAssignment(std::string callsign) const
        {
            // Assign the squawk to our aircraft
            try {
                ApiSquawkAllocation allocation = this->api.GetAssignedSquawk(callsign);
                this->allocations->AddAllocationToQueue(allocation);
                LogInfo("Found existing API squawk allocation of " + allocation.squawk + " for " + callsign);
                return true;
            }
            catch (ApiNotFoundException exception) {
                // We don't need to log here, as this is a legitimate thing
                return false;
            } catch (ApiException exception) {
                LogInfo(
                    "Error when searching for sqawk assignement, API threw exception: " + std::string(exception.what())
                );
                return false;
            }
        }

        /*
            Calls the API to create a new local squawk assignment or force update an existing one.

            THIS FUNCTION SHOULD ONLY BE USED ON AN ASYNCHRONOUS THREAD.
        */
        bool SquawkGenerator::CreateGeneralSquawkAssignment(
            std::string callsign,
            std::string origin,
            std::string destination
        ) const {
            // Assign the squawk to our aircraft
            try {
                ApiSquawkAllocation allocation = this->api.CreateGeneralSquawkAssignment(
                    callsign,
                    origin,
                    destination
                );
                this->allocations->AddAllocationToQueue(allocation);
                LogInfo("API allocated general squawk " + allocation.squawk + " to " + callsign);
                return true;
            } catch (ApiException exception) {
                LogInfo(
                    "Error when create general squawk assignement, API threw exception: "
                        + std::string(exception.what())
                );
                return false;
            }
        }

        /*
            Calls the API to create a new general squawk assignment or force update an existing one.

            THIS FUNCTION SHOULD ONLY BE USED ON AN ASYNCHRONOUS THREAD.
        */
        bool SquawkGenerator::CreateLocalSquawkAssignment(
            std::string callsign,
            std::string unit,
            std::string flightRules
        ) const {
            try {
                ApiSquawkAllocation allocation = this->api.CreateLocalSquawkAssignment(callsign, unit, flightRules);
                this->allocations->AddAllocationToQueue(allocation);
                LogInfo("API allocated local squawk " + allocation.squawk + " to " + callsign);
                return true;
            } catch (ApiException exception) {
                LogInfo(
                    "Error when create general squawk assignement, API threw exception: " +
                        std::string(exception.what())
                );
                return false;
            }
        }

        /*
            Places a request in progress to prevent duplicate requests
        */
        bool SquawkGenerator::StartSquawkUpdate(EuroScopeCFlightPlanInterface & flightplan)
        {
            // Lock the requests queue and mark the request as in progress. Set a holding squawk.
            if (!this->squawkRequests.Start(flightplan.GetCallsign())) {
                return false;
            }


            flightplan.SetSquawk(this->PROCESS_SQUAWK);
            return true;
        }

        /*
            End of squawk update, remove the in progress flag
        */
        void SquawkGenerator::EndSquawkUpdate(std::string callsign)
        {
            this->squawkRequests.End(callsign);
        }
    }  // namespace Squawk
}  // namespace UKControllerPlugin

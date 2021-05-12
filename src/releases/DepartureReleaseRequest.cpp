#include "pch/stdafx.h"
#include "releases/DepartureReleaseRequest.h"

namespace UKControllerPlugin {
    namespace Releases {

        DepartureReleaseRequest::DepartureReleaseRequest(
            int id,
            std::string callsign,
            int requestingController,
            int targetController,
            std::chrono::system_clock::time_point requestExpiresAt
        ): id(id), callsign(std::move(callsign)), requestingController(requestingController),
           targetController(targetController), requestExpiresAt(requestExpiresAt)
        {
            
        }

        void DepartureReleaseRequest::Acknowledge()
        {
            this->acknowledgedAtTime = std::chrono::system_clock::now();
        }

        void DepartureReleaseRequest::Reject()
        {
            this->rejectedAtTime = std::chrono::system_clock::now();
        }

        void DepartureReleaseRequest::Approve(
            std::chrono::system_clock::time_point releasedAtTime,
            std::chrono::system_clock::time_point releaseExpiresAt
        )
        {
            this->releasedAtTime = releasedAtTime;
            this->releaseExpiresAt = releaseExpiresAt;
        }

        int DepartureReleaseRequest::Id() const
        {
            return this->id;
        }

        std::string DepartureReleaseRequest::Callsign() const
        {
            return this->callsign;
        }

        int DepartureReleaseRequest::RequestingController() const
        {
            return this->requestingController;
        }

        int DepartureReleaseRequest::TargetController() const
        {
            return this->targetController;
        }

        bool DepartureReleaseRequest::Acknowledged() const
        {
            return this->acknowledgedAtTime != this->noTime;
        }

        bool DepartureReleaseRequest::Rejected() const
        {
            return this->rejectedAtTime != this->noTime;
        }

        bool DepartureReleaseRequest::Approved() const
        {
            return this->releaseExpiresAt != this->noTime;
        }

        std::chrono::system_clock::time_point DepartureReleaseRequest::RequestExpiryTime() const
        {
            return this->requestExpiresAt;
        }

        std::chrono::system_clock::time_point DepartureReleaseRequest::ReleaseExpiryTime() const
        {
            return this->releaseExpiresAt;
        }

        std::chrono::system_clock::time_point DepartureReleaseRequest::ReleasedAtTime() const
        {
            return this->releasedAtTime;
        }

        std::chrono::system_clock::time_point DepartureReleaseRequest::RejectedAtTime() const
        {
            return this->rejectedAtTime;
        }

        std::chrono::system_clock::time_point DepartureReleaseRequest::AcknowledgedAtTime() const
        {
            return this->acknowledgedAtTime;
        }
    } // namespace Releases
} // namespace UKControllerPlugin

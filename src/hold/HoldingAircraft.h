#pragma once
#include "pch/stdafx.h"

namespace UKControllerPlugin {
    namespace Hold {

        /*
            Data about a holding aircraft
        */
        typedef struct HoldingAircraft
        {
            const std::string callsign;
            const std::string holdIdentifier;
            int reportedAltitude;
            int clearedAltitude;
        } HoldingAircraft;

    }  // namespace Hold
}  // namespace UKControllerPlugin

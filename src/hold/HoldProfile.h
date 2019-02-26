#pragma once
#include "pch/stdafx.h"

namespace UKControllerPlugin {
    namespace Hold {

        /*
            Represents a profile for the configuration of holds.
        */
        typedef struct HoldProfile
        {
            // The id of the profile
            unsigned int id;

            // The name of the profile
            std::string name;

            // The holds that should be loaded in the profile.
            std::set<unsigned int> holds;

            // Whether or not the profile is a users personal profile.
            bool isUserProfile;

            /*
                Equality - because these are going into combo boxes, we want
                to check for equality based on name and id.
            */
            bool operator==(const HoldProfile & compare) const {
                return this->name == compare.name || this->id == compare.id;
            }
        } HoldProfile;

    }  // namespace Hold
}  // namespace UKControllerPlugin
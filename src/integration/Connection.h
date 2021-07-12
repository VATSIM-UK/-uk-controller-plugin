#pragma once
#include "pch/stdafx.h"

namespace UKControllerPlugin::Integration {

    /*
     * Represents the connection between an external integration and the plugin.
     * This may be achieved through a websocket, a winsock, or hidden window or more.
     *
     * This is used to send messages over the connection.
     */
    class Connection
    {
        public:
            virtual ~Connection() = default;
            virtual void Send(std::string message) = 0;
            virtual std::string Receive() = 0;
            virtual bool Active() const = 0;

            static inline const std::string NO_MESSAGE = "";
    };
} // namespace UKControllerPlugin::Integration

#include "pch/stdafx.h"
#include "notifications/Notification.h"

namespace UKControllerPlugin {
    namespace Notifications {
        Notification::Notification(
            int id,
            std::string title,
            std::string body,
            std::chrono::system_clock::time_point validFrom,
            std::chrono::system_clock::time_point validTo,
            Controller::ControllerPositionHierarchy controllers
        ): id(id), title(std::move(title)), body(std::move(body)), controllers(std::move(controllers)),
            validFrom(std::move(validFrom)), validTo(std::move(validTo))
        {
        }

        int Notification::Id() const
        {
            return this->id;
        }

        std::string Notification::Title() const
        {
            return this->title;
        }

        std::string Notification::Body() const
        {
            return this->body;
        }

        bool Notification::Active() const
        {
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            return now >= this->validFrom && now < this->validTo;
        }

        bool Notification::IsRelevant(const Controller::ControllerPosition& position) const
        {
            return this->controllers.PositionInHierarchy(position);
        }

        bool Notification::IsRead() const
        {
            return this->read;
        }

        bool Notification::Read()
        {
            this->read = true;
        }
    }  // namespace Notifications
}  // namespace UKControllerPlugin

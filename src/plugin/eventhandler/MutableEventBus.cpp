#include "EventBusFactory.h"
#include "MutableEventBus.h"

namespace UKControllerPlugin::EventHandler {

    void MutableEventBus::Reset()
    {
        EventBus::singleton = nullptr;
        EventBus::factory = nullptr;
    }

    void MutableEventBus::SetObserver(std::shared_ptr<EventObserver> observer)
    {
        this->observer = std::move(observer);
    }

    void MutableEventBus::SetFactory(std::shared_ptr<EventBusFactory> factory)
    {
        EventBus::factory = std::move(factory);
    }
} // namespace UKControllerPlugin::EventHandler

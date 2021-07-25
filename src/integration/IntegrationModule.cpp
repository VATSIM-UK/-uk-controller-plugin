#include "pch/stdafx.h"
#include "integration/IntegrationModule.h"
#include "integration/OutboundIntegrationMessageHandler.h"
#include "integration/ExternalMessageEventHandler.h"
#include "integration/IntegrationServer.h"
#include "integration/ClientInitialisationManager.h"
#include "integration/IntegrationClientManager.h"
#include "integration/DummyOutboundIntegrationMessageHandler.h"

using UKControllerPlugin::Bootstrap::PersistenceContainer;

namespace UKControllerPlugin {
    namespace Integration {

        void BootstrapPlugin(PersistenceContainer& container, bool duplicatePlugin, bool winsockInitialised)
        {
            // Create handler and add to other handlers
            container.externalEventHandler = std::make_shared<ExternalMessageEventHandler>(duplicatePlugin);
            auto clientManager = std::make_shared<IntegrationClientManager>();
            auto inboundMessageProcessors = std::make_shared<InboundIntegrationMessageHandler>(clientManager);

            if (duplicatePlugin || !winsockInitialised) {
                container.integrationModuleContainer.reset(new IntegrationPersistenceContainer{
                    std::make_shared<DummyOutboundIntegrationMessageHandler>(),
                    std::move(inboundMessageProcessors),
                    nullptr
                });
                return;
            }

            container.timedHandler->RegisterEvent(clientManager, 5);
            container.timedHandler->RegisterEvent(inboundMessageProcessors, 1);
            container.commandHandlers->RegisterHandler(container.externalEventHandler);
            container.timedHandler->RegisterEvent(container.externalEventHandler, 1);

            // Setup the new server
            auto initialisationManager = std::make_shared<ClientInitialisationManager>(clientManager);
            auto server = std::make_unique<IntegrationServer>(initialisationManager);
            container.timedHandler->RegisterEvent(initialisationManager, 1);
            const auto outboundHandler = std::make_shared<OutboundIntegrationMessageHandler>(clientManager);

            container.integrationModuleContainer.reset(new IntegrationPersistenceContainer{
                outboundHandler,
                std::move(inboundMessageProcessors),
                std::move(server)
            });
        }
    }  // namespace Integration
}  // namespace UKControllerPlugin

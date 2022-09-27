#pragma once

#include "../../src/plugin/pch/pch.h"
#include "euroscope/EuroScopePlugIn.h"

// Ignore warnings about uninitialised variables in the Gmock headers
#pragma warning(push)
#pragma warning(disable : 26495 26451 28251)
#include "gmock/gmock.h"
#include "helper/Matchers.h"
#pragma warning(pop)

// Testingutils mocks
#include "../../testingutils/mock/MockApiInterface.h"
#include "../../testingutils/mock/MockApiSettingsProvider.h"
#include "../../testingutils/mock/MockCurlApi.h"
#include "../../testingutils/mock/MockDialogProvider.h"
#include "../../testingutils/mock/MockWinApi.h"

// Test case
#include "../../testingutils/test/ApiTestCase.h"
#include "../../testingutils/test/ApiMethodExpectation.h"
#include "../../testingutils/test/ApiRequestExpectation.h"
#include "../../testingutils/test/ApiResponseExpectation.h"
#include "../../testingutils/test/ApiUriExpectation.h"

// Plugin mocks
#include "../mock/MockAbstractTimedEvent.h"
#include "../mock/MockActiveCallsignEventHandler.h"
#include "../mock/MockAircraftTypeMapper.h"
#include "../mock/MockAirfieldGroup.h"
#include "../mock/MockAsrEventHandlerInterface.h"
#include "../mock/MockBootstrapProvider.h"
#include "../mock/MockCallsignSelectionProvider.h"
#include "../mock/MockConfigurableDisplay.h"
#include "../mock/MockConnection.h"
#include "../mock/MockControllerStatusEventHandlerInterface.h"
#include "../mock/MockDependencyLoader.h"
#include "../mock/MockDisplayRule.h"
#include "../mock/MockEuroScopeCControllerInterface.h"
#include "../mock/MockEuroScopeCFlightplanInterface.h"
#include "../mock/MockEuroScopeCRadarTargetInterface.h"
#include "../mock/MockEuroscopeExtractedRouteInterface.h"
#include "../mock/MockEuroscopeFlightplanList.h"
#include "../mock/MockEuroscopePluginLoopbackInterface.h"
#include "../mock/MockEuroscopeRadarScreenLoopbackInterface.h"
#include "../mock/MockEuroscopeSectorFileElementInterface.h"
#include "../mock/MockExternalMessageHandlerInterface.h"
#include "../mock/MockFlightPlanEventHandlerInterface.h"
#include "../mock/MockFlightplanRadarTargetPair.h"
#include "../mock/MockGraphicsInterface.h"
#include "../mock/MockHistoryTrailDialog.h"
#include "../mock/MockHistoryTrailRepository.h"
#include "../mock/MockIntegrationActionProcessor.h"
#include "../mock/MockListItemProvider.h"
#include "../mock/MockMappingElementDrawer.h"
#include "../mock/MockMenuToggleableDisplay.h"
#include "../mock/MockMetarEventHandler.h"
#include "../mock/MockOutboundIntegrationEventHandler.h"
#include "../mock/MockPluginSettingsProvider.h"
#include "../mock/MockPopupList.h"
#include "../mock/MockPushEventConnection.h"
#include "../mock/MockPushEventProcessor.h"
#include "../mock/MockRadarRendererableInterface.h"
#include "../mock/MockRadarTargetEventHandlerInterface.h"
#include "../mock/MockRunwayDialogAwareInterface.h"
#include "../mock/MockSectorFileProviderInterface.h"
#include "../mock/MockSidMapperInterface.h"
#include "../mock/MockSocket.h"
#include "mock/MockTaskRunnerInterface.h"
#include "../mock/MockUserSettingAwareInterface.h"
#include "../mock/MockUserSettingProviderInterface.h"
#include "../mock/MockWakeCategoryMapper.h"

// Test cases
#include "../test/BootstrapProviderTestCase.h"

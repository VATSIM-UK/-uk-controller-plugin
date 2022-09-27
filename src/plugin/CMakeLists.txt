set(PROJECT_NAME UKControllerPluginCore)

################################################################################
# Source groups
################################################################################
set(resource
    "../../resource/resource.h"
    "../../resource/UKControllerPlugin.rc"
)
source_group("resource" FILES ${resource})

set(src__aircraft
        aircraft/CallsignSelectionProviderInterface.h
        aircraft/CallsignSelectionList.cpp aircraft/CallsignSelectionList.h
        aircraft/CallsignSelectionListFactory.cpp aircraft/CallsignSelectionListFactory.h
        aircraft/CallsignSelectionListFactoryBootstrap.cpp aircraft/CallsignSelectionListFactoryBootstrap.h
        aircraft/AircraftType.cpp aircraft/AircraftType.h
        aircraft/AircraftTypeCollection.cpp aircraft/AircraftTypeCollection.h
        aircraft/AircraftTypeCollectionFactory.cpp aircraft/AircraftTypeCollectionFactory.h
        aircraft/AircraftTypeFactory.cpp aircraft/AircraftTypeFactory.h
        aircraft/AircraftModule.cpp aircraft/AircraftModule.h
        aircraft/FlightplanAircraftTypeMapper.cpp aircraft/FlightplanAircraftTypeMapper.h
        aircraft/AircraftTypeMapperInterface.h approach/AirfieldMinimumSeparationSelectorList.cpp approach/AirfieldMinimumSeparationSelectorList.h)
source_group("src\\aircraft" FILES ${src__aircraft})

set(src__airfield
    "airfield/AirfieldCollection.cpp"
    "airfield/AirfieldCollection.h"
    "airfield/AirfieldCollectionFactory.cpp"
    "airfield/AirfieldCollectionFactory.h"
    "airfield/AirfieldModel.cpp"
    "airfield/AirfieldModel.h"
        airfield/AirfieldModule.cpp airfield/AirfieldModule.h)
source_group("src\\airfield" FILES ${src__airfield})

set(src__api
    "api/ApiConfigurationMenuItem.cpp"
    "api/ApiConfigurationMenuItem.h"
    api/FirstTimeApiConfigLoader.cpp api/FirstTimeApiConfigLoader.h
    api/BootstrapApi.cpp api/BootstrapApi.h
    api/FirstTimeApiAuthorisationChecker.cpp api/FirstTimeApiAuthorisationChecker.h)
source_group("src\\api" FILES ${src__api})

set(src__approach
        approach/ApproachSpacingRingRenderer.cpp approach/ApproachSpacingRingRenderer.h
        approach/ApproachBootstrapProvider.cpp approach/ApproachBootstrapProvider.h
        approach/ApproachModuleFactory.cpp approach/ApproachModuleFactory.h
        approach/ApproachSequence.cpp approach/ApproachSequence.h
        approach/ApproachSequencedAircraft.h approach/ApproachSequencedAircraft.cpp
        approach/ApproachSequencingMode.h
        approach/ApproachSequencerDisplay.cpp approach/ApproachSequencerDisplay.h
        approach/ApproachSequencer.cpp approach/ApproachSequencer.h
        approach/ApproachSequencerDisplayOptions.cpp approach/ApproachSequencerDisplayOptions.h
        approach/ApproachSequencerDisplayAsrLoader.cpp approach/ApproachSequencerDisplayAsrLoader.h
        approach/ToggleApproachSequencerDisplay.cpp approach/ToggleApproachSequencerDisplay.h
        approach/SequencerAirfieldSelector.cpp approach/SequencerAirfieldSelector.h approach/AircraftSelectionProvider.cpp approach/AircraftSelectionProvider.h approach/TargetSelectorList.cpp approach/TargetSelectorList.h approach/ApproachSpacingCalculator.cpp approach/ApproachSpacingCalculator.h approach/ApproachSequencerOptions.cpp approach/ApproachSequencerOptions.h approach/AirfieldApproachOptions.h approach/ApproachSequencerOptionsLoader.cpp approach/ApproachSequencerOptionsLoader.h approach/AirfieldTargetSelectorList.cpp approach/AirfieldTargetSelectorList.h approach/ApproachSequencerDistanceOptions.cpp approach/ApproachSequencerDistanceOptions.h approach/RemoveLandedAircraft.cpp approach/RemoveLandedAircraft.h approach/ApproachFlightplanEventHandler.cpp approach/ApproachFlightplanEventHandler.h)
source_group("src\\approach" FILES ${src__approach})

set(src__bootstrap
    "bootstrap/BootstrapWarningMessage.cpp"
    "bootstrap/BootstrapWarningMessage.h"
    "bootstrap/CollectionBootstrap.cpp"
    "bootstrap/CollectionBootstrap.h"
    "bootstrap/DllInterface.cpp"
    "bootstrap/EventHandlerCollectionBootstrap.cpp"
    "bootstrap/EventHandlerCollectionBootstrap.h"
    "bootstrap/ExternalsBootstrap.cpp"
    "bootstrap/ExternalsBootstrap.h"
    "bootstrap/HelperBootstrap.cpp"
    "bootstrap/HelperBootstrap.h"
    "bootstrap/InitialisePlugin.cpp"
    "bootstrap/InitialisePlugin.h"
    "bootstrap/PersistenceContainer.h"
    "bootstrap/PostInit.cpp"
    "bootstrap/PostInit.h"
    bootstrap/PersistenceContainer.cpp bootstrap/BootstrapProviderInterface.h bootstrap/BootstrapProviderCollection.h bootstrap/BootstrapProviderCollection.cpp bootstrap/BootstrapProviderCollection.h bootstrap/ModuleFactories.h bootstrap/ModuleFactories.cpp bootstrap/ModuleFactories.h bootstrap/BootstrapProviderCollectionFactory.cpp bootstrap/BootstrapProviderCollectionFactory.h bootstrap/ModuleBootstrap.cpp bootstrap/ModuleBootstrap.h)
source_group("src\\bootstrap" FILES ${src__bootstrap})

set(src__command
    "command/CommandHandlerCollection.cpp"
    "command/CommandHandlerCollection.h"
    "command/CommandHandlerInterface.h"
        command/CommandHandlerInterface.cpp)
source_group("src\\command" FILES ${src__command})

set(src__components
    "components/BrushSwitcher.cpp"
    "components/BrushSwitcher.h"
    "components/Button.cpp"
    "components/Button.h"
    "components/ClickableArea.cpp"
    "components/ClickableArea.h"
    "components/StandardButtons.cpp"
    "components/StandardButtons.h"
    "components/TitleBar.cpp"
    "components/TitleBar.h"
        components/CollapsibleWindowTitleBar.cpp components/CollapsibleWindowTitleBar.h components/Title.cpp components/Title.h components/Checkbox.cpp components/Checkbox.h components/Scrollbar.cpp components/Scrollbar.h components/ScrollbarFactory.cpp components/ScrollbarFactory.h components/ScrollbarClickspot.cpp components/ScrollbarClickspot.h components/ScrollbarOptions.cpp components/ScrollbarOptions.h components/ScrollableCheckboxes.cpp components/ScrollableCheckboxes.h components/CheckboxProviderInterface.cpp components/CheckboxProviderInterface.h)
source_group("src\\components" FILES ${src__components})

set(src__controller
    "controller/ActiveCallsign.cpp"
    "controller/ActiveCallsign.h"
    "controller/ActiveCallsignCollection.cpp"
    "controller/ActiveCallsignCollection.h"
    "controller/ActiveCallsignEventHandlerInterface.h"
    "controller/ActiveCallsignMonitor.cpp"
    "controller/ActiveCallsignMonitor.h"
    "controller/ControllerBootstrap.cpp"
    "controller/ControllerBootstrap.h"
    "controller/ControllerPosition.cpp"
    "controller/ControllerPosition.h"
    "controller/ControllerPositionCollection.cpp"
    "controller/ControllerPositionCollection.h"
    "controller/ControllerPositionCollectionFactory.cpp"
    "controller/ControllerPositionCollectionFactory.h"
    "controller/ControllerPositionHierarchy.cpp"
    "controller/ControllerPositionHierarchy.h"
    "controller/ControllerPositionHierarchyFactory.cpp"
    "controller/ControllerPositionHierarchyFactory.h"
    "controller/ControllerPositionParser.cpp"
    "controller/ControllerPositionParser.h"
    "controller/ControllerStatusEventHandlerCollection.cpp"
    "controller/ControllerStatusEventHandlerCollection.h"
    "controller/ControllerStatusEventHandlerInterface.h"
    "controller/HandoffEventHandlerCollection.cpp"
    "controller/HandoffEventHandlerCollection.h"
    "controller/HandoffEventHandlerInterface.h"
    "controller/TranslateFrequencyAbbreviation.cpp"
    "controller/TranslateFrequencyAbbreviation.h"
        controller/ActiveCallsignEventHandlerInterface.cpp)
source_group("src\\controller" FILES ${src__controller})

set(src__countdown
    "countdown/CountdownModule.cpp"
    "countdown/CountdownModule.h"
    "countdown/CountdownRenderer.cpp"
    "countdown/CountdownRenderer.h"
    "countdown/CountdownTimer.cpp"
    "countdown/CountdownTimer.h"
    "countdown/GlobalCountdownSettingFunctions.cpp"
    "countdown/GlobalCountdownSettingFunctions.h"
    "countdown/TimerConfiguration.h"
    "countdown/TimerConfigurationDialog.cpp"
    "countdown/TimerConfigurationDialog.h"
    "countdown/TimerConfigurationManager.cpp"
    "countdown/TimerConfigurationManager.h"
)
source_group("src\\countdown" FILES ${src__countdown})

set(src__datablock
    "datablock/DatablockBoostrap.cpp"
    "datablock/DatablockBoostrap.h"
    "datablock/DatablockFunctions.cpp"
    "datablock/DatablockFunctions.h"
    "datablock/DisplayTime.cpp"
    "datablock/DisplayTime.h"
)
source_group("src\\datablock" FILES ${src__datablock})

set(src__departure
        departure/DepartureCoordinationList.cpp departure/DepartureCoordinationList.h departure/ToggleDepartureCoordinationList.cpp departure/ToggleDepartureCoordinationList.h departure/DepartureModule.cpp departure/DepartureModule.h)
source_group("src\\departure" FILES ${src__departure})

set(src__dependency
    "dependency/DependencyLoader.cpp"
    "dependency/DependencyLoader.h"
    "dependency/DependencyLoaderInterface.h"
    "dependency/UpdateDependencies.cpp"
    "dependency/UpdateDependencies.h"
)
source_group("src\\dependency" FILES ${src__dependency})

set(src__euroscope
    "euroscope/AsrEventHandlerCollection.cpp"
    "euroscope/AsrEventHandlerCollection.h"
    "euroscope/AsrEventHandlerInterface.h"
    "euroscope/CallbackFunction.cpp"
    "euroscope/CallbackFunction.h"
    "euroscope/CompareFunctions.cpp"
    "euroscope/CompareFunctions.h"
    "euroscope/EuroScopeCControllerInterface.h"
    "euroscope/EuroScopeCControllerWrapper.cpp"
    "euroscope/EuroScopeCControllerWrapper.h"
    "euroscope/EuroScopeCFlightPlanInterface.h"
    "euroscope/EuroScopeCFlightPlanWrapper.cpp"
    "euroscope/EuroScopeCFlightPlanWrapper.h"
    "euroscope/EuroScopeCRadarTargetInterface.h"
    "euroscope/EuroScopeCRadarTargetPositionDataInterface.h"
    "euroscope/EuroScopeCRadarTargetWrapper.cpp"
    "euroscope/EuroScopeCRadarTargetWrapper.h"
    "euroscope/EuroscopeExtractedRouteInterface.cpp"
    "euroscope/EuroscopeExtractedRouteInterface.h"
    "euroscope/EuroscopeFlightplanListInterface.h"
    "euroscope/EuroscopeFlightplanListWrapper.cpp"
    "euroscope/EuroscopeFlightplanListWrapper.h"
    "euroscope/EuroscopePluginLoopbackInterface.h"
    "euroscope/EuroscopeRadarLoopbackInterface.h"
    "euroscope/EuroscopeSectorFileElementInterface.h"
    "euroscope/EuroscopeSectorFileElementWrapper.cpp"
    "euroscope/EuroscopeSectorFileElementWrapper.h"
    "euroscope/GeneralSettingsConfiguration.cpp"
    "euroscope/GeneralSettingsConfiguration.h"
    "euroscope/GeneralSettingsConfigurationBootstrap.cpp"
    "euroscope/GeneralSettingsConfigurationBootstrap.h"
    "euroscope/GeneralSettingsDialog.cpp"
    "euroscope/GeneralSettingsDialog.h"
    "euroscope/GeneralSettingsEntries.cpp"
    "euroscope/GeneralSettingsEntries.h"
    "euroscope/LoadDefaultUserSettings.cpp"
    "euroscope/LoadDefaultUserSettings.h"
    "euroscope/PluginUserSettingBootstrap.cpp"
    "euroscope/PluginUserSettingBootstrap.h"
    "euroscope/RadarTargetEventHandlerCollection.cpp"
    "euroscope/RadarTargetEventHandlerCollection.h"
    "euroscope/RadarTargetEventHandlerInterface.h"
    "euroscope/RunwayDialogAwareCollection.cpp"
    "euroscope/RunwayDialogAwareCollection.h"
    "euroscope/RunwayDialogAwareInterface.h"
    "euroscope/UserSetting.cpp"
    "euroscope/UserSetting.h"
    "euroscope/UserSettingAwareCollection.cpp"
    "euroscope/UserSettingAwareCollection.h"
    "euroscope/UserSettingAwareInterface.h"
    "euroscope/UserSettingProviderInterface.h"
        euroscope/AsrEventHandlerInterface.cpp euroscope/UserSettingProviderInterface.cpp euroscope/EuroscopeRadarLoopbackInterface.cpp euroscope/PluginSettingsProviderInterface.h euroscope/PluginSettingsProviderCollection.cpp euroscope/PluginSettingsProviderCollection.h)
source_group("src\\euroscope" FILES ${src__euroscope})

set(src__flightinformationservice
    "flightinformationservice/FlightInformationServiceModule.cpp"
    "flightinformationservice/FlightInformationServiceModule.h"
    "flightinformationservice/FlightInformationServiceTagItem.cpp"
    "flightinformationservice/FlightInformationServiceTagItem.h"
)
source_group("src\\flightinformationservice" FILES ${src__flightinformationservice})

set(src__flightplan
    "flightplan/FlightPlanEventHandlerCollection.cpp"
    "flightplan/FlightPlanEventHandlerCollection.h"
    "flightplan/FlightPlanEventHandlerInterface.h"
    "flightplan/FlightplanStorageBootstrap.cpp"
    "flightplan/FlightplanStorageBootstrap.h"
    "flightplan/StoredFlightplan.cpp"
    "flightplan/StoredFlightplan.h"
    "flightplan/StoredFlightplanCollection.cpp"
    "flightplan/StoredFlightplanCollection.h"
    "flightplan/StoredFlightplanEventHandler.cpp"
    "flightplan/StoredFlightplanEventHandler.h"
)
source_group("src\\flightplan" FILES ${src__flightplan})

set(src__flightrule
        flightrule/FlightRule.h
        flightrule/FlightRuleCollection.cpp flightrule/FlightRuleCollection.h
        flightrule/FlightRuleModule.cpp flightrule/FlightRuleModule.h
        flightrule/FlightRuleCollectionFactory.cpp flightrule/FlightRuleCollectionFactory.h)
source_group("src\\flightrule" FILES ${src__flightrule})

set(src__geometry
        geometry/Line.cpp geometry/Line.h geometry/DistanceRadiusToScreenRadius.cpp geometry/DistanceRadiusToScreenRadius.h geometry/RectangleFunctions.cpp geometry/RectangleFunctions.h)
source_group("src\\geometry" FILES ${src__geometry})

set(src__graphics
    "graphics/GdiGraphicsInterface.h"
    "graphics/GdiGraphicsWrapper.cpp"
    "graphics/GdiGraphicsWrapper.h"
    "graphics/GdiplusBrushes.h"
        graphics/FontManager.cpp graphics/FontManager.h graphics/StringFormatManager.cpp graphics/StringFormatManager.h graphics/DrawTriangle.cpp graphics/DrawTriangle.h)
source_group("src\\graphics" FILES ${src__graphics})

set(src__handoff
    "handoff/ResolvedHandoff.h"
    "handoff/ResolvedHandoff.cpp"
    "handoff/HandoffCollection.cpp"
    "handoff/HandoffCollection.h"
    "handoff/HandoffCollectionFactory.cpp"
    "handoff/HandoffCollectionFactory.h"
    "handoff/HandoffEventHandler.cpp"
    "handoff/HandoffEventHandler.h"
    "handoff/HandoffFrequencyUpdatedMessage.cpp"
    "handoff/HandoffFrequencyUpdatedMessage.h"
    "handoff/HandoffModule.cpp"
    "handoff/HandoffModule.h"
    controller/HandoffEventHandler.cpp
    handoff/HandoffOrder.h handoff/HandoffOrder.cpp handoff/FlightplanSidHandoffMapper.cpp handoff/FlightplanSidHandoffMapper.h handoff/HandoffCache.cpp handoff/HandoffCache.h handoff/DepartureHandoffResolver.cpp handoff/DepartureHandoffResolver.h handoff/FlightplanAirfieldHandoffMapper.cpp handoff/FlightplanAirfieldHandoffMapper.h handoff/ClearCacheOnActiveCallsignChanges.cpp handoff/ClearCacheOnActiveCallsignChanges.h handoff/ClearCacheOnRunwayDialogSave.cpp handoff/ClearCacheOnRunwayDialogSave.h)
source_group("src\\handoff" FILES ${src__handoff})

set(src__headings headings/Heading.h headings/Heading.cpp)
source_group("src\\headings" FILES ${src__headings})

set(src__historytrail
    "historytrail/AircraftHistoryTrail.cpp"
    "historytrail/AircraftHistoryTrail.h"
    "historytrail/HistoryTrailData.h"
    "historytrail/HistoryTrailDialog.cpp"
    "historytrail/HistoryTrailDialog.h"
    "historytrail/HistoryTrailEventHandler.cpp"
    "historytrail/HistoryTrailEventHandler.h"
    "historytrail/HistoryTrailModule.cpp"
    "historytrail/HistoryTrailModule.h"
    "historytrail/HistoryTrailPoint.h"
    "historytrail/HistoryTrailRenderer.cpp"
    "historytrail/HistoryTrailRenderer.h"
    "historytrail/HistoryTrailRepository.cpp"
    "historytrail/HistoryTrailRepository.h"
)
source_group("src\\historytrail" FILES ${src__historytrail})

set(src__hold
    "hold/AbstractHoldLevelRestriction.h"
    "hold/BlockedHoldLevelRestriction.cpp"
    "hold/BlockedHoldLevelRestriction.h"
    "hold/BlockedHoldLevelRestrictionSerializer.cpp"
    "hold/BlockedHoldLevelRestrictionSerializer.h"
    "hold/CompareHoldingAircraft.cpp"
    "hold/CompareHoldingAircraft.h"
    "hold/CompareHolds.cpp"
    "hold/CompareHolds.h"
    "hold/CompareHoldsDescription.cpp"
    "hold/CompareHoldsDescription.h"
    "hold/DeemedSeparatedHold.h"
    "hold/DeemedSeparatedHoldSerializer.cpp"
    "hold/DeemedSeparatedHoldSerializer.h"
    "hold/HoldConfigurationDialog.cpp"
    "hold/HoldConfigurationDialog.h"
    "hold/HoldConfigurationMenuItem.cpp"
    "hold/HoldConfigurationMenuItem.h"
    "hold/HoldDisplay.cpp"
    "hold/HoldDisplay.h"
    "hold/HoldDisplayConfigurationDialog.cpp"
    "hold/HoldDisplayConfigurationDialog.h"
    "hold/HoldDisplayFactory.cpp"
    "hold/HoldDisplayFactory.h"
    "hold/HoldDisplayFunctions.cpp"
    "hold/HoldDisplayFunctions.h"
    "hold/HoldDisplayManager.cpp"
    "hold/HoldDisplayManager.h"
    "hold/HoldEventHandler.cpp"
    "hold/HoldEventHandler.h"
    "hold/HoldingAircraft.cpp"
    "hold/HoldingAircraft.h"
    "hold/HoldingData.cpp"
    "hold/HoldingData.h"
    "hold/HoldingDataSerializer.cpp"
    "hold/HoldingDataSerializer.h"
    "hold/HoldManager.cpp"
    "hold/HoldManager.h"
    "hold/HoldModule.cpp"
    "hold/HoldModule.h"
    "hold/HoldRenderer.cpp"
    "hold/HoldRenderer.h"
    "hold/HoldRestrictionSerializer.cpp"
    "hold/HoldRestrictionSerializer.h"
    "hold/HoldSelectionMenu.cpp"
    "hold/HoldSelectionMenu.h"
    "hold/MinStackHoldLevelRestriction.cpp"
    "hold/MinStackHoldLevelRestriction.h"
    "hold/MinStackHoldLevelRestrictionSerializer.cpp"
    "hold/MinStackHoldLevelRestrictionSerializer.h"
    "hold/PublishedHoldCollection.cpp"
    "hold/PublishedHoldCollection.h"
    "hold/PublishedHoldCollectionFactory.cpp"
    "hold/PublishedHoldCollectionFactory.h"
        hold/AssignHoldCommand.cpp hold/AssignHoldCommand.h hold/AddToHoldCallsignProvider.cpp hold/AddToHoldCallsignProvider.h hold/ProximityHold.h hold/CompareProximityHolds.cpp hold/CompareProximityHolds.h hold/AircraftEnteredHoldingAreaEventHandler.cpp hold/AircraftEnteredHoldingAreaEventHandler.h hold/AircraftExitedHoldingAreaEventHandler.cpp hold/AircraftExitedHoldingAreaEventHandler.h hold/ProximityHold.cpp)
source_group("src\\hold" FILES ${src__hold})

set(src__initialaltitude
    "initialaltitude/InitialAltitudeEventHandler.cpp"
    "initialaltitude/InitialAltitudeEventHandler.h"
    "initialaltitude/InitialAltitudeModule.cpp"
    "initialaltitude/InitialAltitudeModule.h"
)
source_group("src\\initialaltitude" FILES ${src__initialaltitude})

set(src__initialheading
    "initialheading/InitialHeadingEventHandler.cpp"
    "initialheading/InitialHeadingEventHandler.h"
    "initialheading/InitialHeadingModule.cpp"
    "initialheading/InitialHeadingModule.h"
)
source_group("src\\initialheading" FILES ${src__initialheading})

set(src__integration
    "integration/ClientInitialisationManager.cpp"
    "integration/ClientInitialisationManager.h"
    "integration/Connection.h"
    "integration/DummyOutboundIntegrationMessageHandler.cpp"
    "integration/DummyOutboundIntegrationMessageHandler.h"
    "integration/ExternalMessageEventHandler.cpp"
    "integration/ExternalMessageEventHandler.h"
    "integration/ExternalMessageHandlerInterface.h"
    "integration/HiddenWindow.cpp"
    "integration/HiddenWindow.h"
    "integration/InboundIntegrationMessageHandler.cpp"
    "integration/InboundIntegrationMessageHandler.h"
    "integration/IntegrationActionProcessor.h"
    "integration/InboundMessage.cpp"
    "integration/InboundMessage.h"
    "integration/InitialisationFailureMessage.cpp"
    "integration/InitialisationFailureMessage.h"
    "integration/InitialisationSuccessMessage.cpp"
    "integration/InitialisationSuccessMessage.h"
    "integration/IntegrationClient.cpp"
    "integration/IntegrationClient.h"
    "integration/IntegrationClientManager.cpp"
    "integration/IntegrationClientManager.h"
    "integration/IntegrationConnection.cpp"
    "integration/IntegrationConnection.h"
    "integration/IntegrationModule.cpp"
    "integration/IntegrationModule.h"
    "integration/IntegrationPersistenceContainer.h"
    "integration/IntegrationPersistenceContainer.cpp"
    "integration/IntegrationServer.cpp"
    "integration/IntegrationServer.h"
    "integration/MessageInterface.h"
    "integration/MessageType.h"
    "integration/OutboundIntegrationEventHandler.h"
    "integration/OutboundIntegrationMessageHandler.cpp"
    "integration/OutboundIntegrationMessageHandler.h"
    "integration/SocketConnection.cpp"
    "integration/SocketConnection.h"
    "integration/SocketInterface.h"
    "integration/SocketWrapper.cpp"
    "integration/SocketWrapper.h"
        integration/ActionSuccessMessage.cpp integration/ActionSuccessMessage.h integration/ActionFailureMessage.cpp integration/ActionFailureMessage.h integration/MessageType.cpp integration/ExternalMessageHandlerInterface.cpp)
source_group("src\\integration" FILES ${src__integration})

set(src__intention
    "intention/AirfieldGroup.cpp"
    "intention/AirfieldGroup.h"
    "intention/AmsterdamAirfieldGroup.cpp"
    "intention/AmsterdamAirfieldGroup.h"
    "intention/BrusselsAirfieldGroup.cpp"
    "intention/BrusselsAirfieldGroup.h"
    "intention/DublinAirfieldGroup.cpp"
    "intention/DublinAirfieldGroup.h"
    "intention/HomeAirfieldGroup.cpp"
    "intention/HomeAirfieldGroup.h"
    "intention/IntentionCodeCache.cpp"
    "intention/IntentionCodeCache.h"
    "intention/IntentionCodeData.h"
    "intention/IntentionCodeEventHandler.cpp"
    "intention/IntentionCodeEventHandler.h"
    "intention/IntentionCodeFactory.cpp"
    "intention/IntentionCodeFactory.h"
    "intention/IntentionCodeGenerator.cpp"
    "intention/IntentionCodeGenerator.h"
    "intention/IntentionCodeModule.cpp"
    "intention/IntentionCodeModule.h"
    "intention/IntentionCodeUpdatedMessage.cpp"
    "intention/IntentionCodeUpdatedMessage.h"
    "intention/SectorExitPoint.cpp"
    "intention/SectorExitPoint.h"
    "intention/SectorExitPointEtrat.cpp"
    "intention/SectorExitPointEtrat.h"
    "intention/SectorExitPointKonan.cpp"
    "intention/SectorExitPointKonan.h"
    "intention/SectorExitPointLelna.cpp"
    "intention/SectorExitPointLelna.h"
    "intention/SectorExitPointScottish.cpp"
    "intention/SectorExitPointScottish.h"
    "intention/SectorExitPointVeule.cpp"
    "intention/SectorExitPointVeule.h"
    "intention/SectorExitRepository.cpp"
    "intention/SectorExitRepository.h"
    "intention/SectorExitRepositoryFactory.cpp"
    "intention/SectorExitRepositoryFactory.h"
    "intention/ShannonAirfieldGroup.cpp"
    "intention/ShannonAirfieldGroup.h"
)
source_group("src\\intention" FILES ${src__intention})

set(src__list
        list/ListItemProviderInterface.h
        list/PopupListInterface.h
        list/PopupList.cpp list/PopupList.h
        list/PopupListFactory.cpp list/PopupListFactory.h
        list/ListItem.h
        list/ListItemCheckedStatus.h
        list/PopupListFactoryBootstrap.cpp list/PopupListFactoryBootstrap.h)
source_group("src\\list" FILES ${src__list})

set(src__login
    "login/Login.cpp"
    "login/Login.h"
    "login/LoginModule.cpp"
    "login/LoginModule.h"
)
source_group("src\\login" FILES ${src__login})

set(src__mapping
        mapping/MappingElement.cpp mapping/MappingElement.h
        mapping/MappingElementInterface.h
        mapping/MappingElementDrawer.h
        mapping/DisplayRule.h
        mapping/VisualReferencePoint.cpp mapping/VisualReferencePoint.h
        mapping/MappingElementManager.cpp mapping/MappingElementManager.h
        mapping/MappingElementManagerFactory.cpp mapping/MappingElementManagerFactory.h
        mapping/MappingModuleFactory.cpp mapping/MappingModuleFactory.h
        mapping/MappingBootstrapProvider.cpp mapping/MappingBootstrapProvider.h
        mapping/MappingRenderer.cpp mapping/MappingRenderer.h
        mapping/MappingOptionsRenderer.cpp mapping/MappingOptionsRenderer.h
        mapping/MappingRenderOptions.cpp mapping/MappingRenderOptions.h
        mapping/ToggleMappingOptionsRender.cpp mapping/ToggleMappingOptionsRender.h
        mapping/VisualReferencePointShouldRender.cpp mapping/VisualReferencePointShouldRender.h
        mapping/RelatedAirfieldProvider.h
        mapping/RelatedAirfield.cpp mapping/RelatedAirfield.h
        mapping/VisualReferencePointRelatedAirfieldProvider.cpp mapping/VisualReferencePointRelatedAirfieldProvider.h
        mapping/MappingElementDrawerFactoryDelegator.cpp mapping/MappingElementDrawerFactoryDelegator.h
        mapping/MappingElementFactory.h
        mapping/MappingElementDrawerFactory.h
        mapping/VisualReferencePointDrawerFactory.cpp mapping/VisualReferencePointDrawerFactory.h
        mapping/ShowsVisualReferencePoints.cpp mapping/ShowsVisualReferencePoints.h
        mapping/RelatedAirfieldProviderFactory.cpp mapping/RelatedAirfieldProviderFactory.h
        mapping/MappingElementFactory.cpp
        mapping/DisplayRuleFactoryInterface.h
        mapping/DisplayRuleTypeDelegatorFactory.cpp mapping/DisplayRuleTypeDelegatorFactory.h
        mapping/DisplayRuleElementTypeDelegatorFactory.cpp mapping/DisplayRuleElementTypeDelegatorFactory.h
        mapping/DisplayRuleFactoryFactory.cpp mapping/DisplayRuleFactoryFactory.h
        mapping/VisualReferencePointRelatedAirfieldFactory.cpp mapping/VisualReferencePointRelatedAirfieldFactory.h
        mapping/DisplayRulesetFactory.cpp mapping/DisplayRulesetFactory.h
        mapping/DisplayRulesetFactoryInterface.h
        mapping/DisplayRulesetAggregatorFactory.cpp mapping/DisplayRulesetAggregatorFactory.h
        mapping/VisualReferencePointDefaultDisplayRulesetFactory.cpp mapping/VisualReferencePointDefaultDisplayRulesetFactory.h mapping/DefaultDisplayRulesetDelegatorFactory.cpp mapping/DefaultDisplayRulesetDelegatorFactory.h mapping/DisplayRulesetFactoryFactory.cpp mapping/DisplayRulesetFactoryFactory.h mapping/MappingElementDrawerFactoryFactory.cpp mapping/MappingElementDrawerFactoryFactory.h mapping/MappingElementTypes.cpp mapping/MappingElementTypes.h mapping/MappingRenderOptionsAsrLoader.cpp mapping/MappingRenderOptionsAsrLoader.h mapping/VisualReferencePointCheckboxProvider.cpp mapping/VisualReferencePointCheckboxProvider.h)
source_group("src\\mapping" FILES ${src__mapping})

set(src__message
    "message/MessageSerializableInterface.h"
    "message/UserMessager.cpp"
    "message/UserMessager.h"
    "message/UserMessagerBootstrap.cpp"
    "message/UserMessagerBootstrap.h"
        message/MessageSerializableInterface.cpp)
source_group("src\\message" FILES ${src__message})

set(src__metar
    "metar/MetarEventHandlerCollection.cpp"
    "metar/MetarEventHandlerCollection.h"
    metar/MetarEventHandlerInterface.cpp
    "metar/MetarEventHandlerInterface.h"
    "metar/PressureChangeMessage.cpp"
    "metar/PressureChangeMessage.h"
    "metar/PressureMonitor.cpp"
    "metar/PressureMonitor.h"
    "metar/PressureMonitorBootstrap.cpp"
    "metar/PressureMonitorBootstrap.h"
    metar/ParsedMetar.cpp metar/ParsedMetar.h
    metar/PressureComponent.h metar/PressureComponent.cpp
    metar/PressureUnit.h
    metar/MetarComponents.h
    metar/ParsedMetarCollection.cpp metar/ParsedMetarCollection.h
    metar/MetarComponentsFactory.cpp metar/MetarComponentsFactory.h
    metar/MetarComponentFactoryInterface.h
    metar/PressureComponentFactory.cpp metar/PressureComponentFactory.h
    metar/MetarComponentsFactoryFactory.cpp metar/MetarComponentsFactoryFactory.h
    metar/MetarsUpdatedPushEventProcessor.cpp metar/MetarsUpdatedPushEventProcessor.h
    metar/ParsedMetarFactory.cpp metar/ParsedMetarFactory.h
    metar/MetarModule.cpp metar/MetarModule.h
    metar/PressureQueryCommandHandler.cpp metar/PressureQueryCommandHandler.h
    metar/PressureQueryMessage.cpp metar/PressureQueryMessage.h
    metar/PressureNotFoundMessage.cpp metar/PressureNotFoundMessage.h)
source_group("src\\metar" FILES ${src__metar})

set(src__minstack
    "minstack/MinStackConfigurationDialog.cpp"
    "minstack/MinStackConfigurationDialog.h"
    "minstack/MinStackLevel.h"
    "minstack/MinStackManager.cpp"
    "minstack/MinStackManager.h"
    "minstack/MinStackModule.cpp"
    "minstack/MinStackModule.h"
    "minstack/MinStackRenderedItem.h"
    "minstack/MinStackRenderer.cpp"
    "minstack/MinStackRenderer.h"
    "minstack/MinStackRendererConfiguration.cpp"
    "minstack/MinStackRendererConfiguration.h"
        minstack/MinStackLevel.cpp minstack/MinStackRenderedItem.cpp)
source_group("src\\minstack" FILES ${src__minstack})

set(src__missedapproach
        missedapproach/MissedApproach.cpp missedapproach/MissedApproach.h
        missedapproach/MissedApproachCollection.cpp missedapproach/MissedApproachCollection.h
        missedapproach/CompareMissedApproaches.cpp missedapproach/CompareMissedApproaches.h
        missedapproach/RemoveExpiredMissedApproaches.cpp missedapproach/RemoveExpiredMissedApproaches.h
        missedapproach/MissedApproachModule.cpp missedapproach/MissedApproachModule.h
        missedapproach/NewMissedApproachPushEventHandler.cpp missedapproach/NewMissedApproachPushEventHandler.h
        missedapproach/TriggerMissedApproach.cpp missedapproach/TriggerMissedApproach.h
        missedapproach/MissedApproachRenderer.cpp missedapproach/MissedApproachRenderer.h
        missedapproach/MissedApproachRenderMode.h
        missedapproach/MissedApproachRenderOptions.cpp missedapproach/MissedApproachRenderOptions.h
        missedapproach/MissedApproachConfigurationDialog.cpp missedapproach/MissedApproachConfigurationDialog.h
        missedapproach/MissedApproachOptions.cpp missedapproach/MissedApproachOptions.h
        missedapproach/MissedApproachAudioAlert.cpp missedapproach/MissedApproachAudioAlert.h
        missedapproach/MissedApproachUserSettingHandler.cpp missedapproach/MissedApproachUserSettingHandler.h
        missedapproach/MissedApproachButton.cpp missedapproach/MissedApproachButton.h
        missedapproach/ToggleMissedApproachButton.cpp missedapproach/ToggleMissedApproachButton.h
        missedapproach/ConfigureMissedApproaches.cpp missedapproach/ConfigureMissedApproaches.h
        missedapproach/MissedApproachTriggeredMessage.cpp missedapproach/MissedApproachTriggeredMessage.h
        missedapproach/TriggerMissedApproachMessageHandler.cpp missedapproach/TriggerMissedApproachMessageHandler.h
        missedapproach/MissedApproachAcknowledgedUserMessage.cpp missedapproach/MissedApproachAcknowledgedUserMessage.h
        missedapproach/MissedApproachAcknowledgedPushEventProcessor.cpp missedapproach/MissedApproachAcknowledgedPushEventProcessor.h
        missedapproach/MissedApproachIndicator.cpp missedapproach/MissedApproachIndicator.h
        missedapproach/AcknowledgeMissedApproachTagFunction.cpp missedapproach/AcknowledgeMissedApproachTagFunction.h
        missedapproach/AcknowledgeMissedApproachDialog.cpp missedapproach/AcknowledgeMissedApproachDialog.h)

source_group("src\\missedapproach" FILES ${src__missedapproach})

set(src__navaids
    "navaids/CompareNavaids.cpp"
    "navaids/CompareNavaids.h"
    "navaids/Navaid.h"
    "navaids/NavaidCollection.cpp"
    "navaids/NavaidCollection.h"
    "navaids/NavaidModule.cpp"
    "navaids/NavaidModule.h"
        navaids/Navaid.cpp)
source_group("src\\navaids" FILES ${src__navaids})

set(src__notifications
    "notifications/Notification.cpp"
    "notifications/Notification.h"
    "notifications/NotificationsDialog.cpp"
    "notifications/NotificationsDialog.h"
    "notifications/NotificationsEventHandler.cpp"
    "notifications/NotificationsEventHandler.h"
    "notifications/NotificationsMenuItem.cpp"
    "notifications/NotificationsMenuItem.h"
    "notifications/NotificationsModule.cpp"
    "notifications/NotificationsModule.h"
    "notifications/NotificationsRepository.cpp"
    "notifications/NotificationsRepository.h"
    "notifications/NotificationsRepositoryFactory.cpp"
    "notifications/NotificationsRepositoryFactory.h"
    "notifications/UnreadNotificationsMessage.cpp"
    "notifications/UnreadNotificationsMessage.h"
)
source_group("src\\notifications" FILES ${src__notifications})

set(src__number
        number/NumberFormat.cpp number/NumberFormat.h)
source_group("src\\number" FILES ${src__number})

set(src__oceanic
    "oceanic/Clearance.h"
    "oceanic/OceanicClearanceDialog.cpp"
    "oceanic/OceanicClearanceDialog.h"
    "oceanic/OceanicEventHandler.cpp"
    "oceanic/OceanicEventHandler.h"
    "oceanic/OceanicModule.cpp"
    "oceanic/OceanicModule.h"
        oceanic/Clearance.cpp)
source_group("src\\oceanic" FILES ${src__oceanic})

set(src__offblock
    "offblock/ActualOffBlockTimeBootstrap.cpp"
    "offblock/ActualOffBlockTimeBootstrap.h"
    "offblock/ActualOffBlockTimeEventHandler.cpp"
    "offblock/ActualOffBlockTimeEventHandler.h"
    "offblock/EstimatedDepartureTimeBootstrap.cpp"
    "offblock/EstimatedDepartureTimeBootstrap.h"
    "offblock/EstimatedDepartureTimeEventHandler.cpp"
    "offblock/EstimatedDepartureTimeEventHandler.h"
    "offblock/EstimatedOffBlockTimeBootstrap.cpp"
    "offblock/EstimatedOffBlockTimeBootstrap.h"
    "offblock/EstimatedOffBlockTimeEventHandler.cpp"
    "offblock/EstimatedOffBlockTimeEventHandler.h"
)
source_group("src\\offblock" FILES ${src__offblock})

set(src__ownership
    "ownership/AirfieldOwnerQueryMessage.cpp"
    "ownership/AirfieldOwnerQueryMessage.h"
    "ownership/AirfieldOwnershipHandler.cpp"
    "ownership/AirfieldOwnershipHandler.h"
    "ownership/AirfieldOwnershipManager.cpp"
    "ownership/AirfieldOwnershipManager.h"
    "ownership/AirfieldOwnershipModule.cpp"
    "ownership/AirfieldOwnershipModule.h"
    "ownership/AirfieldsOwnedQueryMessage.cpp"
    "ownership/AirfieldsOwnedQueryMessage.h"
    ownership/ServiceProvision.h ownership/ServiceProvision.cpp
    ownership/ServiceType.h
    ownership/AirfieldServiceProviderCollection.cpp ownership/AirfieldServiceProviderCollection.h)
source_group("src\\ownership" FILES ${src__ownership})

set(src__plugin
    "plugin/ForceUpdate.cpp"
    "plugin/ForceUpdate.h"
    "plugin/FunctionCallEventHandler.cpp"
    "plugin/FunctionCallEventHandler.h"
    "plugin/PluginChangelog.cpp"
    "plugin/PluginChangelog.h"
    "plugin/PluginHelpPage.cpp"
    "plugin/PluginHelpPage.h"
    "plugin/PluginInformationBootstrap.cpp"
    "plugin/PluginInformationBootstrap.h"
    "plugin/PluginInformationMessage.cpp"
    "plugin/PluginInformationMessage.h"
    "plugin/PopupMenuItem.h"
    "plugin/UKPlugin.cpp"
    "plugin/UKPlugin.h"
    "plugin/UkPluginBootstrap.cpp"
    "plugin/UkPluginBootstrap.h"
        euroscope/UserSettingAwareInterface.cpp)
source_group("src\\plugin" FILES ${src__plugin})

set(src__prenote
    "prenote/PrenoteEventHandler.cpp"
    "prenote/PrenoteEventHandler.h"
    "prenote/PrenoteUserMessage.cpp"
    "prenote/PrenoteUserMessage.h"
    "prenote/PrenoteModule.cpp"
    "prenote/PrenoteModule.h"
    "prenote/PrenoteService.cpp"
    "prenote/PrenoteService.h"
    "prenote/PrenoteMessage.cpp"
    prenote/PrenoteMessageCollection.cpp prenote/PrenoteMessageCollection.h
    prenote/ComparePrenoteMessages.cpp prenote/ComparePrenoteMessages.h
    prenote/PrenoteAcknowledgedPushEventHandler.cpp prenote/PrenoteAcknowledgedPushEventHandler.h
    prenote/PrenoteDeletedPushEventHandler.cpp prenote/PrenoteDeletedPushEventHandler.h
    prenote/NewPrenotePushEventHandler.cpp prenote/NewPrenotePushEventHandler.h
    prenote/PrenoteMessageTimeout.cpp prenote/PrenoteMessageTimeout.h
    prenote/PrenoteStatusIndicatorTagItem.cpp prenote/PrenoteStatusIndicatorTagItem.h
    prenote/CancelPrenoteMessageMenu.cpp prenote/CancelPrenoteMessageMenu.h
    prenote/SendPrenoteMenu.cpp prenote/SendPrenoteMenu.h
    prenote/PrenoteMessageStatusView.cpp prenote/PrenoteMessageStatusView.h
    prenote/TriggerPrenoteMessageStatusView.cpp prenote/TriggerPrenoteMessageStatusView.h
    prenote/AcknowledgePrenoteMessage.cpp prenote/AcknowledgePrenoteMessage.h
    prenote/PublishedPrenote.h prenote/PublishedPrenote.cpp
    prenote/PublishedPrenoteCollection.cpp prenote/PublishedPrenoteCollection.h
    prenote/PublishedPrenoteCollectionFactory.cpp prenote/PublishedPrenoteCollectionFactory.h
    prenote/PairedAirfieldPrenote.h
    prenote/PublishedPrenoteMapper.cpp prenote/PublishedPrenoteMapper.h)
source_group("src\\prenote" FILES ${src__prenote})

set(src__push
    "push/InterpretPushEvent.cpp"
    "push/InterpretPushEvent.h"
    "push/PollingPushEventConnection.cpp"
    "push/PollingPushEventConnection.h"
    "push/PushEvent.h"
    "push/PushEventBootstrap.cpp"
    "push/PushEventBootstrap.h"
    "push/PushEventConnectionInterface.h"
    "push/PushEventProcessorCollection.cpp"
    "push/PushEventProcessorCollection.h"
    "push/PushEventProcessorInterface.h"
    "push/PushEventProtocolHandler.cpp"
    "push/PushEventProtocolHandler.h"
    "push/PushEventProxyConnection.cpp"
    "push/PushEventProxyConnection.h"
    "push/PushEventProxyHandler.cpp"
    "push/PushEventProxyHandler.h"
    "push/PushEventProxyWindow.cpp"
    "push/PushEventProxyWindow.h"
    "push/PushEventSubscription.cpp"
    "push/PushEventSubscription.h"
    push/PushEvent.cpp
    push/PushEventConnectionInterface.cpp
    push/ProxyPushDataSync.cpp push/ProxyPushDataSync.h)
source_group("src\\push" FILES ${src__push})

set(src__radarscreen
    "radarscreen/ConfigurableDisplayCollection.cpp"
    "radarscreen/ConfigurableDisplayCollection.h"
    "radarscreen/ConfigurableDisplayInterface.h"
    "radarscreen/PositionResetCommand.cpp"
    "radarscreen/PositionResetCommand.h"
    "radarscreen/RadarRenderableCollection.cpp"
    "radarscreen/RadarRenderableCollection.h"
    "radarscreen/RadarRenderableInterface.h"
    "radarscreen/RadarScreenFactory.cpp"
    "radarscreen/RadarScreenFactory.h"
    "radarscreen/ScreenControls.cpp"
    "radarscreen/ScreenControls.h"
    "radarscreen/ScreenControlsBootstrap.cpp"
    "radarscreen/ScreenControlsBootstrap.h"
    "radarscreen/UKRadarScreen.cpp"
    "radarscreen/UKRadarScreen.h"
        radarscreen/RadarRenderableInterface.cpp radarscreen/ConfigurableDisplayInterface.cpp radarscreen/MenuToggleableDisplayInterface.h radarscreen/ToggleDisplayFromMenu.cpp radarscreen/ToggleDisplayFromMenu.h radarscreen/MenuToggleableDisplayFactory.cpp radarscreen/MenuToggleableDisplayFactory.h radarscreen/ScreenObjectInterface.cpp radarscreen/ScreenObjectInterface.h)
source_group("src\\radarscreen" FILES ${src__radarscreen})

set(src__regional
    "regional/RegionalPressure.h"
    "regional/RegionalPressure.cpp"
    "regional/RegionalPressureConfigurationDialog.cpp"
    "regional/RegionalPressureConfigurationDialog.h"
    "regional/RegionalPressureManager.cpp"
    "regional/RegionalPressureManager.h"
    "regional/RegionalPressureManagerFactory.cpp"
    "regional/RegionalPressureManagerFactory.h"
    "regional/RegionalPressureModule.cpp"
    "regional/RegionalPressureModule.h"
    "regional/RegionalPressureRenderedItem.h"
    "regional/RegionalPressureRenderer.cpp"
    "regional/RegionalPressureRenderer.h"
    "regional/RegionalPressureRendererConfiguration.cpp"
    "regional/RegionalPressureRendererConfiguration.h"
        regional/RegionalPressureRenderedItem.cpp)
source_group("src\\regional" FILES ${src__regional})

set(src__releases
    "releases/ApproveDepartureReleaseDialog.cpp"
    "releases/ApproveDepartureReleaseDialog.h"
    "releases/CompareDepartureReleases.cpp"
    "releases/CompareDepartureReleases.h"
    "releases/CompareEnrouteReleaseTypes.cpp"
    "releases/CompareEnrouteReleaseTypes.h"
    "releases/DepartureReleaseColours.h"
    "releases/DepartureReleaseCountdownColours.cpp"
    "releases/DepartureReleaseCountdownColours.h"
    "releases/DepartureReleaseEventHandler.cpp"
    "releases/DepartureReleaseEventHandler.h"
    "releases/DepartureReleaseRequest.cpp"
    "releases/DepartureReleaseRequest.h"
    "releases/DepartureReleaseRequestView.cpp"
    "releases/DepartureReleaseRequestView.h"
    "releases/EnrouteRelease.h"
    "releases/EnrouteReleaseEventHandler.cpp"
    "releases/EnrouteReleaseEventHandler.h"
    "releases/EnrouteReleaseType.h"
    "releases/EnrouteReleaseTypesSerializer.cpp"
    "releases/EnrouteReleaseTypesSerializer.h"
    "releases/ReleaseModule.cpp"
    "releases/ReleaseModule.h"
    "releases/RequestDepartureReleaseDialog.cpp"
    "releases/RequestDepartureReleaseDialog.h"
    releases/EnrouteRelease.cpp releases/EnrouteReleaseType.cpp
    releases/RejectDepartureReleaseDialog.cpp releases/RejectDepartureReleaseDialog.h
    releases/ReleaseApprovalRemarksUserMessage.cpp releases/ReleaseApprovalRemarksUserMessage.h
    releases/ReleaseRejectionRemarksUserMessage.cpp releases/ReleaseRejectionRemarksUserMessage.h)
source_group("src\\releases" FILES ${src__releases})

set(src__runway
        runway/Runway.cpp runway/Runway.h
        runway/RunwayCollection.cpp runway/RunwayCollection.h
        runway/RunwayCollectionFactory.cpp runway/RunwayCollectionFactory.h
        runway/RunwayModule.cpp runway/RunwayModule.h)
source_group("src\\runway" FILES ${src__runway})

set(src__sectorfile
    "sectorfile/Runway.cpp"
    "sectorfile/Runway.h"
    "sectorfile/RunwayCollection.cpp"
    "sectorfile/RunwayCollection.h"
    "sectorfile/SectorFileBootstrap.cpp"
    "sectorfile/SectorFileBootstrap.h"
    "sectorfile/SectorFileCoordinates.cpp"
    "sectorfile/SectorFileCoordinates.h"
    "sectorfile/SectorFileProviderInterface.h"
)
source_group("src\\sectorfile" FILES ${src__sectorfile})

set(src__selcal
        selcal/SelcalParser.cpp selcal/SelcalParser.h
        selcal/ParsedSelcal.cpp selcal/ParsedSelcal.h selcal/SelcalTagItem.cpp selcal/SelcalTagItem.h selcal/SelcalModule.cpp selcal/SelcalModule.h)
source_group("src\\selcal" FILES ${src__selcal})

set(src__sid
    "sid/SidCollection.cpp"
    "sid/SidCollection.h"
    "sid/SidCollectionFactory.cpp"
    "sid/SidCollectionFactory.h"
    "sid/SidModule.cpp"
    "sid/SidModule.h"
    "sid/StandardInstrumentDeparture.cpp"
    "sid/StandardInstrumentDeparture.h"
    sid/FlightplanSidMapper.cpp sid/FlightplanSidMapper.h
    sid/SidMapperInterface.h)
source_group("src\\sid" FILES ${src__sid})

set(src__squawk
    "squawk/ApiSquawkAllocationHandler.cpp"
    "squawk/ApiSquawkAllocationHandler.h"
    "squawk/SquawkAssignment.cpp"
    "squawk/SquawkAssignment.h"
    "squawk/SquawkEventHandler.cpp"
    "squawk/SquawkEventHandler.h"
    "squawk/SquawkGenerator.cpp"
    "squawk/SquawkGenerator.h"
    "squawk/SquawkModule.cpp"
    "squawk/SquawkModule.h"
    "squawk/SquawkRequest.cpp"
    "squawk/SquawkRequest.h"
)
source_group("src\\squawk" FILES ${src__squawk})

set(src__srd
    "srd/SrdModule.cpp"
    "srd/SrdModule.h"
    "srd/SrdSearchDialog.cpp"
    "srd/SrdSearchDialog.h"
    "srd/SrdSearchHandler.cpp"
    "srd/SrdSearchHandler.h"
    srd/ContainsFreeRouteAirspace.cpp srd/ContainsFreeRouteAirspace.h)
source_group("src\\srd" FILES ${src__srd})

set(src__stands
    "stands/CompareStands.cpp"
    "stands/CompareStands.h"
    "stands/Stand.h"
    "stands/StandEventHandler.cpp"
    "stands/StandEventHandler.h"
    "stands/StandModule.cpp"
    "stands/StandModule.h"
    "stands/StandSerializer.cpp"
    "stands/StandSerializer.h"
    "stands/StandAssignedMessage.cpp"
    "stands/StandUnassignedMessage.cpp"
)
source_group("src\\stands" FILES ${src__stands})

set(src__tag
    "tag/TagData.cpp"
    "tag/TagData.h"
    "tag/TagFunction.cpp"
    "tag/TagFunction.h"
    "tag/TagItemCollection.cpp"
    "tag/TagItemCollection.h"
    "tag/TagItemInterface.h"
    "tag/TagItemInterface.cpp"
)
source_group("src\\tag" FILES ${src__tag})

set(src__time
    "time/ParseTimeStrings.cpp"
    "time/ParseTimeStrings.h"
    "time/SystemClock.cpp"
    "time/SystemClock.h"
)
source_group("src\\time" FILES ${src__time})

set(src__timedevent
    "timedevent/AbstractTimedEvent.h"
    "timedevent/AbstractTimedEvent.cpp"
    "timedevent/TimedEventCollection.cpp"
    "timedevent/TimedEventCollection.h"
)
source_group("src\\timedevent" FILES ${src__timedevent})

set(src__timer
    "timer/TimerDisplay.cpp"
    "timer/TimerDisplay.h"
)
source_group("src\\timer" FILES ${src__timer})

set(src__wake
    "wake/CacheItem.h"
    "wake/WakeCategoryEventHandler.cpp"
    "wake/WakeCategoryEventHandler.h"
    "wake/WakeModule.cpp"
    "wake/WakeModule.h"
    wake/WakeScheme.cpp wake/WakeScheme.h
    wake/WakeCategory.cpp wake/WakeCategory.h
    wake/WakeCategoryFactory.cpp wake/WakeCategoryFactory.h
    wake/DepartureWakeInterval.cpp wake/DepartureWakeInterval.h
    wake/DepartureWakeIntervalFactory.cpp wake/DepartureWakeIntervalFactory.h
    wake/WakeSchemeFactory.cpp wake/WakeSchemeFactory.h wake/WakeSchemeCollection.cpp
    wake/WakeSchemeCollection.h
    wake/WakeSchemeCollectionFactory.cpp
    wake/WakeSchemeCollectionFactory.h
    wake/WakeCategoryMapperInterface.h
    wake/FlightplanWakeCategoryMapper.cpp wake/FlightplanWakeCategoryMapper.h
    wake/WakeCalculatorDisplay.cpp wake/WakeCalculatorDisplay.h
    wake/WakeCalculatorOptions.cpp wake/WakeCalculatorOptions.h
    wake/LeadWakeCallsignProvider.cpp wake/LeadWakeCallsignProvider.h
    wake/FollowingWakeCallsignProvider.cpp wake/FollowingWakeCallsignProvider.h
    wake/WakeSchemeProvider.cpp wake/WakeSchemeProvider.h
    wake/WakeIntervalFormatter.cpp wake/WakeIntervalFormatter.h
    wake/ArrivalWakeInterval.cpp wake/ArrivalWakeInterval.h
    wake/ArrivalWakeIntervalFactory.cpp wake/ArrivalWakeIntervalFactory.h
    wake/WakeIntervalInterface.h wake/WakeCategoryMapperCollection.cpp wake/WakeCategoryMapperCollection.h wake/WakeCategoryMapperCollectionFactory.cpp wake/WakeCategoryMapperCollectionFactory.h)
source_group("src\\wake" FILES ${src__wake})

set(ALL_FILES
    ${resource}
    ${src__aircraft}
    ${src__airfield}
    ${src__api}
    ${src__approach}
    ${src__bootstrap}
    ${src__command}
    ${src__components}
    ${src__controller}
    ${src__countdown}
    ${src__datablock}
    ${src__departure}
    ${src__dependency}
    ${src__euroscope}
    ${src__flightinformationservice}
    ${src__flightplan}
    ${src__flightrule}
    ${src__geometry}
    ${src__graphics}
    ${src__handoff}
    ${src__headings}
    ${src__historytrail}
    ${src__hold}
    ${src__initialaltitude}
    ${src__initialheading}
    ${src__integration}
    ${src__intention}
    ${src__list}
    ${src__login}
    ${src__mapping}
    ${src__message}
    ${src__metar}
    ${src__minstack}
    ${src__missedapproach}
    ${src__navaids}
    ${src__notifications}
    ${src__number}
    ${src__oceanic}
    ${src__offblock}
    ${src__ownership}
    ${src__plugin}
    ${src__prenote}
    ${src__push}
    ${src__radarscreen}
    ${src__regional}
    ${src__releases}
    ${src__runway}
    ${src__sectorfile}
    ${src__selcal}
    ${src__sid}
    ${src__squawk}
    ${src__srd}
    ${src__stands}
    ${src__tag}
    ${src__time}
    ${src__timedevent}
    ${src__timer}
    ${src__wake})

################################################################################
# Source Files
################################################################################
set_source_files_properties(ALL_FILES PROPERTIES COMPILE_FLAGS "-include pch/pch.h")

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

target_precompile_headers(${PROJECT_NAME} PRIVATE "pch/pch.h")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE UKControllerPlugin)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
#############################################1###################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "UKControllerPluginCore"
    TARGET_NAME_RELEASE "UKControllerPluginCore"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<CONFIG:Release>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../../resource;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../third_party"
)

################################################################################
# Link directories for cURL
################################################################################
target_link_directories(
    ${PROJECT_NAME} PUBLIC
    $ENV{CURL_DEBUG_LIBRARYDIR}
    $ENV{CURL_LIBRARYDIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG;"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG;"
    ">"
    "WIN32;"
    "_WINDOWS;"
    "_USRDLL;"
    "UKCONTROLLERPLUGIN_EXPORTS;"
    "CURL_STATICLIB;"
    ";"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od
        >
        $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /Gy
        >
        /std:c++20;
        /sdl;
        /W4;
        /WX;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        /Zm200;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
        -Wno-unused-parameter # Lots of interfaces don't use everything
        -Wno-missing-field-initializers # Windows has loads of this sadly
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG:FASTLINK;
            /INCREMENTAL
            -flto=thin
            >
        $<$<CONFIG:Release>:
            /DEBUG;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /NODEFAULTLIB:LIBCMT;
        /SUBSYSTEM:WINDOWS
        /ALLOWISOLATION
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    UKControllerPluginUtils
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    UKControllerPluginUtils
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
        "libcurl_a_debug"
    ">"
    "$<$<CONFIG:Release>:"
        "libcurl_a"
    ">"
    "kernel32;"
    "user32;"
    "gdi32;"
    "winspool;"
    "Ws2_32;"
    "Wldap32;"
    "normaliz;"
    "crypt32;"
    "comdlg32;"
    "advapi32;"
    "shell32;"
    "ole32;"
    "oleaut32;"
    "uuid;"
    "odbc32;"
    "odbccp32;"
    "EuroScopePlugInDll;"
    "Winmm;"
    "Dwmapi;"
    "gdiplus;"
    "comctl32"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

# Post-build copy the EuroScope binary
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/EuroScopePlugInDll.dll" "${PROJECT_BINARY_DIR}/bin/EuroScopePlugInDll.dll"
    COMMENT "Copied EuroScope shared library to ${PROJECT_BINARY_DIR}/bin/EuroScopePlugInDll.dll"
)

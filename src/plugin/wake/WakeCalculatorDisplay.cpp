#include "ArrivalWakeInterval.h"
#include "DepartureWakeInterval.h"
#include "WakeCalculatorDisplay.h"
#include "WakeCategory.h"
#include "WakeCategoryMapperInterface.h"
#include "WakeCalculatorOptions.h"
#include "WakeIntervalFormatter.h"
#include "components/ClickableArea.h"
#include "components/CollapsibleWindowTitleBar.h"
#include "euroscope/EuroscopePluginLoopbackInterface.h"
#include "euroscope/EuroscopeRadarLoopbackInterface.h"
#include "euroscope/UserSetting.h"
#include "graphics/FontManager.h"
#include "graphics/GdiGraphicsInterface.h"
#include "graphics/StringFormatManager.h"
#include "helper/HelperFunctions.h"
#include "list/PopupListInterface.h"

namespace UKControllerPlugin::Wake {

    WakeCalculatorDisplay::WakeCalculatorDisplay(
        std::shared_ptr<WakeCalculatorOptions> options,
        std::shared_ptr<List::PopupListInterface> leadCallsignSelector,
        std::shared_ptr<List::PopupListInterface> followCallsignSelector,
        std::shared_ptr<List::PopupListInterface> wakeSchemeSelector,
        Euroscope::EuroscopePluginLoopbackInterface& plugin,
        int screenObjectId)
        : options(std::move(options)), leadCallsignSelector(std::move(leadCallsignSelector)),
          followCallsignSelector(std::move(followCallsignSelector)), wakeSchemeSelector(std::move(wakeSchemeSelector)),
          plugin(plugin), titleBar(Components::CollapsibleWindowTitleBar::Create(
                              L"Wake Turbulence Calculator",
                              TitleBarArea(),
                              [this]() -> bool { return this->contentCollapsed; },
                              screenObjectId)),
          backgroundBrush(std::make_shared<Gdiplus::SolidBrush>(BACKGROUND_COLOUR)),
          textBrush(std::make_shared<Gdiplus::SolidBrush>(TEXT_COLOUR)),
          resultBrush(std::make_shared<Gdiplus::SolidBrush>(RESULT_COLOUR)),
          dividingLinePen(std::make_shared<Gdiplus::Pen>(TEXT_COLOUR)),
          leadClickspot(Components::ClickableArea::Create(leadTextArea, screenObjectId, "leadcallsign", false)),
          followingClickspot(
              Components::ClickableArea::Create(followingTextArea, screenObjectId, "followcallsign", false)),
          schemeClickspot(Components::ClickableArea::Create(schemeTextArea, screenObjectId, "scheme", false)),
          intermediateClickspot(
              Components::ClickableArea::Create(intermediateTextArea, screenObjectId, "intermediate", false)),
          departureArrivalClickspot(
              Components::ClickableArea::Create(departureArrivaTextArea, screenObjectId, "mode", false))
    {
        this->Move({DEFAULT_WINDOW_POSITION.x, DEFAULT_WINDOW_POSITION.y, 0, 0}, "");
    }

    auto WakeCalculatorDisplay::IsVisible() const -> bool
    {
        return this->visible;
    }

    void WakeCalculatorDisplay::LeftClick(
        Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
        int objectId,
        const std::string& objectDescription,
        POINT mousePos,
        RECT itemArea)
    {
        if (objectDescription == "leadcallsign") {
            leadCallsignSelector->Trigger(mousePos);
            return;
        }

        if (objectDescription == "followcallsign") {
            followCallsignSelector->Trigger(mousePos);
            return;
        }

        if (objectDescription == "scheme") {
            wakeSchemeSelector->Trigger(mousePos);
            return;
        }

        if (objectDescription == "intermediate") {
            options->Intermediate(!options->Intermediate());
            return;
        }

        if (objectDescription == "mode") {
            options->ToggleArrivals();
            options->LeadAircraft("");
            options->FollowingAircraft("");
            return;
        }

        if (objectDescription == "collapseButton") {
            this->contentCollapsed = !this->contentCollapsed;
            return;
        }

        if (objectDescription == "closeButton") {
            this->visible = false;
            return;
        }
    }

    void WakeCalculatorDisplay::Move(RECT position, std::string objectDescription)
    {
        this->windowPosition = {position.left, position.top};
        this->contentArea = WindowContentArea();
        this->titleBar->WithPosition(TitleBarArea());

        // Scheme
        this->schemeStaticArea = {TEXT_INSET, TitleBarArea().GetBottom() + TEXT_INSET, 60, 20};
        this->schemeTextArea = {
            this->schemeStaticArea.GetRight() + TEXT_INSET, TitleBarArea().GetBottom() + TEXT_INSET, 75, 20};
        this->schemeClickspot->WithPosition(this->schemeTextArea);

        // Intermediate
        this->intermediateStaticArea = {schemeTextArea.GetRight() + TEXT_INSET, schemeStaticArea.GetTop(), 105, 20};
        this->intermediateTextArea = {
            intermediateStaticArea.GetRight() + TEXT_INSET, schemeStaticArea.GetTop(), 30, 20};
        this->intermediateClickspot->WithPosition(this->intermediateTextArea);

        // Departure Arrival Mode
        this->departureArrivalStaticArea = {TEXT_INSET, schemeStaticArea.GetBottom() + TEXT_INSET, 45, 20};
        this->departureArrivaTextArea = {
            departureArrivalStaticArea.GetRight() + TEXT_INSET, schemeStaticArea.GetBottom() + TEXT_INSET, 110, 20};
        this->departureArrivalClickspot->WithPosition(this->departureArrivaTextArea);

        // Lead
        this->leadStaticArea = {TEXT_INSET, departureArrivalStaticArea.GetBottom() + TEXT_INSET, 45, 20};
        this->leadTextArea = {
            leadStaticArea.GetRight() + TEXT_INSET, departureArrivalStaticArea.GetBottom() + TEXT_INSET, 110, 20};
        this->leadClickspot->WithPosition(this->leadTextArea);

        // Following
        this->followingStaticArea = {leadTextArea.GetRight() + TEXT_INSET, leadStaticArea.GetTop(), 60, 20};
        this->followingTextArea = {followingStaticArea.GetRight() + TEXT_INSET, leadStaticArea.GetTop(), 110, 20};
        this->followingClickspot->WithPosition(this->followingTextArea);

        // Dividing line
        this->dividingLineStart = Gdiplus::Point(0, followingTextArea.GetBottom() + TEXT_INSET);
        this->dividingLineEnd = Gdiplus::Point(WINDOW_WIDTH, followingTextArea.GetBottom() + TEXT_INSET);

        // Category comparison
        this->comparisonTextArea = {TEXT_INSET, dividingLineEnd.Y + TEXT_INSET, WINDOW_WIDTH - (2 * TEXT_INSET), 20};

        // Calculation result
        this->calculationResultArea = {TEXT_INSET, comparisonTextArea.GetBottom(), WINDOW_WIDTH - (2 * TEXT_INSET), 60};
    }

    void WakeCalculatorDisplay::Render(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        graphics.Translated(windowPosition.x, windowPosition.y, [&graphics, &radarScreen, this]() {
            // Draw the content if not collapsed
            if (!this->contentCollapsed) {
                graphics.FillRect(this->contentArea, *backgroundBrush);
                this->RenderScheme(graphics, radarScreen);
                this->RenderIntermediate(graphics, radarScreen);
                this->RenderMode(graphics, radarScreen);
                this->RenderLead(graphics, radarScreen);
                this->RenderFollowing(graphics, radarScreen);
                this->RenderDividingLine(graphics);
                this->RenderSeparationRequirement(graphics);
            }

            // Do title bar, so it's always on top.
            titleBar->Draw(graphics, radarScreen);
        });
    }

    void WakeCalculatorDisplay::ResetPosition()
    {
        this->Move({DEFAULT_WINDOW_POSITION.x, DEFAULT_WINDOW_POSITION.y, 0, 0}, "");
    }

    void WakeCalculatorDisplay::AsrLoadedEvent(Euroscope::UserSetting& userSetting)
    {
        this->Move(
            {userSetting.GetIntegerEntry(ASR_KEY_X_POS, DEFAULT_WINDOW_POSITION.x),
             userSetting.GetIntegerEntry(ASR_KEY_Y_POS, DEFAULT_WINDOW_POSITION.y),
             0,
             0},
            "");
        this->visible = userSetting.GetBooleanEntry(ASR_KEY_VISIBILITY, false);
        this->contentCollapsed = userSetting.GetBooleanEntry(ASR_KEY_COLLAPSED, false);
    }

    void WakeCalculatorDisplay::AsrClosingEvent(Euroscope::UserSetting& userSetting)
    {
        userSetting.Save(ASR_KEY_X_POS, ASR_DESCRIPTION_X_POS, windowPosition.x);
        userSetting.Save(ASR_KEY_Y_POS, ASR_DESCRIPTION_Y_POS, windowPosition.y);
        userSetting.Save(ASR_KEY_VISIBILITY, ASR_DESCRIPTION_VISIBILITY, visible);
        userSetting.Save(ASR_KEY_COLLAPSED, ASR_DESCRIPTION_COLLAPSED, contentCollapsed);
    }

    auto WakeCalculatorDisplay::TitleBarArea() -> Gdiplus::Rect
    {
        return {0, 0, WINDOW_WIDTH, TITLE_BAR_HEIGHT};
    }

    auto WakeCalculatorDisplay::WindowContentArea() -> Gdiplus::Rect
    {
        return {0, TITLE_BAR_HEIGHT, WINDOW_WIDTH, CONTENT_HEIGHT};
    }

    void WakeCalculatorDisplay::RenderScheme(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        graphics.DrawString(
            L"Scheme:",
            schemeStaticArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        graphics.DrawString(
            HelperFunctions::ConvertToWideString(options->Scheme()),
            schemeTextArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        this->schemeClickspot->Apply(graphics, radarScreen);
    }

    void WakeCalculatorDisplay::RenderMode(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        graphics.DrawString(
            L"Mode:",
            departureArrivalStaticArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        graphics.DrawString(
            options->Arrivals() ? L"Arrival" : L"Departure",
            departureArrivaTextArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        this->departureArrivalClickspot->Apply(graphics, radarScreen);
    }

    void WakeCalculatorDisplay::RenderLead(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        const auto lead = options->LeadAircraft();
        graphics.DrawString(
            L"Lead:",
            leadStaticArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        graphics.DrawString(
            HelperFunctions::ConvertToWideString(lead.empty() ? "--" : lead),
            leadTextArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        this->leadClickspot->Apply(graphics, radarScreen);
    }

    void WakeCalculatorDisplay::RenderFollowing(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        const auto following = options->FollowingAircraft();
        graphics.DrawString(
            L"Follow:",
            followingStaticArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        graphics.DrawString(
            HelperFunctions::ConvertToWideString(following.empty() ? "--" : following),
            followingTextArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        this->followingClickspot->Apply(graphics, radarScreen);
    }

    void WakeCalculatorDisplay::RenderIntermediate(
        Windows::GdiGraphicsInterface& graphics, Euroscope::EuroscopeRadarLoopbackInterface& radarScreen)
    {
        graphics.DrawString(
            L"Intermediate:",
            intermediateStaticArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        graphics.DrawString(
            options->Intermediate() ? L"Yes" : L"No",
            intermediateTextArea,
            *textBrush,
            Graphics::StringFormatManager::Instance().GetLeftAlign(),
            Graphics::FontManager::Instance().GetDefault());
        this->intermediateClickspot->Apply(graphics, radarScreen);
    }

    void WakeCalculatorDisplay::RenderDividingLine(Windows::GdiGraphicsInterface& graphics)
    {
        graphics.DrawLine(*dividingLinePen, dividingLineStart, dividingLineEnd);
    }

    void WakeCalculatorDisplay::RenderSeparationRequirement(Windows::GdiGraphicsInterface& graphics)
    {
        // Check for the mapper and required flightplans
        const auto mapper = options->SchemeMapper();
        const auto leadFlightplan = plugin.GetFlightplanForCallsign(options->LeadAircraft());
        const auto followingFlightplan = plugin.GetFlightplanForCallsign(options->FollowingAircraft());
        if (options->SchemeMapper() == nullptr || leadFlightplan == nullptr || followingFlightplan == nullptr) {
            graphics.DrawString(
                L"--",
                calculationResultArea,
                *resultBrush,
                Graphics::StringFormatManager::Instance().GetCentreAlign(),
                Graphics::FontManager::Instance().Get(16));
            return;
        }

        // Check for the categories;
        const auto leadCategory = mapper->MapForFlightplan(*leadFlightplan);
        const auto followingCategory = mapper->MapForFlightplan(*followingFlightplan);
        if (leadCategory == nullptr || followingCategory == nullptr) {
            graphics.DrawString(
                L"--",
                calculationResultArea,
                *resultBrush,
                Graphics::StringFormatManager::Instance().GetCentreAlign(),
                Graphics::FontManager::Instance().Get(16));
            return;
        }

        // Summarise the WTC comparisons
        const std::wstring categoryComparison = HelperFunctions::ConvertToWideString(leadCategory->Code()) +
                                                L" followed by " +
                                                HelperFunctions::ConvertToWideString(followingCategory->Code()) +
                                                (options->Intermediate() ? L" (intermediate)" : L"");

        graphics.DrawString(categoryComparison, comparisonTextArea, *textBrush);

        // Check for intervals and display if present
        const auto interval = RelevantInterval(*leadCategory, *followingCategory, options->Intermediate());
        if (interval == nullptr) {
            graphics.DrawString(
                L"N/A",
                calculationResultArea,
                *resultBrush,
                Graphics::StringFormatManager::Instance().GetCentreAlign(),
                Graphics::FontManager::Instance().Get(16));
            return;
        }

        graphics.DrawString(
            FormatInterval(*interval),
            calculationResultArea,
            *resultBrush,
            Graphics::StringFormatManager::Instance().GetCentreAlign(),
            Graphics::FontManager::Instance().Get(16));
    }

    auto WakeCalculatorDisplay::RelevantInterval(
        const WakeCategory& lead, const WakeCategory& following, bool intermediate) const
        -> std::shared_ptr<WakeIntervalInterface>
    {
        return options->Departures()
                   ? static_cast<std::shared_ptr<WakeIntervalInterface>>(
                         lead.DepartureInterval(following, intermediate))
                   : static_cast<std::shared_ptr<WakeIntervalInterface>>(lead.ArrivalInterval(following));
    }

    auto WakeCalculatorDisplay::Position() const -> const POINT&
    {
        return windowPosition;
    }

    auto WakeCalculatorDisplay::MenuItem() const -> std::string
    {
        return "Display Wake Turbulence Calculator";
    }

    void WakeCalculatorDisplay::Toggle()
    {
        this->visible = !this->visible;
    }

    auto WakeCalculatorDisplay::IsCollapsed() const -> bool
    {
        return this->contentCollapsed;
    }
} // namespace UKControllerPlugin::Wake

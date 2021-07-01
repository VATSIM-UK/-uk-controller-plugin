#include "pch/stdafx.h"
#include "releases/DepartureReleaseDecisionList.h"
#include "releases/DepartureReleaseRequest.h"
#include "releases/DepartureReleaseEventHandler.h"
#include "euroscope/EuroscopePluginLoopbackInterface.h"
#include "euroscope/EuroscopeRadarLoopbackInterface.h"
#include "euroscope/UserSetting.h"
#include "graphics/GdiGraphicsInterface.h"
#include "helper/HelperFunctions.h"
#include "components/TitleBar.h"
#include "components/Button.h"
#include "components/StandardButtons.h"
#include "components/ClickableArea.h"
#include "components/BrushSwitcher.h"
#include "controller/ControllerPosition.h"
#include "controller/ControllerPositionCollection.h"

namespace UKControllerPlugin {

    namespace Euroscope {
        class EuroscopePluginLoopbackInterface;
    } // namespace Euroscope

    namespace Releases {

        DepartureReleaseDecisionList::DepartureReleaseDecisionList(
            DepartureReleaseEventHandler& handler,
            Euroscope::EuroscopePluginLoopbackInterface& plugin,
            const Controller::ControllerPositionCollection& controllers,
            const int screenObjectId
        ): controllers(controllers), handler(handler), plugin(plugin), textBrush(Gdiplus::Color(227, 227, 227)),
           screenObjectId(screenObjectId),
           visible(false), contentCollapsed(false)
        {
            this->brushSwitcher = Components::BrushSwitcher::Create(
                    std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(197, 129, 214)),
                    std::chrono::seconds(2)
                )
                ->AdditionalBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(255, 97, 93)));

            this->titleBar = Components::TitleBar::Create(
                                 L"Departure Release Requests",
                                 {0, 0, this->titleBarWidth, this->titleBarHeight}
                             )
                             ->WithDrag(this->screenObjectId)
                             ->WithBorder(std::make_shared<Gdiplus::Pen>(Gdiplus::Color(227, 227, 227)))
                             ->WithBackgroundBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(197, 129, 214)))
                             ->WithTextBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(227, 227, 227)));

            this->closeButton = Components::Button::Create(
                {325, 5, 10, 10},
                this->screenObjectId,
                "closeButton",
                Components::CloseButton()
            );

            this->collapseButton = Components::Button::Create(
                {310, 5, 10, 10},
                this->screenObjectId,
                "collapseButton",
                Components::CollapseButton([this]() -> bool { return this->contentCollapsed; })
            );
        }

        void DepartureReleaseDecisionList::LeftClick(
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen,
            int objectId,
            std::string objectDescription,
            POINT mousePos,
            RECT itemArea
        )
        {
            if (objectDescription == "collapseButton") {
                this->contentCollapsed = !this->contentCollapsed;
                return;
            }

            if (objectDescription == "closeButton") {
                this->visible = false;
                return;
            }

            auto fp = this->plugin.GetFlightplanForCallsign(objectDescription);
            auto rt = this->plugin.GetRadarTargetForCallsign(objectDescription);
            if (!fp || !rt) {
                return;
            }

            this->handler.OpenDecisionMenu(*fp, *rt, "", mousePos);
        }

        void DepartureReleaseDecisionList::RightClick(
            int objectId, std::string objectDescription,
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen
        )
        {
            // Do nothing
        }

        bool DepartureReleaseDecisionList::IsVisible() const
        {
            return this->visible;
        }

        void DepartureReleaseDecisionList::Move(RECT position, std::string objectDescription)
        {
            this->position = {
                static_cast<Gdiplus::REAL>(position.left),
                static_cast<Gdiplus::REAL>(position.top)
            };
        }

        void DepartureReleaseDecisionList::Render(
            Windows::GdiGraphicsInterface& graphics,
            Euroscope::EuroscopeRadarLoopbackInterface& radarScreen
        )
        {
            auto decisions = this->handler.GetReleasesRequiringUsersDecision();
            if (decisions.empty()) {
                this->titleBar->WithBackgroundBrush(this->brushSwitcher->Base());
            } else {
                this->titleBar->WithBackgroundBrush(this->brushSwitcher->Next());
            }

            // Translate to content position
            graphics.Translated(
                this->position.X,
                this->position.Y + this->titleBarHeight,
                [this, &graphics, &radarScreen, &decisions]
                {
                    if (this->contentCollapsed) {
                        return;
                    }

                    // Draw column headers
                    graphics.DrawString(L"Callsign", this->callsignColumnHeader, this->textBrush);
                    graphics.DrawString(L"Controller", this->controllerColumnHeader, this->textBrush);
                    graphics.DrawString(L"Dept", this->airportColumnHeader, this->textBrush);
                    graphics.DrawString(L"SID", this->sidColumnHeader, this->textBrush);

                    // Draw each aircraft that we care about
                    Gdiplus::Rect callsignColumn = this->callsignColumnHeader;
                    Gdiplus::Rect controllerColumn = this->controllerColumnHeader;
                    Gdiplus::Rect airportColumn = this->airportColumnHeader;
                    Gdiplus::Rect sidColumn = this->sidColumnHeader;

                    // Draw each decision
                    for (const auto decision : decisions) {
                        auto fp = this->plugin.GetFlightplanForCallsign(decision->Callsign());
                        if (!fp) {
                            continue;
                        }

                        // Shift the cols
                        callsignColumn.Y += 25;
                        controllerColumn.Y += 25;
                        airportColumn.Y += 25;
                        sidColumn.Y += 25;

                        graphics.DrawString(
                            HelperFunctions::ConvertToWideString(decision->Callsign()),
                            callsignColumn,
                            this->textBrush
                        );
                        std::shared_ptr<Components::ClickableArea> callsignClickspot =
                            Components::ClickableArea::Create(
                                callsignColumn,
                                this->screenObjectId,
                                decision->Callsign(),
                                false
                            );
                        callsignClickspot->Apply(graphics, radarScreen);

                        const std::wstring controller = HelperFunctions::ConvertToWideString(
                            this->controllers.FetchPositionById(decision->RequestingController())->GetCallsign()
                        );
                        graphics.DrawString(
                            controller,
                            controllerColumn,
                            this->textBrush
                        );

                        graphics.DrawString(
                            HelperFunctions::ConvertToWideString(fp->GetOrigin()),
                            airportColumn,
                            this->textBrush
                        );

                        graphics.DrawString(
                            HelperFunctions::ConvertToWideString(fp->GetSidName()),
                            sidColumn,
                            this->textBrush
                        );
                    }
                }
            );

            // Translate to window position
            graphics.Translated(
                this->position.X,
                this->position.Y,
                [this, &graphics, &radarScreen]
                {
                    this->titleBar->Draw(graphics, radarScreen);
                    this->closeButton->Draw(graphics, radarScreen);
                    this->collapseButton->Draw(graphics, radarScreen);
                }
            );
        }

        void DepartureReleaseDecisionList::ResetPosition()
        {
            this->Move({100, 100, 200, 200}, "");
        }

        void DepartureReleaseDecisionList::AsrLoadedEvent(
            Euroscope::UserSetting& userSetting
        )
        {
            this->visible = userSetting.GetBooleanEntry(
                GetAsrKey("Visible"),
                false
            );

            this->contentCollapsed = userSetting.GetBooleanEntry(
                GetAsrKey("ContentCollapsed"),
                false
            );

            this->Move(
                {
                    userSetting.GetIntegerEntry(
                        GetAsrKey("XPosition"),
                        100
                    ),
                    userSetting.GetIntegerEntry(
                        GetAsrKey("YPosition"),
                        100
                    ),
                    0,
                    0
                },
                ""
            );
        }

        void DepartureReleaseDecisionList::AsrClosingEvent(
            Euroscope::UserSetting& userSetting
        )
        {
            userSetting.Save(
                GetAsrKey("Visible"),
                GetAsrDescription("Visible"),
                this->visible
            );

            userSetting.Save(
                GetAsrKey("ContentCollapsed"),
                GetAsrDescription("Content Collapsed"),
                this->contentCollapsed
            );

            userSetting.Save(
                GetAsrKey("XPosition"),
                GetAsrDescription("X Position"),
                static_cast<int>(this->position.X)
            );

            userSetting.Save(
                GetAsrKey("YPosition"),
                GetAsrDescription("Y Position"),
                static_cast<int>(this->position.Y)
            );
        }

        void DepartureReleaseDecisionList::ToggleVisible()
        {
            this->visible = !this->visible;
        }

        bool DepartureReleaseDecisionList::ContentCollapsed() const
        {
            return this->contentCollapsed;
        }

        Gdiplus::PointF DepartureReleaseDecisionList::Position() const
        {
            return this->position;
        }

        std::string DepartureReleaseDecisionList::GetAsrKey(std::string item)
        {
            return "departureReleaseRequestList" + item;
        }

        std::string DepartureReleaseDecisionList::GetAsrDescription(std::string description)
        {
            return "Departure Release Request List " + description;
        }
    } // namespace Releases
} // namespace UKControllerPlugin

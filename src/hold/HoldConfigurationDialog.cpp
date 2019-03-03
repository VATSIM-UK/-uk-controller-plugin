#include "pch/stdafx.h"
#include "hold/HoldConfigurationDialog.h"
#include "hold/HoldDisplayFunctions.h"
#include "hold/HoldWindowManager.h"
#include "hold/HoldSelectionMenu.h"
#include "hold/HoldProfileManager.h"

using UKControllerPlugin::Hold::ConvertToTchar;
using UKControllerPlugin::Hold::GetSelectedHoldProfileText;
using UKControllerPlugin::Hold::HoldWindowManager;
using UKControllerPlugin::Hold::HoldSelectionMenu;
using UKControllerPlugin::Hold::HoldProfileManager;

namespace UKControllerPlugin {
    namespace Hold {

        HoldConfigurationDialog::HoldConfigurationDialog(
            HoldWindowManager & windowManager,
            HoldSelectionMenu & holdSelectionMenu,
            HoldProfileManager & holdProfileManager
        )
            : windowManager(windowManager), holdSelectionMenu(holdSelectionMenu),
            holdProfileManager(holdProfileManager)
        {

        }

        /*
            Add a hold to the dialog.
        */
        bool HoldConfigurationDialog::AddHold(UKControllerPlugin::Hold::HoldingData hold)
        {
            if (!this->holds.insert(hold).second) {
                LogWarning("Attempted to add duplicate hold to dialog " + std::to_string(hold.identifier));
                return false;
            }
            
            return true;
        }

        /*
            Return the number of holds.
        */
        size_t HoldConfigurationDialog::CountHolds(void) const
        {
            return this->holds.size();
        }

        /*
            Private dialog procedure for the hold configuration dialog, should be used
            against a bound instance.
        */
        LRESULT HoldConfigurationDialog::_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            switch (msg) {
                // Initialise
                case WM_INITDIALOG: {

                    // Load the holds
                    SendDlgItemMessage(
                        hwnd,
                        IDC_HOLD_SELECTOR,
                        CB_SETMINVISIBLE,
                        10,
                        0
                    );
                    for (
                        std::set<HoldingData>::const_iterator it = this->holds.cbegin();
                        it != this->holds.cend();
                        ++it
                    ) {
                        HoldingData data = *it;
                        SendDlgItemMessage(
                            hwnd,
                            IDC_HOLD_SELECTOR,
                            CB_ADDSTRING,
                            0,
                            reinterpret_cast<LPARAM>(ConvertToTchar(it->description))
                        );
                    }

                    SendDlgItemMessage(
                        hwnd,
                        IDC_HOLD_SELECTOR,
                        CB_SETCURSEL,
                        0,
                        0
                    );

                    // Load the hold profiles
                    SendDlgItemMessage(
                        hwnd,
                        IDC_HOLD_PROFILE_SELECT,
                        CB_SETMINVISIBLE,
                        10,
                        0
                    );
                    for (
                        HoldProfileManager::HoldProfiles::const_iterator it = this->holdProfileManager.cbegin();
                        it != this->holdProfileManager.cend();
                        ++it
                    ) {
                        SendDlgItemMessage(
                            hwnd,
                            IDC_HOLD_PROFILE_SELECT,
                            CB_ADDSTRING,
                            0,
                            reinterpret_cast<LPARAM>(ConvertToTchar(it->name))
                        );
                    }

                    SendDlgItemMessage(
                        hwnd,
                        IDC_HOLD_PROFILE_SELECT,
                        CB_SETCURSEL,
                        0,
                        0
                    );

                    return TRUE;
                };
                // Buttons pressed
                case WM_COMMAND: {
                    switch (LOWORD(wParam)) {

                        case IDC_HOLD_PROFILE_SELECT: {
                            // We're selecting a new profile for holds
                            if (HIWORD(wParam) == CBN_SELCHANGE) {
                                // Change the hold selection text
                                int selectedIndex = SendDlgItemMessage(
                                    hwnd,
                                    IDC_HOLD_PROFILE_SELECT,
                                    CB_GETCURSEL,
                                    0,
                                    0
                                );

                                HoldProfileManager::HoldProfiles::const_iterator it = 
                                    this->holdProfileManager.cbegin();
                                std::advance(it, selectedIndex);

                                SendDlgItemMessage(
                                    hwnd,
                                    IDC_HOLD_PROFILE_STATIC,
                                    WM_SETTEXT,
                                    NULL,
                                    reinterpret_cast<LPARAM>(GetSelectedHoldProfileText(*it))
                                );

                                // Put the holds from the selected profile in the list
                                SendDlgItemMessage(
                                    hwnd,
                                    IDC_HOLD_LIST,
                                    LB_RESETCONTENT,
                                    NULL,
                                    NULL
                                );

                                this->selectedHolds.clear();
                                for (
                                    std::set<unsigned int>::const_iterator holdIt = it->holds.cbegin();
                                    holdIt != it->holds.cend();
                                    ++holdIt
                                ) {
                                    auto hold = std::find_if(
                                        this->holds.cbegin(),
                                        this->holds.cend(),
                                        [holdIt](const HoldingData & theHold) -> bool {
                                            return *holdIt == theHold.identifier;
                                        }
                                    );

                                    if (hold == this->holds.cend()) {
                                        continue;
                                    }

                                    this->selectedHolds.insert(hold->description);
                                    SendDlgItemMessage(
                                        hwnd,
                                        IDC_HOLD_LIST,
                                        LB_INSERTSTRING,
                                        NULL,
                                        reinterpret_cast<LPARAM>(ConvertToTchar(hold->description))
                                    );
                                }

                                return TRUE;
                            }
                            return DefWindowProc(hwnd, msg, wParam, lParam);
                        }
                        case HOLD_SELECTOR_OK: {
                            // OK clicked, close the window
                            EndDialog(hwnd, wParam);
                            return TRUE;
                        }
                        case IDC_HOLD_ADD: {
                            // Add a hold to the profile list
                            const int selectedIndex = SendDlgItemMessage(
                                hwnd,
                                IDC_HOLD_SELECTOR,
                                CB_GETCURSEL,
                                0,
                                0
                            );
                            std::set<HoldingData, CompareHoldsDescription>::iterator it = this->holds.cbegin();
                            std::advance(it, selectedIndex);

                            if (!this->selectedHolds.insert(it->description).second) {
                                return TRUE;
                            }

                            SendDlgItemMessage(
                                hwnd,
                                IDC_HOLD_LIST,
                                LB_ADDSTRING,
                                NULL,
                                reinterpret_cast<LPARAM>(ConvertToTchar(it->description))
                            );

                            return TRUE;
                        }
                        case IDC_HOLD_REMOVE: {
                            // Remove a hold from the profile list
                            const int selectedIndex = SendDlgItemMessage(
                                hwnd,
                                IDC_HOLD_SELECTOR,
                                LB_GETCURSEL,
                                0,
                                0
                            );

                            SendDlgItemMessage(
                                hwnd,
                                IDC_HOLD_LIST,
                                LB_DELETESTRING,
                                selectedIndex,
                                NULL
                            );
                            return TRUE;
                        }
                        case IDC_HOLD_PROFILE_NEW: {
                            // Creating a new hold profile
                            //std::string profileName =
                            return TRUE;
                        }
                        case IDC_HOLD_SELECT_DISPLAY: {
                            // They want to display the hold profile
                            const int selectedIndex =  SendDlgItemMessage(
                                hwnd,
                                IDC_HOLD_SELECTOR,
                                CB_GETCURSEL,
                                0,
                                0
                            );
                            std::set<HoldingData, CompareHoldsDescription>::iterator it = this->holds.cbegin();
                            std::advance(it, selectedIndex);

                            // Create a hold window and add an item to the hold selection menu
                            this->windowManager.AddWindow(it->identifier);
                            this->holdSelectionMenu.AddHoldToMenu(it->identifier);
                            return TRUE;
                        }
                    }
                }
            }
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        
        /*
            Public dialog procedure for the hold configuration dialog.
        */
        LRESULT HoldConfigurationDialog::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            if (msg == WM_INITDIALOG) {
                LogInfo("Hold configuration dialog opened");
                SetWindowLongPtr(
                    hwnd,
                    GWLP_USERDATA,
                    reinterpret_cast<LONG>(reinterpret_cast<HoldConfigurationDialog *>(lParam))
                );
            }
            else if (msg == WM_DESTROY) {
                SetWindowLongPtr(hwnd, GWLP_USERDATA, NULL);
                LogInfo("Hold configuration dialog closed");
            }

            HoldConfigurationDialog * dialog = reinterpret_cast<HoldConfigurationDialog*>(
                GetWindowLongPtr(hwnd, GWLP_USERDATA)
            );
            return dialog ? dialog->_WndProc(hwnd, msg, wParam, lParam) : DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }  // namespace Hold
} // namespace UKControllerPlugin

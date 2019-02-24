#include "pch/stdafx.h"
#include "hold/HoldConfigurationDialog.h"
#include "hold/HoldDisplayFunctions.h"
#include "hold/HoldWindowManager.h"

using UKControllerPlugin::Hold::ConvertToTchar;
using UKControllerPlugin::Hold::HoldWindowManager;

namespace UKControllerPlugin {
    namespace Hold {

        HoldConfigurationDialog::HoldConfigurationDialog(HoldWindowManager & windowManager)
            : windowManager(windowManager)
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

                    return TRUE;
                };
                // Buttons pressed
                case WM_COMMAND: {
                    switch (LOWORD(wParam)) {
                        case HOLD_SELECTOR_OK: {
                            // OK clicked, close the window
                            EndDialog(hwnd, wParam);
                            return TRUE;
                        }
                        case IDC_HOLD_OPEN: {
                            // They want to open a hold
                            int selectedIndex =  SendDlgItemMessage(
                                hwnd,
                                IDC_HOLD_SELECTOR,
                                CB_GETCURSEL,
                                0,
                                0
                            );
                            std::set<HoldingData, CompareHoldsDescription>::iterator it = this->holds.cbegin();
                            std::advance(it, selectedIndex);
                            this->windowManager.AddWindow(it->identifier);
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

#include "ScrollbarOptions.h"

namespace UKControllerPlugin::Components {

    ScrollbarOptions::ScrollbarOptions(unsigned short notches) : notches(notches), notch(1)
    {
        if (notches == 0) {
            throw std::invalid_argument("A scrollbar must have at least one notch");
        }
    }

    auto ScrollbarOptions::Notches() const -> unsigned short
    {
        return notches;
    }

    auto ScrollbarOptions::Notch() const -> unsigned short
    {
        return notch;
    }

    void ScrollbarOptions::Increment()
    {
        if (notch == notches) {
            return;
        }

        notch++;
    }

    void ScrollbarOptions::Decrement()
    {
        if (notch == 1) {
            return;
        }

        notch--;
    }
} // namespace UKControllerPlugin::Components

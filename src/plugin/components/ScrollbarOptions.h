#pragma once

namespace UKControllerPlugin::Components {

    /**
     * Contains options about scrollbars
     */
    class ScrollbarOptions
    {
        public:
        ScrollbarOptions(unsigned short notches);
        [[nodiscard]] auto Notches() const -> unsigned short;
        [[nodiscard]] auto Notch() const -> unsigned short;
        void Increment();
        void Decrement();

        private:
        // The total number of notches
        const unsigned short notches;

        // The current notch
        unsigned short notch;
    };

} // namespace UKControllerPlugin::Components

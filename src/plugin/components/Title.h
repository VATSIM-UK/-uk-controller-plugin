#pragma once

namespace UKControllerPlugin {
    namespace Windows {
        class GdiGraphicsInterface;
    } // namespace Windows
} // namespace UKControllerPlugin

namespace UKControllerPlugin::Components {

    /**
     * Prints a title to the screen
     */
    class Title : public std::enable_shared_from_this<Title>
    {
        public:
        static auto Create(std::wstring text, Gdiplus::Rect position) -> std::shared_ptr<Title>;
        void Draw(Windows::GdiGraphicsInterface& graphics) const;

        protected:
        Title(std::wstring text, Gdiplus::Rect position);

        private:
        // The text to display
        std::wstring text;

        // Where to show the text
        Gdiplus::Rect position;

        // The font
        const Gdiplus::Font& font;

        // Format
        const Gdiplus::StringFormat& format;

        // The brush
        std::shared_ptr<Gdiplus::Brush> textBrush;
    };

} // namespace UKControllerPlugin::Components

#include "Title.h"
#include "graphics/FontManager.h"
#include "graphics/StringFormatManager.h"
#include "graphics/GdiGraphicsInterface.h"

namespace UKControllerPlugin::Components {

    Title::Title(std::wstring text, Gdiplus::Rect position)
        : text(text), position(position), font(Graphics::FontManager::Instance().Get(14)),
          format(Graphics::StringFormatManager::Instance().GetCentreAlign()),
          textBrush(std::make_shared<Gdiplus::SolidBrush>(Gdiplus::Color(255, 255, 255)))
    {
    }

    auto Title::Create(std::wstring text, Gdiplus::Rect position) -> std::shared_ptr<Title>
    {
        return std::shared_ptr<Title>(new Title(text, position));
    }

    void Title::Draw(Windows::GdiGraphicsInterface& graphics) const
    {
        graphics.DrawString(text, position, *textBrush, format, font);
    }
} // namespace UKControllerPlugin::Components

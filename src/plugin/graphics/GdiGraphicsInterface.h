#pragma once

namespace Gdiplus {
    class RectF;
} // namespace Gdiplus

namespace UKControllerPlugin {
    namespace Windows {

        /*
            Interface for Windows' GDI Graphics API. Used by classes that want to draw to the
            radar screen.
        */
        class GdiGraphicsInterface
        {
            public:
            virtual ~GdiGraphicsInterface() = default;
            virtual void DrawRect(const Gdiplus::RectF& area, const Gdiplus::Pen& pen) = 0;
            virtual void DrawRect(const Gdiplus::Rect& area, const Gdiplus::Pen& pen) = 0;
            virtual void DrawRect(const RECT& area, const Gdiplus::Pen& pen) = 0;
            virtual void DrawCircle(const Gdiplus::RectF& area, const Gdiplus::Pen& pen) = 0;
            virtual void FillCircle(const Gdiplus::RectF& area, const Gdiplus::Brush& brush) = 0;
            virtual void FillCircle(const Gdiplus::Rect& area, const Gdiplus::Brush& brush) = 0;
            virtual void DrawCircle(const Gdiplus::Rect& area, const Gdiplus::Pen& pen) = 0;
            virtual void DrawDiamond(const Gdiplus::RectF& area, const Gdiplus::Pen& pen) = 0;
            virtual void FillDiamond(const Gdiplus::RectF& area, const Gdiplus::Brush& brush) = 0;
            virtual void DrawLine(const Gdiplus::Pen& pen, const Gdiplus::Point& start, const Gdiplus::Point& end) = 0;
            virtual void
            DrawLine(const Gdiplus::Pen& pen, const Gdiplus::PointF& start, const Gdiplus::PointF& end) = 0;
            virtual void DrawPath(const Gdiplus::GraphicsPath& path, const Gdiplus::Pen& pen) = 0;
            virtual void DrawString(std::wstring text, const Gdiplus::RectF& area, const Gdiplus::Brush& brush) = 0;
            virtual void DrawString(std::wstring text, const Gdiplus::Rect& area, const Gdiplus::Brush& brush) = 0;
            virtual void DrawString(
                const std::wstring& text,
                const Gdiplus::Rect& area,
                const Gdiplus::Brush& brush,
                const Gdiplus::StringFormat& format,
                const Gdiplus::Font& font) = 0;
            virtual void DrawString(std::wstring text, const RECT& area, const Gdiplus::Brush& brush) = 0;
            virtual void FillRect(const Gdiplus::RectF& area, const Gdiplus::Brush& brush) = 0;
            virtual void FillRect(const Gdiplus::Rect& area, const Gdiplus::Brush& brush) = 0;
            virtual void FillRect(const RECT& area, const Gdiplus::Brush& brush) = 0;
            virtual void SetAntialias(bool setting) = 0;
            virtual void SetDeviceHandle(HDC& handle) = 0;
            virtual void Clipped(Gdiplus::Region& clipRegion, std::function<void()> drawFunction) = 0;
            virtual void Translated(Gdiplus::REAL x, Gdiplus::REAL y, std::function<void()> drawFunction) = 0;
            virtual std::shared_ptr<Gdiplus::Matrix> GetTransform() = 0;
            virtual std::shared_ptr<Gdiplus::Matrix> GetTotalTransform() = 0;
            virtual Gdiplus::RectF GetClipBounds() = 0;
            virtual void Scaled(Gdiplus::REAL x, Gdiplus::REAL y, std::function<void()> drawFunction) = 0;
            virtual void Rotated(Gdiplus::REAL angle, std::function<void()> drawFunction) = 0;
            virtual void FillPolygon(Gdiplus::Point* points, const Gdiplus::Brush& brush, int numPoints) = 0;
        };
    } // namespace Windows
} // namespace UKControllerPlugin

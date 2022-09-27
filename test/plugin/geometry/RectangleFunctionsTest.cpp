#include "geometry/RectangleFunctions.h"

using UKControllerPlugin::Geometry::PointInRect;

namespace UKControllerPluginTest::Geometry {
    class RectangleFunctionsTest : public testing::Test
    {
        public:
        RECT rect{10, 10, 50, 50};
    };

    TEST_F(RectangleFunctionsTest, PointIsInRectangleTopLeftCorner)
    {
        EXPECT_TRUE(PointInRect(POINT{10, 10}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInRectangleTopBoundary)
    {
        EXPECT_TRUE(PointInRect(POINT{20, 10}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInRectangleTopRightCorner)
    {
        EXPECT_TRUE(PointInRect(POINT{50, 10}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInRectangleRightBoundary)
    {
        EXPECT_TRUE(PointInRect(POINT{50, 30}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInRectangleBottomRightCorner)
    {
        EXPECT_TRUE(PointInRect(POINT{50, 50}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInRectangleBottomBoundary)
    {
        EXPECT_TRUE(PointInRect(POINT{25, 50}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInRectangleBottomLeftCorner)
    {
        EXPECT_TRUE(PointInRect(POINT{10, 50}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInRectangleLeftBoundary)
    {
        EXPECT_TRUE(PointInRect(POINT{10, 30}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInNotInRectangleAboveTopBoundary)
    {
        EXPECT_FALSE(PointInRect(POINT{25, 5}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInNotInRectangleRightOfRightBoundary)
    {
        EXPECT_FALSE(PointInRect(POINT{55, 25}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInNotInRectangleBelowBottomBoundary)
    {
        EXPECT_FALSE(PointInRect(POINT{25, 55}, rect));
    }

    TEST_F(RectangleFunctionsTest, PointIsInNotInRectangleLeftOfLeftBoundary)
    {
        EXPECT_FALSE(PointInRect(POINT{5, 25}, rect));
    }
} // namespace UKControllerPluginTest::Geometry

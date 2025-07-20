#include <gtest/gtest.h>

#include "../Include/Canvas.h"

//Create a canvas (window) of size 420 x 360 and make it 100% black
TEST(canvasTests, WindowCreate) {
    Tuple color = Tuple::color(1,1,1);
    Canvas canvas(420, 360, color);

    EXPECT_EQ(canvas.width, 420);
    EXPECT_EQ(canvas.height, 360);
    EXPECT_TRUE(Tuple::isEqual(canvas.bgColor, color));
}

//write specific color to specific pixel of the canvas
TEST(canvastests, SpecifyPixel) {
    Tuple colorAtPixel = Tuple::color(1,1,1);
    Tuple bgColor = Tuple::color(0,0,0);
    Canvas canvas(420, 360, colorAtPixel);

    writeToPixel(canvas, colorAtPixel);
    EXPECT_TRUE(Tuple::isEqual(getColorAtPixel(), colorAtPixel));
}
//
// Created by Ryan Jones on 7/5/25.
//

#ifndef CANVAS_H
#define CANVAS_H

#include "../Include/Tuple.h"
#include <iostream>
#include <fstream>

/*
 * A canvas is not an interactive window, it's just pixels rendered to screen at a specified size and color. In theory
 * we may be able to use PPM file format to accomplish this - at least to start
 */

class Canvas {
public:
    int width;
    int height;
    Tuple bgColor;

    Canvas() = default;
    explicit Canvas(int width, int height, Tuple bgColor = Tuple::color(0,0,0));

    std::filesystem::path makeFile(std::string fileName);
    void writeToFile(std::filesystem::path filePath);
    void readFromFile(std::filesystem::path filePath);
    std::string randNum(); //just for fun, not likely to stick around
    void writeToPixel(Canvas canvas, int x_pos, int y_pos, Tuple color);
};



#endif //CANVAS_H

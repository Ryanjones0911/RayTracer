//
// Created by Ryan Jones on 7/5/25.
//
#include "../Include/Canvas.h"
#include <filesystem>

Canvas::Canvas(int width, int height, Tuple bgColor) {
    this->width = width;
    this->height = height;
    this->bgColor = bgColor;
}

std::filesystem::path Canvas::makeFile(std::string fileName){
    std::filesystem::path dirPath = "../Images/";
    std::filesystem::path imagePath;
    std::string temp = ".ppm";

    imagePath = fileName + temp;
    std::filesystem::path fullPath = dirPath / imagePath;

    return fullPath;
}

void Canvas::writeToFile(std::filesystem::path filePath) {
    char input;

    if (std::filesystem::exists(filePath)) {
        std::cout << "File already exists. Do you want to overwrite? (y/n)" << std::endl;
        std::cin >> input;
        if (input == 'y') {
            std::cout << "Overwriting existing file." << std::endl;
        }
        else {
            std::cout << "Exiting." << std::endl;
        }
    }

    std::ofstream imageFile(filePath);



    imageFile << "P3\n";
    imageFile << width << " " << height << "\n";
    imageFile << "255\n";
    for (int i = 0; i < width * height; i++) {
        if (i % 2 == 0) {
            imageFile << randNum() << " " << randNum() << " " << randNum() << std::endl;
            //imageFile << "0 0 0\n";
        }
        else {
            imageFile << "255 255 255\n";
        }
    }
    imageFile.close();
}

void Canvas::readFromFile(std::filesystem::path filePath) {
    //for now this is just gonna convert ppm to txt for debugging

}

void writeToPixel(Canvas canvas, int x_pos, int y_pos, Tuple color) {

}

std::string Canvas::randNum() {
    int i = rand() % 256;
    std::string s = std::to_string(i);
    return s;
}
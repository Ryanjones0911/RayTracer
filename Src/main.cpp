#include <iostream>
#include "../Include/Tuple.h"
#include "../Include/Canvas.h"

int main() {
    std::srand(std::time(nullptr));

    std::string name;
    int i = 0;
    while (i != 10){
        int width = std::rand() % 51;
        int height = std::rand() % 51;
        Canvas canvas(width, height);
        std::cout << "Enter name: ";
        std::cin >> name;

        canvas.writeToFile(canvas.makeFile(name));
        i++;
    }
    return 0;
}

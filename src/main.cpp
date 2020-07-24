#include "vector3.h"

#include <iostream>

int main() {
    Vector3 vec(1, 2, 3);
    std::cout<< vec.X << " " << vec.G << " " << vec.Data[2] << std::endl;
    return 0;
}

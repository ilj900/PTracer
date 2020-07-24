#pragma once

#include "vector3.h"

class Sphere
{
public:
    Sphere() = default;
    Sphere(Vector3 &CenterIn, float RadiusIn): Center(CenterIn), Radius(RadiusIn) {};
    ~Sphere() = default;

private:
    Vector3 Center;
    float Radius;
};
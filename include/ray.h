#pragma once

#include "vector3.h"

static Vector3 DefaultOrigin = {0.f, 0.f, 0.f};

class Ray
{
public:
    Ray() = default;
    Ray(Vector3 &DirectionIn, Vector3 &OriginIn = DefaultOrigin): Direction(DirectionIn), Origin(OriginIn) {};
    ~Ray() = default;

public:
    Vector3 Direction = {1.f, 0.f, 0.f};
    Vector3 Origin = DefaultOrigin;
};
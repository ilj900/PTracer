#pragma once

#include "ray.h"

Direction3 Reflect(Direction3& RayDirection, Direction3& Normal)
{
    Direction3 ReflectedDirection = Normal * 2 * (Normal * RayDirection) - RayDirection;
    return ReflectedDirection;
}

Direction3 Reflect(Direction3&& RayDirection, Direction3& Normal)
{
    Direction3 ReflectedDirection = Normal * 2 * (Normal * RayDirection) - RayDirection;
    return ReflectedDirection;
}
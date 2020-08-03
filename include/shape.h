#pragma once

#include "ray.h"

class FShape
{
public:
    FShape() = default;
    ~FShape() = default;

    virtual bool Intersect(FRay& RayIn, FRay* RayOut = nullptr) = 0;
};
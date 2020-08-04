#pragma once

#include "ray.h"

class FShape
{
public:
    virtual bool Intersect(FRay RayIn, FRay& RayOut) = 0;

public:
    ColorRGBA Albedo;
};
#pragma once

#include "ray.h"

class FShape
{
public:
    ///
    virtual bool Intersect(FRay RayIn, FRay& RayOut) = 0;

public:
    FVector3 Position;
    ColorRGBA Albedo;
};
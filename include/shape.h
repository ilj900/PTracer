#pragma once

#include "ray.h"
#include "utils.h"

class FShape
{
public:
    FShape() = default;
    FShape(FVector3&& PositionIn, ColorRGBA&& AlbedoIn) : Position(PositionIn), Albedo(AlbedoIn) {};
    FShape(FVector3& PositionIn, ColorRGBA& AlbedoIn) : Position(PositionIn), Albedo(AlbedoIn) {};
    ~FShape() = default;
    virtual bool Intersect(FRay RayIn, FRay& RayOut, FVector3& Normal) {return false;};

public:
    FVector3 Position;
    ColorRGBA Albedo;
};
#pragma once

#include "ray.h"

class FShape
{
public:
    FShape() = default;
    FShape(FVector3&& PositionIn, ColorRGBA&& AlbedoIn) : Position(PositionIn), Albedo(AlbedoIn) {};
    FShape(FVector3& PositionIn, ColorRGBA& AlbedoIn) : Position(PositionIn), Albedo(AlbedoIn) {};
    ~FShape() = default;
    virtual bool Intersect(FRay RayIn, FRay& RayOut) {return false;};

public:
    FVector3 Position;
    ColorRGBA Albedo;
};
#pragma once

#include "vector3.h"

static FVector3 DefaultOrigin = {0.f, 0.f, 0.f};
static FVector3 DefaultDirection = {1.f, 0.f, 0.f};

class FRay
{
public:
    FRay(FVector3 &OriginIn = DefaultOrigin, FVector3 &DirectionIn = DefaultDirection): Direction(DirectionIn), Origin(OriginIn) {};
    ~FRay() = default;

public:
    FVector3 Direction = {1.f, 0.f, 0.f};
    FVector3 Origin = DefaultOrigin;
    float Eta = 1.f;
};
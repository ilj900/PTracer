#pragma once

#include "vector4.h"

class FLight
{
public:
    FLight(const Vector4& Position) : Position{Position} {};
    FLight(float X, float Y, float Z) : Position{X, Y, Z, 1.f} {};
    ~FLight() = default;

public:
    Vector4 Position;
};
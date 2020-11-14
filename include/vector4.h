#pragma once

#include <iostream>
#include <string>
#include "vector3.h"

class FVector4
{
public:
    FVector4() = default;
    FVector4(float X, float Y, float Z, float W): Data{X, Y, Z, W} {};
    ~FVector4() = default;

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y) + "Z: " + std::to_string(Z) + " W: " + std::to_string(W);};

public:
    union {
        float Data[4];
        struct {float X, Y, Z, W;};
        struct {float R, G, B, A;};
    };

    FVector4 operator+(const FVector4& val) const
    {
        return FVector4{X + val.X, Y + val.Y, Z + val.Z, W + val.W};
    }

    FVector4 operator-(const FVector4& val) const
    {
        return FVector4{X - val.X, Y - val.Y, Z - val.Z, W - val.W};
    }

    FVector4 operator*(float val) const
    {
        return {X * val, Y * val, Z * val, W * val};
    }

    FVector4 operator/(float val) const
    {
        return {X / val, Y / val, Z / val, W / val};
    }

    void operator+=(const FVector4& val)
    {
        X += val.X;
        Y += val.Y;
        Z += val.Z;
        W += val.W;
    }

    void operator-=(const FVector4& val)
    {
        X -= val.X;
        Y -= val.Y;
        Z -= val.Z;
        W -= val.W;
    }

    void operator*=(float val)
    {
        X *= val;
        Y *= val;
        Z *= val;
        W *= val;
    }

    void operator/=(float val)
    {
        X /= val;
        Y /= val;
        Z /= val;
        W /= val;
    }

    FVector3 GetVector3() const
    {
        return {X, Y, Z};
    }
};

using Vector4 = FVector4;
using Direction4 = FVector4;
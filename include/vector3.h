#pragma once

#include <iostream>
#include <string>
#include <cmath>

class FVector3
{
public:
    FVector3() = default;
    FVector3(float X, float Y, float Z): Data{X, Y , Z} {};
    ~FVector3() = default;

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y) + " Z: " + std::to_string(Z);};

public:
    union {
        float Data[3];
        struct {float X, Y, Z;};
        struct {float R, G, B;};
    };

    FVector3 operator+(const FVector3& val)
    {
        return FVector3{X + val.X, Y + val.Y, Z + val.Z};
    }

    FVector3 operator-(const FVector3& val)
    {
        return FVector3{X - val.X, Y - val.Y, Z - val.Z};
    }

    FVector3 operator*(float val)
    {
        return {X * val, Y * val, Z * val};
    }

    FVector3 operator/(float val)
    {
        return {X / val, Y / val, Z / val};
    }

    void operator+=(const FVector3& val)
    {
        X += val.X;
        Y += val.Y;
        Z += val.Z;
    }

    void operator-=(const FVector3& val)
    {
        X -= val.X;
        Y -= val.Y;
        Z -= val.Z;
    }

    void operator*=(float val)
    {
        X *= val;
        Y *= val;
        Z *= val;
    }

    void operator/=(float val)
    {
        X /= val;
        Y /= val;
        Z /= val;
    }

    float Len()
    {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    float Len2()
    {
        return X * X + Y * Y + Z * Z;
    }

    FVector3 GetNormal()
    {
        auto Length = Len();
        return {X /= Length, Y /= Length,Z /= Length};
    }

    void Normalize()
    {
        auto Length = Len();
        X /= Length;
        Y /= Length;
        Z /= Length;
    }
};

using Direction3 = FVector3;

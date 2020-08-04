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

    FVector3 operator+(const FVector3& Val)
    {
        return FVector3{X + Val.X, Y + Val.Y, Z + Val.Z};
    }

    FVector3 operator-(const FVector3& Val)
    {
        return FVector3{X - Val.X, Y - Val.Y, Z - Val.Z};
    }

    FVector3 operator*(float Val)
    {
        return {X * Val, Y * Val, Z * Val};
    }

    float operator*(FVector3& Val)
    {
        return X * Val.X + Y * Val.Y + Z * Val.Z;
    }

    FVector3 operator/(float Val)
    {
        return {X / Val, Y / Val, Z / Val};
    }

    void operator+=(const FVector3& Val)
    {
        X += Val.X;
        Y += Val.Y;
        Z += Val.Z;
    }

    FVector3 operator-()
    {
        return {-X, -Y, -Z};
    }

    void operator-=(const FVector3& Val)
    {
        X -= Val.X;
        Y -= Val.Y;
        Z -= Val.Z;
    }

    void operator*=(float Val)
    {
        X *= Val;
        Y *= Val;
        Z *= Val;
    }

    void operator/=(float Val)
    {
        X /= Val;
        Y /= Val;
        Z /= Val;
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

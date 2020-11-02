#pragma once

#include "utils.h"

#include <iostream>
#include <string>
#include <cmath>

class FVector3
{
public:
    FVector3(): X(0.f), Y(0.f), Z(0.f) {};
    FVector3(float X, float Y, float Z): Data{X, Y , Z} {};
    FVector3(const FVector3& Vec) : Data{Vec.X, Vec.Y, Vec.Z} {};
    ~FVector3() = default;

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y) + " Z: " + std::to_string(Z);};

public:
    union {
        float Data[3];
        struct {float X, Y, Z;};
        struct {float R, G, B;};
    };

    inline FVector3 operator+(const FVector3& Value)
    {
        return FVector3{X + Value.X, Y + Value.Y, Z + Value.Z};
    }

    inline FVector3 operator-(const FVector3& Value)
    {
        return FVector3{X - Value.X, Y - Value.Y, Z - Value.Z};
    }

    inline FVector3 operator*(float Value)
    {
        return {X * Value, Y * Value, Z * Value};
    }

    inline FVector3 operator/(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FVector3::Division_by_zero.");
        return {X * Inversed, Y * Inversed, Z * Inversed};
    }

    inline void operator+=(const FVector3& Value)
    {
        X += Value.X;
        Y += Value.Y;
        Z += Value.Z;
    }

    inline FVector3 operator-()
    {
        return {-X, -Y, -Z};
    }

    inline void operator-=(const FVector3& Value)
    {
        X -= Value.X;
        Y -= Value.Y;
        Z -= Value.Z;
    }

    inline void operator*=(float Value)
    {
        X *= Value;
        Y *= Value;
        Z *= Value;
    }

    inline void operator/=(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FVector3::Division_by_zero.");
        X *= Inversed;
        Y *= Inversed;
        Z *= Inversed;
    }

    inline float operator*(FVector3& Value)
    {
        return X * Value.X + Y * Value.Y + Z * Value.Z;
    }

    inline float Len()
    {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    inline float Len2()
    {
        return X * X + Y * Y + Z * Z;
    }

    inline FVector3 GetNormal()
    {
        auto InversedLength = 1.f / CHECK_NOT_ZERO(Len(), "FVector3::Length_is_zero.");
        return {X *= InversedLength, Y *= InversedLength,Z *= InversedLength};
    }

    inline void Normalize()
    {
        auto InversedLength = 1.f / CHECK_NOT_ZERO(Len(), "FVector3::Length_is_zero.");
        X *= InversedLength;
        Y *= InversedLength;
        Z *= InversedLength;
    }
};

inline std::ostream& operator<<(std::ostream& OutputStream, const FVector3& Vec)
{
    OutputStream << "X: " << Vec.X << " Y: " << Vec.Y << " Z: " << Vec.Z << std::endl;
    return OutputStream;
}

using Direction3 = FVector3;

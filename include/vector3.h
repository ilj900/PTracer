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

    inline FVector3 operator+(const FVector3& Value) const
    {
        return FVector3{X + Value.X, Y + Value.Y, Z + Value.Z};
    }

    inline FVector3 operator-(const FVector3& Value) const
    {
        return FVector3{X - Value.X, Y - Value.Y, Z - Value.Z};
    }

    inline FVector3 operator-() const
    {
        return FVector3{-X, -Y, -Z};
    }

    inline float operator*(const FVector3& Value) const
    {
        return X * Value.X + Y * Value.Y + Z * Value.Z;
    }

    inline void operator+=(const FVector3& Value)
    {
        X += Value.X;
        Y += Value.Y;
        Z += Value.Z;
    }

    inline void operator-=(const FVector3& Value)
    {
        X -= Value.X;
        Y -= Value.Y;
        Z -= Value.Z;
    }

    inline FVector3 operator*(float Value) const
    {
        return {X * Value, Y * Value, Z * Value};
    }

    inline FVector3 operator/(float Value) const
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FVector3::Division_by_zero.");
        return {X * Inversed, Y * Inversed, Z * Inversed};
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

    inline float Len() const
    {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    inline float Len2() const
    {
        return X * X + Y * Y + Z * Z;
    }

    inline FVector3 GetNormalized() const
    {
        auto InversedLength = 1.f / CHECK_NOT_ZERO(Len(), "FVector3::Length_is_zero.");
        return {X * InversedLength, Y * InversedLength,Z * InversedLength};
    }

    inline void Normalize()
    {
        auto InversedLength = 1.f / CHECK_NOT_ZERO(Len(), "FVector3::Length_is_zero.");
        X *= InversedLength;
        Y *= InversedLength;
        Z *= InversedLength;
    }

    inline float GetCos(const FVector3& Vector) const
    {
        return GetNormalized() * Vector.GetNormalized();
    }

    inline float GetAngle(const FVector3& Vector) const
    {
        return std::acos(GetNormalized() * Vector.GetNormalized());
    }

    inline FVector3 GetPrjectionOnVector(const FVector3& Vector) const
    {
        return Vector * ((Vector * (*this)) / Vector.Len2());
    }

    inline FVector3 GetPerpendecularToVector(const FVector3& Vector) const
    {
        return (*this) - GetPrjectionOnVector(Vector);
    }

    inline void Rotate(const FVector3& Vector, float Angle)
    {
        //Todo
    }

    inline FVector3 RotateX(float Angle)
    {
        auto C = std::cos(Angle);
        auto S = std::sin(Angle);
    }

    inline FVector3 RotateY(float Angle)
    {

    }

    inline FVector3 RotateZ(float Angle)
    {

    }
};

inline std::ostream& operator<<(std::ostream& OutputStream, const FVector3& Vec)
{
    OutputStream << "X: " << Vec.X << " Y: " << Vec.Y << " Z: " << Vec.Z << std::endl;
    return OutputStream;
}

using Direction3 = FVector3;

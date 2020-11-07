#pragma once

#include "utils.h"

#include <iostream>
#include <stdexcept>
#include <string>

class FVector2
{
public:
    FVector2(): Data{0.f, 0.f} {};
    FVector2(float X, float Y): Data{X, Y} {};
    FVector2(const FVector2& Vec) : Data{Vec.X, Vec.Y} {};
    ~FVector2() = default;

    std::string ToString() const {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y);};

public:
    union {
        float Data[2];
        struct {float X, Y;};
        struct {float U, V;};
    };

    inline FVector2 operator+(const FVector2& Value) const
    {
        return FVector2{X + Value.X, Y + Value.Y};
    }

    inline FVector2 operator-(const FVector2& Value) const
    {
        return FVector2{X - Value.X, Y - Value.Y};
    }

    inline FVector2 operator-() const
    {
        return FVector2(-X, -Y);
    }

    inline FVector2 operator*(float Value) const
    {
        return {X * Value, Y * Value};
    }

    inline FVector2 operator/(float Value) const
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FVector2::Division_by_zero.");
        return {X * Inversed, Y * Inversed};
    }

    inline void operator+=(const FVector2& Value)
    {
        X += Value.X;
        Y += Value.Y;
    }

    inline void operator-=(const FVector2& Value)
    {
        X -= Value.X;
        Y -= Value.Y;
    }

    inline void operator*=(float Value)
    {
        X *= Value;
        Y *= Value;
    }

    inline void operator/=(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FVector2::Division_by_zero.");
        X *= Inversed;
        Y *= Inversed;
    }

    inline float operator*(const FVector2& Vector) const
    {
        return Vector.X * X + Vector.Y * Y;
    }

    inline float Len() const
    {
        return std::sqrt(X * X + Y * Y);
    }

    inline float Len2() const
    {
        return X * X + Y * Y;
    }

    inline FVector2 GetNormalized() const
    {
        auto InversedLength = 1.f / CHECK_NOT_ZERO(Len(), "FVector2::Length_is_zero.");
        return FVector2{X * InversedLength, Y * InversedLength};
    }

    inline void  Normalize()
    {
        auto InversedLength = 1.f / CHECK_NOT_ZERO(Len(), "FVector2::Length_is_zero.");
        X *= InversedLength;
        Y *= InversedLength;
    }

    inline float GetCos(const FVector2& Vector) const
    {
        return GetNormalized() * Vector.GetNormalized();
    }

    inline float GetAngle(const FVector2& Vector) const
    {
        return std::acos(GetNormalized() * Vector.GetNormalized());
    }

    inline FVector2 GetPrjectionOnVector(const FVector2& Vector) const
    {
        return Vector * ((Vector * (*this)) / Vector.Len2());
    }

    inline FVector2 GetPerpendecularToVector(const FVector2& Vector) const
    {
        return (*this) - GetPrjectionOnVector(Vector);
    }

    inline FVector2 Reflect(FVector2 Normal)
    {
        auto Perp = GetPerpendecularToVector(Normal);
        return (*this + (Perp * 2.f));
    }
};

inline std::ostream& operator<<(std::ostream& OutputStream, const FVector2& Vec)
{
    OutputStream << "X: " << Vec.X << " Y: " << Vec.Y << std::endl;
    return OutputStream;
}

using TextureCoordinates = FVector2;
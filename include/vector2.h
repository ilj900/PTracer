#pragma once

#include <iostream>
#include <string>

class FVector2
{
public:
    FVector2() = default;
    FVector2(float X, float Y): Data{X, Y} {};
    ~FVector2() = default;

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y);};

public:
    union {
        float Data[2];
        struct {float X, Y;};
        struct {float U, V;};
    };

    FVector2 operator+(const FVector2& val)
    {
        return FVector2{X + val.X, Y + val.Y};
    }

    FVector2 operator-(const FVector2& val)
    {
        return FVector2{X - val.X, Y - val.Y};
    }

    FVector2 operator*(float val)
    {
        return {X * val, Y * val};
    }

    FVector2 operator/(float val)
    {
        return {X / val, Y / val};
    }

    void operator+=(const FVector2& val)
    {
        X += val.X;
        Y += val.Y;
    }

    void operator-=(const FVector2& val)
    {
        X -= val.X;
        Y -= val.Y;
    }

    void operator*=(float val)
    {
        X *= val;
        Y *= val;
    }

    void operator/=(float val)
    {
        X /= val;
        Y /= val;
    }
};

using TextureCoordinates = FVector2;
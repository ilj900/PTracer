#pragma once

#include <iostream>
#include <string>

class Vector2
{
public:
    Vector2() = default;
    Vector2(float X, float Y): Data{X, Y} {};
    ~Vector2() = default;

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y);};

public:
    union {
        float Data[2];
        struct {float X, Y;};
        struct {float U, V;};
    };

    Vector2 operator+(const Vector2& val)
    {
        return Vector2{X + val.X, Y + val.Y};
    }

    Vector2 operator-(const Vector2& val)
    {
        return Vector2{X - val.X, Y - val.Y};
    }

    Vector2 operator*(float val)
    {
        return {X * val, Y * val};
    }

    Vector2 operator/(float val)
    {
        return {X / val, Y / val};
    }

    void operator+=(const Vector2& val)
    {
        X += val.X;
        Y += val.Y;
    }

    void operator-=(const Vector2& val)
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
#pragma once

#include <iostream>
#include <string>

class Vector3
{
public:
    Vector3() = default;
    Vector3(float X, float Y, float Z): Data{X, Y ,Z} {};
    ~Vector3() = default;

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y) + " Z: " + std::to_string(Z);};

public:
    union {
        float Data[3];
        struct {float X, Y, Z;};
        struct {float R, G, B;};
    };

    Vector3 operator+(const Vector3& val)
    {
        return Vector3{X + val.X, Y + val.Y, Z + val.Z};
    }

    Vector3 operator-(const Vector3& val)
    {
        return Vector3{X - val.X, Y - val.Y, Z - val.Z};
    }

    Vector3 operator*(float val)
    {
        return {X * val, Y * val, Z * val};
    }

    Vector3 operator/(float val)
    {
        return {X / val, Y / val, Z / val};
    }

    void operator+=(const Vector3& val)
    {
        X += val.X;
        Y += val.Y;
        Z += val.Z;
    }

    void operator-=(const Vector3& val)
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
};

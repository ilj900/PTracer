#pragma once

#include <iostream>
#include <string>

class Vector4
{
public:
    Vector4() = default;
    Vector4(float X, float Y, float Z, float W): Data{X, Y, Z, W} {};
    ~Vector4() = default;

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y) + "Z: " + std::to_string(Z) + " W: " + std::to_string(W);};

public:
    union {
        float Data[4];
        struct {float X, Y, Z, W;};
        struct {float R, G, B, A;};
    };

    Vector4 operator+(const Vector4& val)
    {
        return Vector4{X + val.X, Y + val.Y, Z + val.Z, W + val.W};
    }

    Vector4 operator-(const Vector4& val)
    {
        return Vector4{X - val.X, Y - val.Y, Z - val.Z, W - val.W};
    }

    Vector4 operator*(float val)
    {
        return {X * val, Y * val, Z * val, W * val};
    }

    Vector4 operator/(float val)
    {
        return {X / val, Y / val, Z / val, W / val};
    }

    void operator+=(const Vector4& val)
    {
        X += val.X;
        Y += val.Y;
        Z += val.Z;
        W += val.W;
    }

    void operator-=(const Vector4& val)
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
};

#pragma once

#include <iostream>
#include <string>

class TVector4
{
public:
    TVector4() = default;
    TVector4(float X, float Y, float Z, float W): Data{X, Y, Z, W} {};
    ~TVector4() = default;

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y) + "Z: " + std::to_string(Z) + " W: " + std::to_string(W);};

public:
    union {
        float Data[4];
        struct {float X, Y, Z, W;};
        struct {float R, G, B, A;};
    };

    TVector4 operator+(const TVector4& val)
    {
        return TVector4{X + val.X, Y + val.Y, Z + val.Z, W + val.W};
    }

    TVector4 operator-(const TVector4& val)
    {
        return TVector4{X - val.X, Y - val.Y, Z - val.Z, W - val.W};
    }

    TVector4 operator*(float val)
    {
        return {X * val, Y * val, Z * val, W * val};
    }

    TVector4 operator/(float val)
    {
        return {X / val, Y / val, Z / val, W / val};
    }

    void operator+=(const TVector4& val)
    {
        X += val.X;
        Y += val.Y;
        Z += val.Z;
        W += val.W;
    }

    void operator-=(const TVector4& val)
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

using Vector4 = TVector4;
using Direction4 = TVector4;
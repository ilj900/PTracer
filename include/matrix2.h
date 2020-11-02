#pragma once

#include "utils.h"

#include <stdexcept>

class FMatrix2
{
public:
    FMatrix2() : Data{0.f, 0.f, 0.f, 0.f} {};
    FMatrix2(float M00, float M01, float M10, float M11) : Data{M00, M01, M10, M11} {};
    FMatrix2(const FMatrix2& Mat) : Data{Mat.M00, Mat.M01, Mat.M10, Mat.M11} {};
    ~FMatrix2() = default;
public:
    union {
        float Data[4];
        struct {float M00, M01, M10, M11;};
    };

public:
    FMatrix2 operator+(FMatrix2& Mat)
    {
        return FMatrix2{M00 + Mat.M00, M01 + Mat.M01, M10 + Mat.M10, M11 + Mat.M11};
    }

    FMatrix2 operator-(FMatrix2& Mat)
    {
        return FMatrix2{M00 - Mat.M00, M01 - Mat.M01, M10 - Mat.M10, M11 - Mat.M11};
    }

    void operator+=(const FMatrix2& Mat)
    {
        M00 += Mat.M00;
        M01 += Mat.M01;
        M10 += Mat.M10;
        M11 += Mat.M11;
    }

    void operator-=(const FMatrix2& Mat)
    {
        M00 -= Mat.M00;
        M01 -= Mat.M01;
        M10 -= Mat.M10;
        M11 -= Mat.M11;
    }

    FMatrix2 operator*(float Value)
    {
        return FMatrix2{M00 * Value, M01 * Value, M10 * Value, M11 * Value};
    }

    FMatrix2 operator/(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FMatrix2::Division_by_zero.");
        return FMatrix2{M00 * Inversed, M01 * Inversed, M10 * Inversed, M11 * Inversed};
    }

    void operator*=(float Value)
    {
        M00 *= Value;
        M01 *= Value;
        M10 *= Value;
        M11 *= Value;
    }

    void operator/=(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FMatrix2::Division_by_zero.");
        M00 *= Inversed;
        M01 *= Inversed;
        M10 *= Inversed;
        M11 *= Inversed;
    }

    FMatrix2 operator*(FMatrix2& Mat)
    {
        return FMatrix2{M00 * Mat.M00 + M01 * Mat.M10, M00 * Mat.M10 + M10 * Mat.M11, M00 * Mat.M10 + M01 * Mat.M10, M10 * Mat.M01 + M11 * Mat.M11};
    }

    float GetDeterminant()
    {
        return M00 * M11 - M10 * M01;
    }

    void Transpose()
    {
        float Buff = M01;
        M01 = M10;
        M10 = Buff;
    }

    void Inverse()
    {
        auto InversedD = 1.f / CHECK_NOT_ZERO(GetDeterminant(), "Determinant_is_zero.");
        {
            float Temp = M00;
            M00 = M11;
            M11 = Temp;
            Temp = M10;
            M10 = -M01;
            M01 = -Temp;
            M00 *= InversedD;
            M01 *= InversedD;
            M10 *= InversedD;
            M11 *= InversedD;
        }
    }
};

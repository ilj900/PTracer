#pragma once

#include "utils.h"

#include <stdexcept>
#include <iomanip>

class FMatrix4
{
public:
    FMatrix4() : Data{0.f, 0.f, 0.f, 0.f,
                      0.f, 0.f, 0.f, 0.f,
                      0.f, 0.f, 0.f, 0.f,
                      0.f, 0.f, 0.f, 0.f} {};
    FMatrix4(float M00, float M01, float M02, float M03,
             float M10, float M11, float M12, float M13,
             float M20, float M21, float M22, float M23,
             float M30, float M31, float M32, float M33) : Data{M00, M01, M02, M03,
                                                                M10, M11, M12, M13,
                                                                M20, M21, M22, M23,
                                                                M30, M31, M32, M33} {};
    FMatrix4(const FMatrix4& Mat) : Data{Mat.M00, Mat.M01, Mat.M02, Mat.M03,
                                         Mat.M10, Mat.M11, Mat.M12, Mat.M13,
                                         Mat.M20, Mat.M21, Mat.M22, Mat.M23,
                                         Mat.M30, Mat.M31, Mat.M32, Mat.M33} {};
    ~FMatrix4() = default;
public:
    union {
        float Data[16];
        struct {float M00, M01, M02, M03, M10, M11, M12, M13, M20, M21, M22, M23, M30, M31, M32, M33;};
    };

public:
    FMatrix4 operator+(FMatrix4& Mat)
    {
        return FMatrix4{M00 + Mat.M00, M01 + Mat.M01, M02 + Mat.M02, M03 + Mat.M03,
                        M10 + Mat.M10, M11 + Mat.M11, M12 + Mat.M12, M13 + Mat.M13,
                        M20 + Mat.M20, M21 + Mat.M21, M22 + Mat.M22, M23 + Mat.M23,
                        M30 + Mat.M30, M31 + Mat.M31, M32 + Mat.M32, M33 + Mat.M33};
    }

    FMatrix4 operator-(FMatrix4& Mat)
    {
        return FMatrix4{M00 - Mat.M00, M01 - Mat.M01, M02 - Mat.M02, M03 - Mat.M03,
                        M10 - Mat.M10, M11 - Mat.M11, M12 - Mat.M12, M13 - Mat.M13,
                        M20 - Mat.M20, M21 - Mat.M21, M22 - Mat.M22, M23 - Mat.M23,
                        M30 - Mat.M30, M31 - Mat.M31, M32 - Mat.M32, M33 - Mat.M33};
    }

    void operator+=(const FMatrix4& Mat)
    {
        M00 += Mat.M00;
        M01 += Mat.M01;
        M02 += Mat.M02;
        M03 += Mat.M03;
        M10 += Mat.M10;
        M11 += Mat.M11;
        M12 += Mat.M12;
        M13 += Mat.M13;
        M20 += Mat.M20;
        M21 += Mat.M21;
        M22 += Mat.M22;
        M23 += Mat.M23;
        M30 += Mat.M30;
        M31 += Mat.M31;
        M32 += Mat.M32;
        M33 += Mat.M33;
    }

    void operator-=(const FMatrix4& Mat)
    {
        M00 -= Mat.M00;
        M01 -= Mat.M01;
        M02 -= Mat.M02;
        M03 -= Mat.M03;
        M10 -= Mat.M10;
        M11 -= Mat.M11;
        M12 -= Mat.M12;
        M13 -= Mat.M13;
        M20 -= Mat.M20;
        M21 -= Mat.M21;
        M22 -= Mat.M22;
        M23 -= Mat.M23;
        M30 -= Mat.M30;
        M31 -= Mat.M31;
        M32 -= Mat.M32;
        M33 -= Mat.M33;
    }

    FMatrix4 operator*(float Value)
    {
        return FMatrix4{M00 * Value, M01 * Value, M02 * Value, M03 * Value,
                        M10 * Value, M11 * Value, M12 * Value, M13 * Value,
                        M20 * Value, M21 * Value, M22 * Value, M23 * Value,
                        M30 * Value, M31 * Value, M32 * Value, M33 * Value,};
    }

    FMatrix4 operator/(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FMatrix4::Division_by_zero.");
        return FMatrix4{M00 * Inversed, M01 * Inversed, M02 * Inversed, M03 * Inversed,
                        M10 * Inversed, M11 * Inversed, M12 * Inversed, M13 * Inversed,
                        M20 * Inversed, M21 * Inversed, M22 * Inversed, M23 * Inversed,
                        M30 * Inversed, M31 * Inversed, M32 * Inversed, M33 * Inversed};
    }

    void operator*=(float Value)
    {
        M00 *= Value;
        M01 *= Value;
        M02 *= Value;
        M03 *= Value;
        M10 *= Value;
        M11 *= Value;
        M12 *= Value;
        M13 *= Value;
        M20 *= Value;
        M21 *= Value;
        M22 *= Value;
        M23 *= Value;
        M30 *= Value;
        M31 *= Value;
        M32 *= Value;
        M33 *= Value;
    }

    void operator/=(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FMatrix4::Division_by_zero.");
        M00 *= Inversed;
        M01 *= Inversed;
        M02 *= Inversed;
        M03 *= Inversed;
        M10 *= Inversed;
        M11 *= Inversed;
        M12 *= Inversed;
        M13 *= Inversed;
        M20 *= Inversed;
        M21 *= Inversed;
        M22 *= Inversed;
        M23 *= Inversed;
        M30 *= Inversed;
        M31 *= Inversed;
        M32 *= Inversed;
        M33 *= Inversed;
    }

    FMatrix4 operator*(FMatrix4& Mat)
    {
        return FMatrix4{M00 * Mat.M00 + M01 * Mat.M10 + M02 * Mat.M20 + M03 * Mat.M30, M00 * Mat.M01 + M01 * Mat.M11 + M02 * Mat.M21 + M03 * Mat.M31, M00 * Mat.M02 + M01 * Mat.M12 + M02 * Mat.M22 + M03 * Mat.M32, M00 * Mat.M03 + M01 * Mat.M13 + M02 * Mat.M23 + M03 * Mat.M33,
                        M10 * Mat.M00 + M11 * Mat.M10 + M12 * Mat.M20 + M13 * Mat.M30, M10 * Mat.M01 + M11 * Mat.M11 + M12 * Mat.M21 + M13 * Mat.M31, M10 * Mat.M02 + M11 * Mat.M12 + M12 * Mat.M22 + M13 * Mat.M32, M10 * Mat.M03 + M11 * Mat.M13 + M12 * Mat.M23 + M13 * Mat.M33,
                        M20 * Mat.M00 + M21 * Mat.M10 + M22 * Mat.M20 + M23 * Mat.M30, M20 * Mat.M01 + M21 * Mat.M11 + M22 * Mat.M21 + M23 * Mat.M31, M20 * Mat.M02 + M21 * Mat.M12 + M22 * Mat.M22 + M23 * Mat.M32, M20 * Mat.M03 + M21 * Mat.M13 + M22 * Mat.M23 + M23 * Mat.M33,
                        M30 * Mat.M00 + M31 * Mat.M10 + M32 * Mat.M20 + M33 * Mat.M30, M30 * Mat.M01 + M31 * Mat.M11 + M32 * Mat.M21 + M33 * Mat.M31, M30 * Mat.M02 + M31 * Mat.M12 + M32 * Mat.M22 + M33 * Mat.M32, M30 * Mat.M03 + M31 * Mat.M13 + M32 * Mat.M23 + M33 * Mat.M33};
    }

    float GetDeterminant()
    {
        return
          M00 * (M11 * M22 * M33 + M12 * M23 * M31 + M13 * M21 * M32 - M13 * M22 * M31 - M12 * M21 * M33 - M11 * M23 * M32)
        - M01 * (M10 * M22 * M33 + M12 * M23 * M30 + M13 * M20 * M32 - M13 * M22 * M30 - M12 * M20 * M33 - M10 * M23 * M32)
        + M02 * (M10 * M21 * M33 + M11 * M23 * M30 + M13 * M20 * M31 - M13 * M21 * M30 - M11 * M20 * M33 - M10 * M23 * M31)
        - M03 * (M10 * M21 * M32 + M11 * M22 * M30 + M12 * M20 * M31 - M12 * M21 * M30 - M11 * M20 * M32 - M10 * M22 * M31);
    }

    void Transpose()
    {
        float Buff = M01;
        M01 = M10;
        M10 = Buff;
        Buff = M02;
        M02 = M20;
        M20 = Buff;
        Buff = M03;
        M03 = M30;
        M30 = Buff;
        Buff = M12;
        M12 = M21;
        M21 = Buff;
        Buff = M13;
        M13 = M31;
        M31 = Buff;
        Buff = M23;
        M23 = M32;
        M32 = Buff;
    }

    FMatrix4 GetTranspose()
    {
        return {M00, M10, M20, M30,
                M01, M11, M21, M31,
                M02, M12, M22, M32,
                M03, M13, M23, M33};
    }

    void Inverse()
    {
        auto InversedD = 1.f / CHECK_NOT_ZERO(GetDeterminant(), "Determinant_is_zero.");
        {
            float M0000 = M01 * M10 + M02 * M20 + M03 * M30;
            float M0100 = M00 * M11 + M02 * M21 + M03 * M31;
            float M0200 = M00 * M12 + M01 * M22 + M03 * M32;
            float M0300 = M00 * M13 + M01 * M23 + M02 * M33;

            float M0001 = M11 * M00 + M12 * M20 + M13 * M30;
            float M0101 = M10 * M01 + M12 * M21 + M13 * M31;
            float M0201 = M10 * M02 + M11 * M22 + M13 * M32;
            float M0301 = M10 * M03 + M11 * M23 + M12 * M33;

            float M0002 = M21 * M00 + M22 * M10 + M23 * M30;
            float M0102 = M20 * M01 + M22 * M11 + M23 * M31;
            float M0202 = M20 * M02 + M21 * M12 + M23 * M32;
            float M0302 = M20 * M03 + M21 * M13 + M22 * M33;

            float M0003 = M31 * M00 + M32 * M10 + M33 * M20;
            float M0103 = M30 * M01 + M32 * M11 + M33 * M21;
            float M0203 = M30 * M02 + M31 * M12 + M33 * M22;
            float M0303 = M30 * M03 + M31 * M13 + M32 * M23;

            M00 = M0000 * InversedD;
            M01 = M0100 * InversedD;
            M02 = M0200 * InversedD;
            M03 = M0300 * InversedD;
            M10 = M0001 * InversedD;
            M11 = M0101 * InversedD;
            M12 = M0201 * InversedD;
            M13 = M0301 * InversedD;
            M20 = M0002 * InversedD;
            M21 = M0102 * InversedD;
            M22 = M0202 * InversedD;
            M23 = M0302 * InversedD;
            M30 = M0003 * InversedD;
            M31 = M0103 * InversedD;
            M32 = M0203 * InversedD;
            M32 = M0303 * InversedD;
        }
    }

    inline FMatrix4 GetInversed()
    {
        auto InversedD = 1.f / CHECK_NOT_ZERO(GetDeterminant(), "Determinant_is_zero.");
        {
            float M0000 = M11 * M22 * M33 + M12 * M23 * M31 + M13 * M21 * M32 - M11 * M23 * M32 - M12 * M21 * M33 - M13 * M22 * M31;
            float M0001 = M10 * M23 * M32 + M12 * M20 * M33 + M13 * M22 * M30 - M10 * M22 * M33 - M12 * M23 * M30 - M13 * M20 * M32;
            float M0002 = M10 * M21 * M33 + M11 * M23 * M30 + M13 * M20 * M31 - M10 * M23 * M31 - M11 * M20 * M33 - M13 * M21 * M30;
            float M0003 = M10 * M22 * M31 + M11 * M20 * M32 + M12 * M21 * M30 - M10 * M21 * M32 - M11 * M22 * M30 - M12 * M20 * M31;

            float M0100 = M01 * M23 * M32 + M02 * M21 * M33 + M03 * M22 * M31 - M01 * M22 * M33 - M02 * M23 * M31 - M03 * M21 * M32;
            float M0101 = M00 * M22 * M33 + M02 * M23 * M30 + M03 * M20 * M32 - M00 * M23 * M32 - M02 * M20 * M33 - M03 * M22 * M30;
            float M0102 = M00 * M23 * M31 + M01 * M20 * M33 + M03 * M21 * M30 - M00 * M21 * M33 - M01 * M23 * M30 - M03 * M20 * M31;
            float M0103 = M00 * M21 * M32 + M01 * M22 * M30 + M02 * M20 * M31 - M00 * M22 * M31 - M01 * M20 * M32 - M02 * M21 * M30;

            float M0200 = M01 * M12 * M33 + M02 * M13 * M31 + M03 * M11 * M32 - M01 * M13 * M32 - M02 * M11 * M33 - M03 * M12 * M31;
            float M0201 = M00 * M13 * M32 + M02 * M10 * M33 + M03 * M12 * M30 - M00 * M12 * M33 - M02 * M13 * M30 - M03 * M10 * M32;
            float M0202 = M00 * M11 * M33 + M01 * M13 * M30 + M03 * M10 * M31 - M00 * M13 * M31 - M01 * M10 * M33 - M03 * M11 * M30;
            float M0203 = M00 * M12 * M31 + M01 * M10 * M32 + M02 * M11 * M30 - M00 * M11 * M32 - M01 * M12 * M30 - M02 * M10 * M32;

            float M0300 = M01 * M13 * M22 + M02 * M11 * M23 + M03 * M12 * M21 - M01 * M12 * M23 - M02 * M13 * M21 - M03 * M11 * M22;
            float M0301 = M00 * M12 * M23 + M02 * M13 * M20 + M03 * M10 * M22 - M00 * M13 * M22 - M02 * M10 * M22 - M03 * M12 * M20;
            float M0302 = M00 * M13 * M21 + M01 * M10 * M23 + M03 * M11 * M20 - M00 * M11 * M23 - M01 * M13 * M20 - M03 * M10 * M21;
            float M0303 = M00 * M11 * M22 + M01 * M12 * M20 + M02 * M10 * M21 - M00 * M12 * M21 - M01 * M10 * M22 - M02 * M11 * M20;

            return FMatrix4
            {M0000 * InversedD, M0001 * InversedD, M0002 * InversedD, M0003 * InversedD,
             M0100 * InversedD, M0101 * InversedD, M0102 * InversedD, M0103 * InversedD,
             M0200 * InversedD, M0201 * InversedD, M0202 * InversedD, M0203 * InversedD,
             M0300 * InversedD, M0301 * InversedD, M0302 * InversedD, M0303 * InversedD}.GetTranspose();
        }
    }
};

inline std::ostream& operator<<(std::ostream& OutputStream, const FMatrix4& Matrix)
{
    OutputStream << std::setprecision(5) << std::right;
    OutputStream << std::setw(5) << Matrix.M00 << " " << std::setw(5) << Matrix.M01 << " " << std::setw(5) << Matrix.M02 << " " << std::setw(5) << Matrix.M03 << std::endl;
    OutputStream << std::setw(5) << Matrix.M10 << " " << std::setw(5) << Matrix.M11 << " " << std::setw(5) << Matrix.M12 << " " << std::setw(5) << Matrix.M13 << std::endl;
    OutputStream << std::setw(5) << Matrix.M20 << " " << std::setw(5) << Matrix.M21 << " " << std::setw(5) << Matrix.M22 << " " << std::setw(5) << Matrix.M23 << std::endl;
    OutputStream << std::setw(5) << Matrix.M30 << " " << std::setw(5) << Matrix.M31 << " " << std::setw(5) << Matrix.M32 << " " << std::setw(5) << Matrix.M33 << std::endl;
    return OutputStream;
}

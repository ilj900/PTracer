#pragma once

#include "utils.h"

#include <stdexcept>
#include <iomanip>

class FMatrix3
{
public:
    FMatrix3() : Data{0.f, 0.f, 0.f,
                      0.f, 0.f, 0.f,
                      0.f, 0.f, 0.f} {};
    FMatrix3(float M00, float M01, float M02,
             float M10, float M11, float M12,
             float M20, float M21, float M22) : Data{M00, M01, M02,
                                                     M10, M11, M12,
                                                     M20, M21, M22} {};
    FMatrix3(const FMatrix3& Mat) : Data{Mat.M00, Mat.M01, Mat.M02,
                                         Mat.M10, Mat.M11, Mat.M12,
                                         Mat.M20, Mat.M21, Mat.M22} {};
    ~FMatrix3() = default;
public:
    union {
        float Data[9];
        struct {float M00, M01, M02, M10, M11, M12, M20, M21, M22;};
    };

public:
    FMatrix3 operator+(FMatrix3& Mat)
    {
        return FMatrix3{M00 + Mat.M00, M01 + Mat.M01, M02 + Mat.M02,
                        M10 + Mat.M10, M11 + Mat.M11, M12 + Mat.M12,
                        M20 + Mat.M20, M21 + Mat.M21, M22 + Mat.M22};
    }

    FMatrix3 operator-(FMatrix3& Mat)
    {
        return FMatrix3{M00 - Mat.M00, M01 - Mat.M01, M02 - Mat.M02,
                        M10 - Mat.M10, M11 - Mat.M11, M12 - Mat.M12,
                        M20 - Mat.M20, M21 - Mat.M21, M22 - Mat.M22};
    }

    void operator+=(const FMatrix3& Mat)
    {
        M00 += Mat.M00;
        M01 += Mat.M01;
        M02 += Mat.M02;
        M10 += Mat.M10;
        M11 += Mat.M11;
        M12 += Mat.M12;
        M20 += Mat.M20;
        M21 += Mat.M21;
        M22 += Mat.M22;
    }

    void operator-=(const FMatrix3& Mat)
    {
        M00 -= Mat.M00;
        M01 -= Mat.M01;
        M02 -= Mat.M02;
        M10 -= Mat.M10;
        M11 -= Mat.M11;
        M12 -= Mat.M12;
        M20 -= Mat.M20;
        M21 -= Mat.M21;
        M22 -= Mat.M22;
    }

    FMatrix3 operator*(float Value)
    {
        return FMatrix3{M00 * Value, M01 * Value, M02 * Value,
                        M10 * Value, M11 * Value, M12 * Value,
                        M20 * Value, M21 * Value, M22 * Value};
    }

    FMatrix3 operator/(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FMatrix3::Division_by_zero.");
        return FMatrix3{M00 * Inversed, M01 * Inversed, M02 * Inversed,
                        M10 * Inversed, M11 * Inversed, M12 * Inversed,
                        M20 * Inversed, M21 * Inversed, M22 * Inversed};
    }

    void operator*=(float Value)
    {
        M00 *= Value;
        M01 *= Value;
        M02 *= Value;
        M10 *= Value;
        M11 *= Value;
        M12 *= Value;
        M20 *= Value;
        M21 *= Value;
        M22 *= Value;
    }

    void operator/=(float Value)
    {
        float Inversed = 1.f / CHECK_NOT_ZERO(Value, "FMatrix3::Division_by_zero.");
        M00 *= Inversed;
        M01 *= Inversed;
        M02 *= Inversed;
        M10 *= Inversed;
        M11 *= Inversed;
        M12 *= Inversed;
        M20 *= Inversed;
        M21 *= Inversed;
        M22 *= Inversed;
    }

    FMatrix3 operator*(FMatrix3& Mat)
    {
        // Todo: optimize?
        return FMatrix3{M00 * Mat.M00 + M01 * Mat.M10 + M02 * Mat.M20, M00 * Mat.M01 + M01 * Mat.M11 + M02 * Mat.M21, M00 * Mat.M02 + M01 * Mat.M12 + M02 * Mat.M22,
                        M10 * Mat.M00 + M11 * Mat.M10 + M12 * Mat.M20, M10 * Mat.M01 + M11 * Mat.M11 + M12 * Mat.M21, M10 * Mat.M02 + M11 * Mat.M12 + M12 * Mat.M22,
                        M20 * Mat.M00 + M21 * Mat.M10 + M22 * Mat.M20, M20 * Mat.M01 + M21 * Mat.M11 + M22 * Mat.M21, M20 * Mat.M02 + M21 * Mat.M12 + M12 * Mat.M22};
    }

    float GetDeterminant()
    {
        return M00 * M11 * M22 + M01 * M12 * M20 + M02 * M10 * M21 - M02 * M11 * M20 - M01 * M10 * M22 - M00 * M12 * M21;
    }

    void Transpose()
    {
        float Buff = M01;
        M01 = M10;
        M10 = Buff;
        Buff = M02;
        M02 = M20;
        M02 = Buff;
        Buff = M12;
        M12 = M21;
        M21 = Buff;
    }

    void Inverse()
    {
        auto InversedD = 1.f / CHECK_NOT_ZERO(GetDeterminant(), "Determinant_is_zero.");
        {
            float M0000 = M01 * M10 + M02 * M20;
            float M0100 = M00 * M11 + M02 * M21;
            float M0200 = M00 * M12 + M01 * M22;
            float M0001 = M00 * M11 + M20 * M12;
            float M0101 = M01 * M10 + M02 * M20;
            float M0201 = M02 * M10 + M22 * M11;
            float M0002 = M00 * M21 + M01 * M22;
            float M0102 = M01 * M20 + M11 * M22;
            float M0202 = M02 * M20 + M12 * M21;

            M00 = M0000 * InversedD;
            M01 = M0100 * InversedD;
            M02 = M0200 * InversedD;
            M10 = M0001 * InversedD;
            M11 = M0101 * InversedD;
            M12 = M0201 * InversedD;
            M20 = M0002 * InversedD;
            M21 = M0102 * InversedD;
            M22 = M0202 * InversedD;
        }
    }

    inline FMatrix3 GetInversed()
    {
        auto InversedD = 1.f / CHECK_NOT_ZERO(GetDeterminant(), "Determinant_is_zero.");
        {
            float M0000 = M01 * M10 + M02 * M20;
            float M0100 = M00 * M11 + M02 * M21;
            float M0200 = M00 * M12 + M01 * M22;
            float M0001 = M00 * M11 + M20 * M12;
            float M0101 = M01 * M10 + M02 * M20;
            float M0201 = M02 * M10 + M22 * M11;
            float M0002 = M00 * M21 + M01 * M22;
            float M0102 = M01 * M20 + M11 * M22;
            float M0202 = M02 * M20 + M12 * M21;

            return {M0000 * InversedD, M0100 * InversedD, M0200 * InversedD,
                    M0001 * InversedD, M0101 * InversedD, M0201 * InversedD,
                    M0002 * InversedD, M0102 * InversedD, M0202 * InversedD};
        }
    }
};

inline std::ostream& operator<<(std::ostream& OutputStream, const FMatrix3& Matrix)
{
    OutputStream << std::setprecision(5) << std::right;
    OutputStream << std::setw(5) << Matrix.M00 << " " << std::setw(5) << Matrix.M01 << " " << std::setw(5) << Matrix.M02 << std::endl;
    OutputStream << std::setw(5) << Matrix.M10 << " " << std::setw(5) << Matrix.M11 << " " << std::setw(5) << Matrix.M12 << std::endl;
    OutputStream << std::setw(5) << Matrix.M20 << " " << std::setw(5) << Matrix.M21 << " " << std::setw(5) << Matrix.M22 << std::endl;
    return OutputStream;
}

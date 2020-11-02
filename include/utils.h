#pragma once

#include <cinttypes>
#include <stdexcept>

struct ColorRGB
{
    std::uint8_t R;
    std::uint8_t G;
    std::uint8_t B;
};

struct ColorRGBA
{
    std::uint8_t R;
    std::uint8_t G;
    std::uint8_t B;
    std::uint8_t A;
};

inline float CHECK_NOT_ZERO(float X, std::string&& FailMassage)
{
    if (X == 0.f || X == -0.f)
    {
        throw std::runtime_error(FailMassage);
    }
    return X;
}
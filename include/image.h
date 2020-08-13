#pragma once

#include <cinttypes>
#include <vector>

struct RGBA
{
    std::uint8_t R;
    std::uint8_t G;
    std::uint8_t B;
    std::uint8_t A;
};

class UImage
{
public:
    UImage(std::uint32_t WidthIn, std::uint32_t HeightIn): Width(WidthIn), Height(HeightIn) {Data.resize(Width*Height);};
    inline std::uint32_t GetWidth() {return Width;};
    inline std::uint32_t GetHeight() {return Height;};
    RGBA& operator[](std::uint32_t index) {return Data[index];};
    void* GetData() {return Data.data();};
private:
    std::uint32_t Width;
    std::uint32_t Height;
    std::vector<RGBA> Data;
};
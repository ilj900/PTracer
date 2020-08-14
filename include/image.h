#pragma once

#include <cinttypes>
#include <vector>
#include "utils.h"

class UImage
{
public:
    UImage(std::uint32_t WidthIn, std::uint32_t HeightIn, ColorRGBA DefaaultColor = {0, 0, 0, 0}): Width(WidthIn), Height(HeightIn) {Data.resize(Width*Height, DefaaultColor);};
    inline std::uint32_t GetWidth() {return Width;};
    inline std::uint32_t GetHeight() {return Height;};
    ColorRGBA& operator[](std::uint32_t index) {return Data[index];};
    void* GetData() {return Data.data();};
private:
    std::uint32_t Width;
    std::uint32_t Height;
    std::vector<ColorRGBA> Data;
};
#pragma once

#include "stb_image_write.h"
#include "utils.h"

#include <cinttypes>
#include <vector>
#include <string>

class UImage
{
public:
    UImage(std::uint32_t WidthIn, std::uint32_t HeightIn, ColorRGBA DefaaultColor = {0, 0, 0, 0}): Width(WidthIn), Height(HeightIn)
    {
        if (WidthIn % 2 != 0 || HeightIn % 2 != 0)
        {
            throw std::exception("UImage doesn't support odd size");
        }
        Data.resize(Width*Height, DefaaultColor);
    };
    inline std::uint32_t GetWidth() {return Width;};
    inline std::uint32_t GetHeight() {return Height;};
    ColorRGBA& operator[](std::uint32_t index) {return Data[index];};
    void* GetData() {return Data.data();};
    bool SaveImage(std::string path)
    {
        stbi_write_png("Test.png", Width, Height, 4, Data.data(), 0);
        return true;
    };
private:
    std::uint32_t Width;
    std::uint32_t Height;
    std::vector<ColorRGBA> Data;
};
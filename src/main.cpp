#include "stb_image_write.h"
#include "vector4.h"

#include <vector>
#include <cstdint>
int main()
{
    std::uint32_t Width = 256;
    std::uint32_t Height = 256;
    std::uint32_t NumberOfChannels = 4;
    std::vector<std::uint8_t> Image(Width * Height * NumberOfChannels);
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            Image[(i * Width + j) * NumberOfChannels] = 255;
            Image[(i * Width + j) * NumberOfChannels + 1] = 0;
            Image[(i * Width + j) * NumberOfChannels + 2] = 255;
            Image[(i * Width + j) * NumberOfChannels + 3] = 255;
        }
    }
    stbi_write_png("Test.png", Width, Height, NumberOfChannels, Image.data(), 0);
    return 0;
}

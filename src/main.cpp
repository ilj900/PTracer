#include "stb_image_write.h"
#include "utils.h"
#include "sphere.h"
#include "camera.h"
#include "randomizer.h"

#include <cstdint>

int main()
{
    std::uint32_t Width = 1920;
    std::uint32_t Height = 1080;
    std::uint32_t NumberOfChannels = 4;
    std::vector<FShape*> Shapes{new FSphere{{4.f, 4.f, 10.f}, {255, 0, 0, 255}, 2.f},
                                new FSphere{{5.f, 7.f, 6.f}, {0, 128, 192, 255}, 3.f},
                                new FSphere{{-3.f, 0.f, 25.f}, {0, 255, 0, 255}, 2.f},
                                new FSphere{{-90.f, -45.f, 120.f}, {255, 0, 128, 255}, 10.f}};

    UImage Image(Width, Height, {20, 15, 40, 255});
    FVector3 CameraCenter(0.f, 0.f, -10.f);
    FVector3 CameraDirection( 0.f, 0.f, 1.f);
    Camera Cam(CameraCenter, CameraDirection, 90.f, 100.f, 0.1f, Image);

    for (std::uint32_t Y = 0; Y < Height; ++Y)
    {
        for (std::uint32_t X = 0; X < Width; ++X)
        {
            FRay Ray = Cam.GenerateRay(X, Y);
            FRay RayOut;
            for (auto item : Shapes)
            {
                if (item->Intersect(Ray, RayOut))
                {
                    auto Angle = GetAngle(Ray.Direction, RayOut.Direction) / 3.1415926;
                    std::uint8_t AdjustedColor = std::uint8_t(255.f * Angle);
                    Image[Y * Width + X] = item->Albedo;
                }
            }
        }
    }
    stbi_write_png("Test.png", Width, Height, NumberOfChannels, Image.GetData(), 0);
    return 0;
}

#include "stb_image_write.h"
#include "utils.h"
#include "sphere.h"
#include "camera.h"

#include <vector>
#include <cstdint>
#include <cmath>

int main()
{
    std::uint32_t Width = 1920;
    std::uint32_t Height = 1080;
    std::uint32_t NumberOfChannels = 4;
    FVector3 SphereCenter(4.f, 4.f, 10.f);
    FSphere Sphere(SphereCenter, 2.f);

    UImage Image(Width, Height);
    FVector3 CameraCenter(0.f, 0.f, -10.f);
    FVector3 CameraDirection( 0.f, 0.f, 1.f);
    Camera Cam(CameraCenter, CameraDirection, 90.f, 100.f, 0.1f, Image);

    for (std::uint32_t Y = 0; Y < Height; ++Y)
    {
        for (std::uint32_t X = 0; X < Width; ++X)
        {
            FRay Ray = Cam.GenerateRay(X, Y);
            FRay RayOut;
            if (Sphere.Intersect(Ray, RayOut))
            {
                auto Angle = GetAngle(Ray.Direction, RayOut.Direction) / 3.1415926;
                std::uint8_t AdjustedColor = std::uint8_t(255.f * Angle);
                Image[Y * Width + X].R = AdjustedColor;
                Image[Y * Width + X].G = 0;
                Image[Y * Width + X].B = 0;
                Image[Y * Width + X].A = 255;
            }
            else
            {
                Image[Y * Width + X].R = 20;
                Image[Y * Width + X].G = 15;
                Image[Y * Width + X].B = 40;
                Image[Y * Width + X].A = 255;
            }
        }
    }
    stbi_write_png("Test.png", Width, Height, NumberOfChannels, Image.GetData(), 0);
    return 0;
}

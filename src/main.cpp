#include "stb_image_write.h"
#include "vector4.h"
#include "utils.h"
#include "sphere.h"

#include <vector>
#include <cstdint>
#include <cmath>

int main()
{
    std::int32_t Width = 256;
    std::int32_t Height = 256;
    std::int32_t NumberOfChannels = 4;
    std::vector<ColorRGBA> Image(Width * Height);
    FVector3 SphereCenter(1.f, 2.f, 15.f);
    FSphere Sphere(SphereCenter, 2.f);

    FVector3 CameraCenter(0.f, 0.f, -1.f);
    FVector3 CameraDirection( 0.f, 0.f, 1.f);
    FVector3 CameraRightDirection(-1.f, 0.f, 0.f);
    FVector3 CameraUpDirection(0.f, 1.f, 0.f);
    float CameraAngle = 90.f * 3.1415926536f / 180.f;
    float MaxTraceDistance = 100.f;
    float RayVStep = CameraAngle / float(Height);
    float RayHStep = CameraAngle / float(Width);
    FVector3 CameraFarPoint = CameraCenter + CameraDirection * MaxTraceDistance;

    float VerticalCameraAngle = -(RayVStep / 2.f + (Height / 2.f) * RayVStep);
    for (std::int32_t i = 0; i < Height; ++i, VerticalCameraAngle += RayVStep)
    {
        FVector3 VerticalOffset = CameraRightDirection * std::tan(VerticalCameraAngle);
        float HorizontalCameraAngle = -(RayHStep / 2.f + (Width / 2.f) * RayHStep);
        for (std::int32_t j = 0; j < Width; ++j, HorizontalCameraAngle += RayHStep)
        {
            FVector3 HorizontalOffset = CameraUpDirection * std::tan(HorizontalCameraAngle);
            auto Offset = VerticalOffset + HorizontalOffset;
            auto RayDirection = CameraFarPoint + Offset * MaxTraceDistance;
            FRay Ray(CameraCenter, RayDirection);
            FRay RayOut;
            if (Sphere.Intersect(Ray, &RayOut))
            {
                Image[i * Width + j].R = 255;
                Image[i * Width + j].G = 0;
                Image[i * Width + j].B = 0;
                Image[i * Width + j].A = 255;
            }
            else
            {
                Image[i * Width + j].R = 0;
                Image[i * Width + j].G = 255;
                Image[i * Width + j].B = 0;
                Image[i * Width + j].A = 255;
            }
        }
    }
    stbi_write_png("Test.png", Width, Height, NumberOfChannels, Image.data(), 0);
    return 0;
}

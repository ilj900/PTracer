#pragma once

#include "vector3.h"
#include "image.h"
#include "ray.h"
#include "linmath.h"

#define MY_PI 3.14159265359f
#define MY_RADIAN 57.2957795131f
class Camera
{
public:
    Camera(FVector3& CameraCenter, Direction3& CameraDirection, float FOV, float FarDistance, float NearDistance, UImage& ImageIn):
        CameraCenter(CameraCenter), CameraDirection(CameraDirection), HFOV(FOV / MY_RADIAN), FarDistance(FarDistance), NearDistance(NearDistance), Image(ImageIn)
        {
        AspectRate = float(ImageIn.GetWidth()) / float(ImageIn.GetHeight());
        VFOV = std::atan(std::tan(HFOV * 0.5f) * AspectRate);
        CameraDirection.Normalize();
        NearPlaneCenterPoint = CameraCenter + CameraDirection * NearDistance;
        FarPlaneCenterPoint = CameraCenter + CameraDirection * FarDistance;
        CameraRight = Cross(FVector3{0.f, 1.f, 0.f}, CameraDirection);
        CameraUp = Cross(CameraDirection, CameraRight);
        HalfImageWidth = Image.GetWidth() / 2;
        HalfImageHeight = Image.GetHeight() / 2;
        GenerateOffsets();
        };
    ~Camera() = default;

    void GenerateOffsets()
    {
        HOffsets.resize(HalfImageWidth);
        auto HStep = std::tan(HFOV / 2.f) * FarDistance / HalfImageWidth;
        auto Step = HStep * 0.5f;
        for (std::uint32_t i = 0; i < HalfImageWidth; ++i)
        {
            HOffsets[i] = Step;
            Step += HStep;
        }
        VOffsets.resize(HalfImageHeight);
        auto VStep = std::tan(VFOV / 2.f) * FarDistance / HalfImageHeight;
        Step = VStep * 0.5f;
        for (std::uint32_t i = 0; i < HalfImageHeight; ++i)
        {
            VOffsets[i] = Step;
            Step += VStep;
        }
    }

    FRay GenerateRay(std::uint32_t X, std::uint32_t Y)
    {
        FRay Ray;
        Ray.Origin = CameraCenter;
        FVector3 End = FarPlaneCenterPoint;
        if (X >= Image.GetWidth() || Y >= Image.GetHeight())
        {
            throw std::exception("GenerateRay failed cause passed X value is greater that image width");
        }

        if (X < HalfImageWidth)
        {
            End -= CameraRight * HOffsets[HalfImageWidth - X - 1];
        }
        else
        {
            End += CameraRight * HOffsets[X - HalfImageWidth];
        }
        if (Y < HalfImageHeight)
        {
            End += CameraUp * VOffsets[HalfImageHeight - Y - 1];
        }
        else
        {
            End -= CameraUp * VOffsets[Y - HalfImageHeight];
        }
        Ray.Direction = End - Ray.Origin;
        return Ray;
    };

    void Render() {};

private:
    FVector3 CameraCenter;
    FVector3 NearPlaneCenterPoint;
    FVector3 FarPlaneCenterPoint;
    Direction3 CameraDirection;
    Direction3 CameraRight;
    Direction3 CameraUp;
    float AspectRate;
    float HFOV;
    float VFOV;
    float FarDistance;
    float NearDistance;
    float HStep;
    float VStep;
    std::vector<float> TangentValues;
    std::vector<float> HOffsets;
    std::vector<float> VOffsets;
    UImage& Image;
    std::uint32_t HalfImageWidth;
    std::uint32_t HalfImageHeight;
};
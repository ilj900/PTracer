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
        AspectRate = float(ImageIn.GetHeight()) / float(ImageIn.GetWidth());
        VFOV = HFOV * AspectRate;
        CameraDirection.Normalize();
        NearPlaneCenterPoint = CameraCenter + CameraDirection * NearDistance;
        FarPlaneCenterPoint = CameraCenter + CameraDirection * FarDistance;
        CameraRight = Cross(FVector3{0.f, 1.f, 0.f}, CameraDirection);
        CameraUp = Cross(CameraDirection, CameraRight);
        HalfImageWidth = Image.GetWidth() / 2;
        HalfImageHeight = Image.GetHeight() / 2;
        GenerateTangentValues();
        };
    ~Camera() = default;

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
            End -= CameraRight * TangentValues[HalfImageWidth - X - 1];
        }
        else
        {
            End += CameraRight * TangentValues[X - HalfImageWidth];
        }
        if (Y < HalfImageHeight)
        {
            End += CameraUp * TangentValues[HalfImageHeight - Y - 1];
        }
        else
        {
            End -= CameraUp * TangentValues[Y - HalfImageHeight];
        }
        Ray.Direction = End - Ray.Origin;
        return Ray;
    };

    void GenerateTangentValues()
    {
        float HalfAngle;
        std::uint32_t HalfSize;
        if (HalfImageWidth > HalfImageHeight)
        {
            HalfSize = HalfImageWidth;
            HalfAngle = HFOV / 2.f;
        }
        else
        {
            HalfSize = Image.GetHeight() / 2;
            HalfAngle = VFOV / 2.f;
        }
        auto AngleStep = HalfAngle / HalfSize;
        auto Angle = AngleStep * 0.5f;
        TangentValues.resize(HalfSize);
        for (auto i = 0u; i < HalfSize; ++i)
        {
            TangentValues[i] = std::tan(Angle) * FarDistance;
            Angle += AngleStep;
        }
    }

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
    FVector3 TopLeftPoint;
    std::vector<float> TangentValues;
    UImage& Image;
    std::uint32_t HalfImageWidth;
    std::uint32_t HalfImageHeight;
};
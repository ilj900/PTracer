#pragma once

#include "vector3.h"
#include "image.h"
#include "ray.h"
#include "linmath.h"

class Camera
{
public:
    Camera(FVector3& CameraCenter, Direction3& CameraDirection, float FOV, float FarDistance, float NearDistance, UImage& ImageIn):
        CameraCenter(CameraCenter), CameraDirection(CameraDirection), HFOV(FOV), FarDistance(FarDistance), NearDistance(NearDistance), Image(ImageIn)
        {
        VFOV = HFOV * Image.GetHeight() / Image.GetWidth();
        NearPlaneCenterPoint = CameraCenter + CameraDirection * NearDistance;
        FarPlaneCenterPoint = CameraCenter + CameraDirection * FarDistance;
        CameraDirection.Normalize();
        CameraRight = Cross(FVector3{0.f, 1.f, 0.f}, CameraDirection);
        CameraUp = Cross(CameraDirection, CameraRight);
        AspectRate = float(ImageIn.GetHeight()) / float(ImageIn.GetWidth());
        float FarPlaneWidth = FarDistance * 2.f * std::tan(HFOV * 0.5f * 3.1415926536f / 180.f);
        float FarPlaneHeight = FarPlaneWidth * AspectRate;
        HStep = FarPlaneWidth / Image.GetWidth();
        VStep = FarPlaneHeight / Image.GetHeight();

        TopLeftPoint = FarPlaneCenterPoint - (CameraRight * (FarPlaneWidth * 0.5f));
        TopLeftPoint += CameraUp * (FarPlaneHeight * 0.5f);
        };
    ~Camera() = default;

    FRay GenerateRay(float X, float Y)
    {
        if (X <= 0.f || X >= 1919.f)
        {
            X = X;
        }
        if (Y <= 0.f || Y >= 1079.f)
        {
            Y = Y;
        }
        FRay Ray;
        Ray.Origin = CameraCenter;
        FVector3 End = TopLeftPoint;
        End += CameraRight * X * HStep;
        End -= CameraUp * Y * VStep;
        Ray.Direction = End - Ray.Origin;
        return Ray;
    };

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
    UImage& Image;
};
#pragma once

#include "vector3.h"

class Camera
{
public:
    Camera() = default;
    Camera(FVector3& CameraCenter, Direction3& CameraDirection, float FOV, float FarDistance, float NearDistance, std::uint32_t ImageWidth, std::uint32_t ImageHeight);
    ~Camera() = default;
private:
    FVector3 CameraCenter;
    Direction3 CameraDirection;
    float FOV;
    float FarDistance;
    float NearDistance;
    std::uint32_t ImageWidth;
    std::uint32_t ImageHeight;
};
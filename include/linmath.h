#pragma once

#include "ray.h"

Direction3 Reflect(Direction3& RayDirection, Direction3& Normal)
{
    Direction3 ReflectedDirection = Normal * 2 * (Normal * RayDirection) - RayDirection;
    return ReflectedDirection;
}

Direction3 Reflect(Direction3&& RayDirection, Direction3& Normal)
{
    Direction3 ReflectedDirection = Normal * 2 * (Normal * RayDirection) - RayDirection;
    return ReflectedDirection;
}

float Dot(FVector3& VecA, FVector3& VecB)
{
    return VecA.X * VecB.X + VecA.Y * VecB.Y + VecA.Z * VecB.Z;
}

FVector3 Cross(const FVector3& A, const FVector3& B)
{
    return {A.Y * B.Z - A.Z * B.Y, A.Z * B.X - A.X * B.Z, A.X * B.Y - A.Y * B.X};
}

float GetCos(FVector3 VecA, FVector3 VecB)
{
    VecA.Normalize();
    VecB.Normalize();
    return Dot(VecA, VecB);
}

float GetAngle(FVector3 VecA, FVector3 VecB)
{
    VecA.Normalize();
    VecB.Normalize();
    return std::acos(Dot(VecA, VecB));
}

bool SolveQuadratic(float A, float B, float C, float& X1, float& X2)
{
    auto D = B * B - 4.f * A * C;
    if (D < 0.f)
        return false;
    auto SqrtD = std::sqrt(D);
    X1 = (-B - SqrtD) / (2.f * A);
    X2 = (-B + SqrtD) / (2.f * A);
    return true;
}

bool GetSmallestNonNegative(float A, float B, float& Result)
{
    if (A < 0 && B < 0)
    {
        return false;
    }
    if (A < 0)
    {
        Result = B;
        return true;
    }
    if (B < 0)
    {
        Result = A;
        return true;
    }
    if (A < B)
    {
        Result = A;
        return true;
    }
    else
    {
        Result = B;
        return true;
    }

}
#pragma once

#include <vector3.h>

float Dot(FVector3& VecA, FVector3& VecB)
{
    return VecA.X * VecB.X + VecA.Y * VecB.Y + VecA.Z * VecB.Z;
}

float GetAngle(FVector3 VecA, FVector3 VecB)
{
    VecA.Normalize();
    VecB.Normalize();
    return (Dot(VecA, VecB));
}

bool SolveQuadratic(float A, float B, float C, float& X1, float& X2)
{
    auto D = B * B - 4.f * A * C;
    if (D < 0.f)
        return false;
    auto SqrtD = std::sqrt(D);
    X1 = (-B - SqrtD) / (2.f * A);
    X2 = (-B + SqrtD) / (2.f * A);
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

//bool RaySphereIntersection(FRay& RayIn, FSphere& SphereIn)
//{
//    // Translate Ray into sphere center coordinates
//    auto RayOrigin = RayIn.Origin - SphereIn.Center;
//    auto A = RayIn.Direction.Len2();
//    auto B = 2.f * (Dot(RayOrigin, RayIn.Direction));
//    auto C = RayOrigin.Len2() - SphereIn.Radius * SphereIn.Radius;
//    float X1, X2;
//    if (SolveQuadratic(A, B, C, X1, X2))
//    {
////        float X;
////        if (!GetSmallestNonNegative(X1, X2, X))
////        {
////            return false;
////        }
//    return true;
//    }
//    return false;
//}
#pragma once

#include "shape.h"
#include "intersections.h"
#include "linmath.h"

class FSphere: public FShape
{
public:
    FSphere() = default;
    FSphere(FVector3 &CenterIn, float RadiusIn): Center(CenterIn), Radius(RadiusIn) {};
    ~FSphere() = default;

public:
    FVector3 Center;
    float Radius;
    virtual bool Intersect(FRay RayIn, FRay& RayOut) override
    {
        // Translate Ray into sphere center coordinates
        auto RayOrigin = RayIn.Origin - Center;
        auto A = RayIn.Direction.Len2();
        auto B = 2.f * (Dot(RayOrigin, RayIn.Direction));
        auto C = RayOrigin.Len2() - Radius * Radius;
        float X1, X2;
        if (SolveQuadratic(A, B, C, X1, X2))
        {
            float X;
            if (GetSmallestNonNegative(X1, X2, X))
            {
                auto IntersectedRay = RayIn.Origin + RayIn.Direction * X;
                auto Normal = IntersectedRay - Center;
                auto ReflectedRayDirection = Reflect(-IntersectedRay, Normal);
                RayOut = FRay(IntersectedRay, ReflectedRayDirection);
                return true;
            }
        }
        return false;
    }
};
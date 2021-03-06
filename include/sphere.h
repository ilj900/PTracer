#pragma once

#include "shape.h"
#include "linmath.h"

class FSphere: public FShape
{
public:
    FSphere() = default;
    FSphere(FVector3&& PositionIn, ColorRGBA&& AlbedoIn, float RadiusIn): FShape(PositionIn, AlbedoIn), Radius(RadiusIn) {};
    FSphere(FVector3& PositionIn, ColorRGBA& AlbedoIn, float RadiusIn): FShape(PositionIn, AlbedoIn), Radius(RadiusIn) {};
    ~FSphere() = default;

    virtual bool Intersect(FRay RayIn, FRay& RayOut, FVector3& Normal) override
    {
        // Translate Ray into sphere center coordinates
        auto RayOrigin = RayIn.Origin - Position;
        auto A = RayIn.Direction.Len2();
        auto B = 2.f * (Dot(RayOrigin, RayIn.Direction));
        auto C = RayOrigin.Len2() - Radius * Radius;
        float X1, X2;
        if (SolveQuadratic(A, B, C, X1, X2))
        {
            float X;
            if (GetSmallestNonNegative(X1, X2, X))
            {
                if (X > 1.f)
                {
                    return false;
                }
                auto IntersectionPoint = RayIn.Origin + RayIn.Direction * X;
                Normal = IntersectionPoint - Position;
                Normal.Normalize();
                auto ReflectedRayDirection = Reflect(-RayIn.Direction, Normal);
                RayOut = FRay(IntersectionPoint, ReflectedRayDirection);
                return true;
            }
        }
        return false;
    }

public:
    float Radius;
};
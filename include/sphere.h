#pragma once

#include "shape.h"
#include "intersections.h"

class FSphere: public FShape
{
public:
    FSphere() = default;
    FSphere(FVector3 &CenterIn, float RadiusIn): Center(CenterIn), Radius(RadiusIn) {};
    ~FSphere() = default;

public:
    FVector3 Center;
    float Radius;
    virtual bool Intersect(FRay& RayIn, FRay* RayOut = nullptr) override
    {
        // Translate Ray into sphere center coordinates
        auto RayOrigin = RayIn.Origin - Center;
        auto A = RayIn.Direction.Len2();
        auto B = 2.f * (Dot(RayOrigin, RayIn.Direction));
        auto C = RayOrigin.Len2() - Radius * Radius;
        float X1, X2;
        if (SolveQuadratic(A, B, C, X1, X2))
        {
            return true;
        }
        return false;
    }
};
#pragma once

#include "shape.h"
#include "linmath.h"

class FTriangle : public FShape
{
public:
    FTriangle() = default;
    FTriangle(FVector3&& PositionIn, ColorRGBA&& AlbedoIn, FVector3&& P1, FVector3&& P2, FVector3&& P3): FShape(PositionIn, AlbedoIn)
    {
        Points[0] = P1;
        Points[1] = P2;
        Points[2] = P3;
    };
    //FTriangle(FVector3 PositionIn, ColorRGBA AlbedoIn, FVector3 P1, FVector3 P2, FVector3 P3): FShape(PositionIn, AlbedoIn), Points{P1, P2, P3}{};
    ~FTriangle();

    virtual bool Intersect(FRay RayIn, FRay &RayOut, FVector3& Normal) override
    {
        auto E1 = Points[1] - Points[0];
        auto E2 = Points[2] - Points[0];

        auto PVec = Cross(RayIn.Direction, E2);
        auto Det = E1 * PVec;

        if (Det < 0.000001f && Det > -0.000001f)
            return false;

        auto InvD = 1 / Det;
        auto TVec = RayIn.Origin - Points[0];

        auto U = TVec * PVec * InvD;
        if (U < 0 || U > 1)
            return false;

        auto QVec = Cross(TVec, E1);
        auto V = RayIn.Direction * QVec * InvD;
        if (V < 0 || U + V > 1)
            return false;
        return true;
    }

public:
    FVector3 Points[3];
};
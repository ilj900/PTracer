#pragma once

#include "matrix4.h"

class FTransformations
{
    static FMatrix4 GetTranslation4(float X, float Y, float Z)
    {
        return FMatrix4{1.f, 0.f, 0.f, X,
                        0.f, 1.f, 0.f, Y,
                        0.f, 0.f, 1.f, Z,
                        0.f, 0.f, 0.f, 1.f};
    }
};
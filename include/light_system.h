#pragma once

#include "light.h"

namespace LightSystem
{
    int AddLight(Vector4& Position);
    int Update();
    Vector4 CalculateLightForPoint(const Vector4& Position, const Vector4& Normal);
}


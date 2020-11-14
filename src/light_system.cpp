#include "light_system.h"

#include <vector>

namespace LightSystem
{
    std::vector<FLight> Lights;

    int LightSystem::AddLight(Vector4 &Position) {
        Lights.push_back(FLight(FVector4{.0f, 0.f, 0.f, 0.f}));
        return 0;
    }

    Vector4 GetColor(const Vector4& Position, const Vector4& Normal)
    {
        return FVector4{};
    }
}

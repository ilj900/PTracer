#pragma once

#include <random>
#include <functional>

namespace Random
{
    static std::default_random_engine Generator;

    auto GetUniformInt32Distributor(std::int32_t Bot, std::int32_t Top)
    {
        if (Bot > Top)
        {
            throw std::exception(__FUNCTION__);
        }
        static std::uniform_int_distribution<std::int32_t> Distribution(Bot, Top);
        return std::bind (Distribution, Generator);
    }

    auto GetUniformUInt32Distributor(std::uint32_t Bot, std::uint32_t Top)
    {
        if (Bot > Top)
        {
            throw std::exception(__FUNCTION__);
        }
        static std::uniform_int_distribution<std::uint32_t> Distribution(Bot, Top);
        return std::bind (Distribution, Generator);
    }

    auto GetUniformRealDistributor(float Bot, float Top)
    {
        if (Bot > Top)
        {
            throw std::exception(__FUNCTION__);
        }
        static std::uniform_real_distribution<> Distribution(Bot, Top);
        return std::bind (Distribution, Generator);
    }
}
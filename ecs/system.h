#pragma once

#include "entity.h"

#include <set>

class ISystem
{
public:
    virtual ~ISystem() = default;
    std::set<FEntity> Entities;
};
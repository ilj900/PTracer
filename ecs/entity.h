#pragma once

#include <cinttypes>
#include <bitset>
#include <queue>
#include <array>
#include <unordered_map>

// Entity is simply and ID, alias
using FEntity = std::uint32_t;

// Maximum number of entities
const FEntity MAX_ENTITIES = 4096u;

using FComponentType = std::uint8_t;

const FComponentType MAX_COMPONENTS = 255u;

using FSignature = std::bitset<MAX_COMPONENTS>;
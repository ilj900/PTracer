#pragma once

#include "entity.h"

#include <cassert>

class FEntityManager {
public:

    // Constructor fills the queue with all available entities
    FEntityManager()
    {
        for (FEntity Entity = 0u; Entity < MAX_ENTITIES; ++Entity) {
            AvailableEntities.push(Entity);
        }
    }

    // The first available entity will be popped from the queue and returned
    FEntity CreateEntity()
    {
        assert(LivingEntityCount < MAX_ENTITIES && "Too many entities in existance.");

        FEntity Entity = AvailableEntities.front();
        AvailableEntities.pop();
        ++LivingEntityCount;

        return Entity;
    }

    // Will push back the entity back into the queue
    void DestroyEntity(FEntity Entity)
    {
        assert(Entity < MAX_ENTITIES && "Entity out of range.");

        Signatures[Entity].reset();

        AvailableEntities.push(Entity);
        --LivingEntityCount;
    }

    // Every entity has a signature thar can tell which components does the entity consist of
    void SetSignature(FEntity Entity, FSignature Signature)
    {
        assert(Entity < MAX_ENTITIES && "Entity out of range.");
        Signatures[Entity] = Signature;
    }

    // Get signature of an entity
    FSignature GetSignature(FEntity Entity)
    {
        assert(Entity < MAX_ENTITIES && "Entity out of range.");

        return Signatures[Entity];
    }

private:
    std::queue<FEntity> AvailableEntities;
    std::array<FSignature, MAX_ENTITIES> Signatures;
    uint32_t LivingEntityCount;
};
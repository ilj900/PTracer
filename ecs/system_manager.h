#pragma once

#include "entity.h"
#include "system.h"

#include <cassert>
#include <memory>
#include <unordered_map>

class FSystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* TypeName = typeid(T).name();

        assert(Systems.find(TypeName) == Systems.end() && "Registering system more than once.");

        auto System = std::make_shared<T>();
        Systems.insert({TypeName, System});
        return System;
    }

    template<typename T>
    void SetSignature(FSignature Signature)
    {
        const char* TypeName = typeid(T).name();

        assert(Systems.find(TypeName) != Systems.end() && "System used before registered.");

        Signatures.insert({TypeName, Signature});
    }

    void EntityDestroyed(FEntity Entity)
    {
        for (auto const& Pair : Systems)
        {
            Pair.second->Entities.erase(Entity);
        }
    }

    // If Entity's signature changed with either add it to some system
    // Or remove it form it
    void EntitySignatureChanged(FEntity Entity, FSignature Signature)
    {
        for (auto const& Pair : Systems)
        {
            auto const& Type = Pair.first;
            auto const& System = Pair.second;
            auto const& SystemSignature = Signatures[Type];

            if ((Signature & SystemSignature) == SystemSignature)
            {
                System->Entities.insert(Entity);
            }
            else
            {
                System->Entities.erase(Entity);
            }
        }
    }

private:
    std::unordered_map<const char*, FSignature> Signatures{};

    std::unordered_map<const char*, std::shared_ptr<ISystem>> Systems{};
};

#pragma once

#include <cinttypes>
#include <bitset>
#include <queue>
#include <array>
#include <unordered_map>

namespace ECS {

// Entity is simply and ID, alias
    using Entity = std::uint32_t;

// Maximum number of entities
    const Entity MAX_ENTITIES = 4096;

    using ComponentType = std::uint8_t;

    const ComponentType MAX_COMPONENTS = 256;

    using Signature = std::bitset<MAX_COMPONENTS>;

    class EntityManager {
    public:
        EntityManager();

        Entity CreateEntity();

        void DestroyEntity(Entity EntityIn);

        void SetSignature(Entity EntityIn, Signature SignatureIn);

        Signature GetSignature(Entity EntityIn);

    private:
        std::queue<Entity> AvailableEntities{};
        std::array<Signature, MAX_ENTITIES> Signatures{};
        uint32_t LivingEntityCount{};
    };

    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity EntityIn) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        void InsertData(Entity EntityIn, T Component);
        void RemoveData(Entity EntityIn);
        T& GetData(Entity EntityIn);
        void EntityDestroyed(Entity EntityIn) override;
    private:
        std::array<T, MAX_ENTITIES> ComponentArray;
        std::unordered_map<Entity, size_t> EntityToIndexMap;
        std::unordered_map<size_t, Entity> IndexToEntityMap;
        size_t Size;
    };
}
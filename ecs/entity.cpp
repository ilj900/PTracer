#include "entity.h"
#include "cassert"

namespace ECS
{
    EntityManager::EntityManager()
    {
        for (Entity i = 0; i < MAX_ENTITIES; ++i)
        {
            AvailableEntities.push(i);
        }
    }

    Entity EntityManager::CreateEntity()
    {
        assert(LivingEntityCount < MAX_ENTITIES && "Too many entities in existance.");

        Entity Id = AvailableEntities.front();
        AvailableEntities.pop();
        ++LivingEntityCount;

        return Id;
    }

    void EntityManager::DestroyEntity(Entity EntityIn)
    {
        assert(EntityIn < MAX_ENTITIES && "Entity out of range.");

        Signatures[EntityIn].reset();

        AvailableEntities.push(EntityIn);
        --LivingEntityCount;
    }

    void EntityManager::SetSignature(Entity EntityIn, Signature SignatureIn)
    {
        assert(EntityIn < MAX_ENTITIES && "Entity out of range.");
        Signatures[EntityIn] = SignatureIn;
    }

    template<typename T>
    void ComponentArray<T>::InsertData(Entity EntityIn, T Component)
    {
        assert(EntityToIndexMap.find(EntityIn) == EntityToIndexMap.end() && "Component added to same entity more than once.");

        size_t NewIndex = Size;
        EntityToIndexMap[EntityIn] = newIndex;
        IndexToEntityMap[NewIndex] = entity;
        ComponentArray[NewIndex] = Component;
        ++Size;
    }

    template<typename T>
    void ComponentArray<T>::RemoveData(Entity EntityIn)
    {
        assert(EntityToIndexMap.find(EntityIn) != EntityToIndexMap.end() && "Removing non-existent component.");

        // Assign the last element of the array to the removed one
        size_t IndexOfRemovedEntity = EntityToIndexMap[entity];
        size_t IndexOfLastElement = Size - 1;
        ComponentArray[IndexOfRemovedEntity] = ComponentArray[IndexOfLastElement];

        // Update map to point to moved spot
        Entity EntityOfLastElement = IndexToEntityMap[IndexOfLastElement];
        EntityToIndexMap[EntityOfLastElement] = IndexOfRemovedEntity;
        IndexToEntityMap[IndexOfRemovedEntity] = EntityOfLastElement;

        EntityToIndexMap.erase(EntityIn);
        IndexToEntityMap.erase(IndexOfLastElement);
        --Size;
    }

    template<typename T>
    T& ComponentArray<T>::GetData(Entity EntityIn)
    {
        assert(EntityToIndexMap.find(EntityIn) != EntityToIndexMap.end() && "Retrieving non-existent component.");

        return ComponentArray[EntityToIndexMap[EntityIn]];
    }

    template<typename T>
    void ComponentArray<T>::EntityDestroyed(Entity EntityIn)
    {
        if (EntityToIndexMap.find(EntityIn) != EntityToIndexMap.end())
        {
            RemoveData(EntityIn);
        }
    }
}
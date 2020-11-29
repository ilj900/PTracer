#pragma once

#include "entity.h"

#include <cassert>

// A common interface to work with ComponentArrays
class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(FEntity EntityIn) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
    // Inserts the component's data into back of the component's array
    // Also store information: Entity->Index and Index->Entity
    void InsertData(FEntity Entity, T Component)
    {
        assert(EntityToIndexMap.find(Entity) == EntityToIndexMap.end() && "Component added to same entity more than once.");

        size_t NewIndex = Size;
        EntityToIndexMap[Entity] = NewIndex;
        IndexToEntityMap[NewIndex] = Entity;
        ComponentsData[NewIndex] = Component;
        ++Size;
    }

    // Removes component's data corresponding to entity
    // Also removes Entity from Entity->Index and Index->Entity map
    void RemoveData(FEntity Entity)
    {
        assert(EntityToIndexMap.find(Entity) != EntityToIndexMap.end() && "Removing non-existent component.");

        // Assign the last element of the array to the removed one
        size_t IndexOfRemovedEntity = EntityToIndexMap[Entity];
        size_t IndexOfLastElement = Size - 1;
        ComponentsData[IndexOfRemovedEntity] = ComponentsData[IndexOfLastElement];

        // Update map to point to moved spot
        FEntity EntityOfLastElement = IndexToEntityMap[IndexOfLastElement];
        EntityToIndexMap[EntityOfLastElement] = IndexOfRemovedEntity;
        IndexToEntityMap[IndexOfRemovedEntity] = EntityOfLastElement;

        EntityToIndexMap.erase(Entity);
        IndexToEntityMap.erase(IndexOfLastElement);
        --Size;
    }

    // Returns the component's data corresponding to that Entity
    T& GetData(FEntity Entity)
    {
        assert(EntityToIndexMap.find(Entity) != EntityToIndexMap.end() && "Retrieving non-existent component.");

        return ComponentsData[EntityToIndexMap[Entity]];
    }

    // Processes the deletion of entity.
    void EntityDestroyed(FEntity Entity) override
    {
        if (EntityToIndexMap.find(Entity) != EntityToIndexMap.end())
        {
            RemoveData(Entity);
        }
    }
private:
    static std::array<T, MAX_ENTITIES> ComponentsData;
    static std::unordered_map<FEntity, size_t> EntityToIndexMap;
    static std::unordered_map<size_t, FEntity> IndexToEntityMap;
    static size_t Size;
};

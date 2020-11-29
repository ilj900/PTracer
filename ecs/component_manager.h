#pragma once

#include "entity.h"
#include "component_array.h"

#include <memory>
#include <cassert>

class FComponentManager
{
public:
    // Get component's type and create a ComponentArray for it.
    // Map type's name to it's ID
    template<typename T>
    void RegisterComponent()
    {
        const char* TypeName = typeid(T).name();

        assert(ComponentTypes.find(TypeName) == ComponentTypes.end() && "Registering component type more than once.");
        ComponentTypes.insert({TypeName, NextComponentType});
        ComponentArrays.insert({TypeName, std::make_shared<ComponentArray<T>>()});
        ++NextComponentType;
    }

    // Return an ID of component that corresponds to that ComponentManager
    template<typename T>
    FComponentType GetComponentType()
    {
        const char* TypeName = typeid(T).name();
        assert(ComponentTypes.find(TypeName) != ComponentTypes.end() && "Component not registered before use.");
        return ComponentTypes[TypeName];
    }

    // Add component to entity and it's data
    // Component should be registered before it can be used
    template<typename T>
    void AddComponent(FEntity Entity, T Component)
    {
        const char* TypeName = typeid(T).name();
        assert(ComponentTypes.find(TypeName) != ComponentTypes.end() && "Component not registered before use.");
        std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[TypeName])->InsertData(Entity, Component);
    }

    // Removes component from entity and data accordingly
    // Component should be registered before it can be used
    template<typename T>
    void RemoveComponent(FEntity Entity)
    {
        const char* TypeName = typeid(T).name();
        assert(ComponentTypes.find(TypeName) != ComponentTypes.end() && "Component not registered before use.");
        return std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[TypeName])->RemoveData(Entity);
    }

    // Returns component's data of entity
    template<typename T>
    T& GetComponent(FEntity Entity)
    {
        const char* TypeName = typeid(T).name();
        assert(ComponentTypes.find(TypeName) != ComponentTypes.end() && "Component not registered before use.");
        return std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[TypeName])->GetData(Entity);
    }

    // Calls EntityDestroyed for every ComponentArray
    void EntityDestroyed(FEntity Entity)
    {
        for (auto const& Pair : ComponentArrays)
        {
            Pair.second->EntityDestroyed(Entity);
        }
    }

private:
    // Map from type string pointer to a component type
    std::unordered_map<const char*, FComponentType> ComponentTypes{};

    // Map from type string pointer to a component array
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> ComponentArrays{};

    // The component type to be assigned to the next registered component - starting at 0
    FComponentType NextComponentType{};
};
#pragma once

#include "component_manager.h"
#include "entity_manager.h"
#include "system_manager.h"

#include <memory>

class TheDirector
{
public:
    void Init()
    {
        ComponentManager = std::make_unique<FComponentManager>();
        EntityManager = std::make_unique<FEntityManager>();
        SystemManager = std::make_unique<FSystemManager>();
    }

    FEntity CreateEntity()
    {
        return EntityManager->CreateEntity();
    }

    void DestroyEntity(FEntity Entity)
    {
        EntityManager->DestroyEntity(Entity);
        ComponentManager->EntityDestroyed(Entity);
        SystemManager->EntityDestroyed(Entity);
    }

    template<typename T>
    void RegisterComponent()
    {
        ComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(FEntity Entity, T Component)
    {
        ComponentManager->AddComponent(Entity, Component);

        auto Signature = EntityManager->GetSignature(Entity);
        Signature.set(ComponentManager->GetComponentType<T>(), true);
        EntityManager->SetSignature(Entity, Signature);

        SystemManager->EntitySignatureChanged(Entity, Signature);
    }

    template<typename T>
    void RemoveComponent(FEntity Entity)
    {
        ComponentManager->RegisterComponent<T>(Entity);

        auto Signature = EntityManager->GetSignature(Entity);
        Signature.set(ComponentManager->GetComponentType<T>(), false);
        EntityManager->SetSignature(Entity, Signature);

        SystemManager->EntitySignatureChanged(Entity, Signature);
    }

    template<typename T>
    T& GetComponent(FEntity Entity)
    {
        return ComponentManager->GetComponent<T>(Entity);
    }

    template<typename T>
    FComponentType GetComponentType()
    {
        return ComponentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return SystemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(FSignature Signature)
    {
        SystemManager->SetSignature<T>(Signature);
    }


private:
    std::unique_ptr<FComponentManager> ComponentManager;
    std::unique_ptr<FEntityManager> EntityManager;
    std::unique_ptr<FSystemManager> SystemManager;

};
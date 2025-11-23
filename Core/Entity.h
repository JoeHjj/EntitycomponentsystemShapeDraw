#pragma once

#include "Component.h"
#include "TypedObjectCollection.h"

#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>
#include <QDebug>
#include <memory>
#include <typeindex>
#include <cassert>

struct Entity
{
    size_t id;
    CapabilityMask capabilityMask;
    TypedObjectCollection<Component> m_componentsCollection;

    template <typename T>
    void AddComponent(std::shared_ptr<T> component)
    {
        auto objects = m_componentsCollection.GetObjectsOfType<T>();// only one of type accepted
       // assert(objects.size() == 0 && "only one of same type is accepted");

        m_componentsCollection.Add<T>(component);
        Assign<Entity, T>(*this);
        qDebug()<<"Added component of type : "<<typeid(T).name() << " to entity";
    }

    template <typename T>
    void RemoveComponentOfType()
    {
        m_componentsCollection.Remove(typeid(T));
        UnAssign<Entity, T>(*this);
        qDebug()<<"Removed component of type : "<<typeid(T).name() << " from entity";

    }
    template <typename T> T* GetComponentOfType()
    {
        auto objects = m_componentsCollection.GetObjectsOfType<T>();// only one of type accepted
        if (objects.size() < 1)
        {
            return nullptr;
        }
        return dynamic_cast<T*>(objects.front().get());
    }

    template <typename T> std::list<std::shared_ptr<Component>> GetComponentsOfType()
    {
        return m_componentsCollection.GetObjectsOfType<T>();// only one of type accepted
    }

    std::list<std::shared_ptr<Component>> GetAllComponents()
    {
        return m_componentsCollection.GetAllObjects();
    }
};

#pragma once

#include <list>
#include <iostream>
#include <map>
#include <typeindex>
#include <algorithm>
#include <memory>
#include <cstring>

template<typename BASETYPE>
class TypedObjectCollection final
{
public:
    TypedObjectCollection() = default;

    ~TypedObjectCollection() = default;
    template <typename TYPE>
    void Add(std::shared_ptr<TYPE> obj)
    {
        m_object[typeid(TYPE)].emplace_back(obj);
    }


    template <typename TYPE>
    void Remove(std::shared_ptr<TYPE> value)
    {
        auto it = m_object.find(typeid(TYPE));
        if (it != m_object.end())
        {
            auto& iterators = it->second;

            auto objIter = std::find_if(iterators.begin(), iterators.end(), [&](const auto& iter)
                                        {
                                            return iter == value;
                                        });

            if (objIter != iterators.end())
            {
                iterators.erase(objIter);
            }
        }
    }
    void Remove(std::type_index type)
    {
        m_object.erase(type);
    }
    template <typename TYPE>
    std::list<std::shared_ptr<BASETYPE>> GetObjectsOfType()
    {
        auto it = m_object.find(typeid(TYPE));

        if (it != m_object.end())
        {
            return it->second;
        }
        return {};
    }

    std::list<std::shared_ptr<BASETYPE>> GetAllObjects() const {
        std::list<std::shared_ptr<BASETYPE>> result;
        for (const auto& entry : m_object) {
            if (!entry.second.empty()) {
                result.insert(result.end(), entry.second.begin(), entry.second.end());
            }
        }
        return result;
    }

private:
    std::map<std::type_index, std::list<std::shared_ptr<BASETYPE>>> m_object;
};

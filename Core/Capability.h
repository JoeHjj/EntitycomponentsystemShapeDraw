#pragma once

#include <bitset>
#include <typeindex>
#include <unordered_map>

using CapabilityMask = std::bitset<32>;

using CapabilitiesContainer = std::unordered_map<std::type_index, size_t>;

struct Capability
{
    Capability() = default;
    virtual ~Capability() = default;

    static inline CapabilitiesContainer capabilityIds;

    template<typename CapabilityType>
    static size_t getId()
    {
        auto it = capabilityIds.find(std::type_index(typeid(CapabilityType)));
        if (it != capabilityIds.end()) {
            return it->second;
        }
        size_t capabilityId = capabilityIds.size() + 1;
        capabilityIds.emplace(std::type_index(typeid(CapabilityType)), capabilityId);
        return capabilityId;
    }
};

template<typename ObjectType, typename CapabilityType>
inline void Assign(ObjectType& object)
{
    object.capabilityMask |= (static_cast<CapabilityMask>(1) << (Capability::getId<CapabilityType>() - 1));
}

template<typename ObjectType, typename CapabilityType>
inline void UnAssign(ObjectType& object)
{
    object.capabilityMask &= ~(static_cast<CapabilityMask>(1) << (Capability::getId<CapabilityType>() - 1));
}

template<typename ObjectType, typename CapabilityType>
inline bool HaveCapability(const ObjectType& object)
{
    return object.capabilityMask[Capability::getId<CapabilityType>() - 1];
}

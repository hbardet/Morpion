#pragma once

#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Health/Health.hh"
#include "../../Component/Position/Position.hpp"

namespace ECS {
    namespace Systems {

        class GetDeadEntities : public System{
        public:
            
            std::vector<std::size_t> getDeadEntities(
                ECS::ComponentManager::SparseArray<ECS::Components::Health> healths,
                ECS::ComponentManager::SparseArray<ECS::Components::Position> positions,
                const std::vector<std::size_t> & entities);
        };
    }
}

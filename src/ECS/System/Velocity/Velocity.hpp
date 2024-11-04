/*
** EPITECH PROJECT, 2024
** SystemVelocity.hh
** File description:
** SystemVelocity class
*/
#pragma once

#include <cstddef>
#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Velocity/Velocity.hh"
#include <map>

namespace ECS {
    namespace Systems {

        /**
        * @brief System that handles updating the position of entities based on their velocity.
        *
        * The SystemVelocity class is responsible for updating the position of entities in the
        * ECS (Entity-Component-System) architecture.
        */
        class SystemVelocity : public System {
        public:
            /**
            * @brief Default constructor for SystemVelocity.
            *
            * Initializes a new instance of the SystemVelocity class.
            */
            SystemVelocity() = default;

            /**
            * @brief Default destructor for SystemVelocity.
            */
            ~SystemVelocity() = default;

            /**
            * @brief Updates the positions of entities based on their velocity.
            *
            * For each entity in the provided list, this function fetches its Position and Velocity
            * components, then updates the entity's position by adding the velocity values.
            *
            * @param positions SparseArray of Position components where the positions of entities are stored.
            * @param velocities SparseArray of Velocity components where the velocities of entities are stored.
            * @param entities Vector of entity indices to update.
            * @return void.
            */
            void update(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        ECS::ComponentManager::SparseArray<ECS::Components::Velocity> &velocities,
                        std::map<int, std::size_t> &players,
                        std::vector<std::size_t> &entities);
        };
    }
}

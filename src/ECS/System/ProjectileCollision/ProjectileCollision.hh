/*
** EPITECH PROJECT, 2024
** R-Type - System : Hitbox
** File description:
** System hitbox class
*/

#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Hitbox/Hitbox.hh"
#include "../../Component/Projectile/Projectile.hh"
#include "../../Component/AI/AI.hh"

namespace ECS {
    namespace Systems {

        /**
        * @brief System for handling projectile collisions with other entities.
        *
        * The ProjectileCollision system checks for collisions between projectiles and other entities.
        * It uses the position and hitbox components to determine if a projectile has collided with
        * another entity or is out of bounds.
        */
        class ProjectileCollision : public System {
        public:

            /**
            * @brief Default constructor for ProjectileCollision.
            */
            ProjectileCollision() = default;

            /**
            * @brief Default destructor for ProjectileCollision.
            */
            ~ProjectileCollision() = default;

            /**
            * @brief Checks for collisions between projectiles and entities.
            *
            * This method checks if a projectile has collided with another entity or has gone out of bounds.
            * If a collision is detected, the method returns the projectile's ID. It skips self-collision checks
            * (for example the projectile does not collide with its own entity).
            *
            * @param positions SparseArray containing the Position components of entities.
            * @param hitboxes SparseArray containing the Hitbox components of entities.
            * @param projectileEntities Vector of projectile entity IDs to check for collisions.
            * @param entities Vector of other entity IDs to check against projectiles.
            * @return The ID of the projectile that has collided, or a large number (100000) if no collision occurs.
            */
            std::vector<std::size_t> projectileIsHit(
                ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
                ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> & hitboxes,
                ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
                std::vector<std::size_t> & projectileEntities, std::vector<std::size_t> & entities,
                std::vector<std::size_t> & AIEntities);
        };
    }
}

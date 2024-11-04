/*
** EPITECH PROJECT, 2024
** R-Type - ECS : ProjectileCollision
** Fie description:
** Handles collision between projectiles and other entities.
*/

#include "ProjectileCollision.hh"
#include "../../Utils/Utils.hh"

#include <cassert>

std::vector<std::size_t> ECS::Systems::ProjectileCollision::projectileIsHit(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::AI> &AIs,
    std::vector<std::size_t> &projectileEntities, std::vector<std::size_t> &entities,
    std::vector<std::size_t> &AIEntities)
{
    bool selfCollision = false;
    std::vector<std::size_t> entityCollided;
    bool isAIShot = false;
    bool isAIEntity = false;

    for (std::size_t j = 0; j < projectileEntities.size(); ++j) {
        std::size_t projectile = projectileEntities[j];
//        std::cout << "projectile: " << projectile;
        assert(positions[projectile].has_value());
        assert(hitboxes[projectile].has_value());
        auto &projectilePos = positions[projectile].value();
        auto &projectileHitbox = hitboxes[projectile].value();
        isAIShot = false;

        for (int i = 0; i < AIEntities.size(); i++)
            if (AIEntities[i] == projectile)
                isAIShot = true;

//        std::cout << " " << isAIShot << std::endl;
        if (projectilePos.getX() >= 11.0 || projectilePos.getX() <= -11.0) {
            entityCollided.push_back(projectile);
            continue;
        }

        for (std::size_t i = 0; i < entities.size(); i++) {
            for (std::size_t temp = 0; temp < projectileEntities.size(); temp++) {
                if (entities[i] == projectileEntities[temp]) {
                    selfCollision = true;
                    break;
                } else {
                    selfCollision = false;
                }
            }
            if (selfCollision == true) {
                continue;
            }
            std::size_t entity = entities[i];
//            std::cout << "entity: " << entity;
            assert(positions[entity].has_value());
            assert(hitboxes[entity].has_value());
            auto &entityPos = positions[entity].value();
            auto &entityHitbox = hitboxes[entity].value();
//            std::cout << " --> ";
            isAIEntity = false;

            for (int k = 0; k < AIEntities.size(); k++)
                if (AIEntities[k] == entity)
                    isAIEntity = true;

//            std::cout << isAIEntity << std::endl;
            if ((isAIShot && isAIEntity) || (!isAIShot && !isAIEntity)) {
                continue;
            }
            if (ECS::Utils::checkCollision(entityPos, entityHitbox, projectilePos, projectileHitbox)) {
//                std::cerr << "collision entity: " << entity;
//                std::cerr << "collision projectile: " << projectile << std::endl;
                entityCollided.push_back(entity);
                entityCollided.push_back(projectile);
            }
        }
    }
    return entityCollided;
}

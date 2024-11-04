/*
** EPITECH PROJECT, 2024
** hitbox.hh
** File description:
** System hitbox class
*/

#include "Collision.hh"
#include "../../Utils/Utils.hh"

void ECS::Systems::Collision::playerIsHit(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::Health> &healths,
    std::size_t player, std::vector<std::size_t> &entities)
{
    if (healths[player]->getInvincibility() > 0)
        healths[player]->modifyInvincibilityBy(-1);
    auto &posPlayer = positions[player].value();
    auto &hitboxPlayer = hitboxes[player].value();

    for (std::size_t i = 0; i < entities.size(); ++i) {
        std::size_t entity = entities[i];
        auto &posEntity = positions[entity].value();
        auto &hitboxEntity = hitboxes[entity].value();

        if (ECS::Utils::checkCollision(posEntity, hitboxEntity, posPlayer, hitboxPlayer)) {
            if (healths[player]->getInvincibility() == 0) {
                std::cout << "OOF!!" << std::endl;
                healths[player]->modifyHealthBy(-1);
                healths[player]->setInvincibility(200);
            } 
        }
    }
}

std::vector<std::size_t> ECS::Systems::Collision::AIHitPod(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::Health> &healths,
    ECS::ComponentManager::SparseArray<ECS::Components::Pod> &pods,
    const std::vector<std::size_t> &podsEntity, const std::vector<std::size_t> &AIs)
{
    std::vector<std::size_t> AIHitByPod;

    for (std::size_t j = 0; j < podsEntity.size(); j++) {
        std::size_t pod = podsEntity[j];

        if (pods[pod]->getPlayer() == 10000)
            continue;

        auto &posPod = positions[pod].value();
        auto &hitboxPod = hitboxes[pod].value();

        for (std::size_t i = 0; i < AIs.size(); ++i) {
            std::size_t AI = AIs[i];
            auto &posAI = positions[AI].value();
            auto &hitboxAI = hitboxes[AI].value();

            if (ECS::Utils::checkCollision(posAI, hitboxAI, posPod, hitboxPod)) {
                if (healths[AI]->getInvincibility() == 0) {
                    std::cout << "pod is working hassoul!!" << std::endl;
                    AIHitByPod.push_back(AI);
                }
            }
        }
    }
    return AIHitByPod;
}

std::vector<std::size_t> ECS::Systems::Collision::PlayerPickedUpPod(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> & hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::Pod> & pods,
    std::vector<std::size_t> & podsEntity, std::size_t player)
{
    std::vector<std::size_t> playerPickedUpPod;

    for (std::size_t j = 0; j < podsEntity.size(); j++) {
        std::size_t pod = podsEntity[j];

        if (pods[pod]->getPlayer() < 10000)
            continue;

        auto &posPod = positions[pod].value();
        auto &hitboxPod = hitboxes[pod].value();
        auto &posPlayer = positions[player].value();
        auto &hitboxPlayer = hitboxes[player].value();

        if (ECS::Utils::checkCollision(posPlayer, hitboxPlayer, posPod, hitboxPod)) {
            playerPickedUpPod.push_back(pod);
        }
    }
    return playerPickedUpPod;
}

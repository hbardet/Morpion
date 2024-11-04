#include "UpdateVelocityAI.hh"
#include <cstdlib>
#include <ctime>

void ECS::Systems::UpdateVelocityAI::update (
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
    std::vector<std::size_t> entities,
    const std::map<int, std::size_t> & serverToLocalPlayersId) const
{
    std::size_t boss2CoreId = 0;

    for (std::size_t i = 0; i < entities.size(); i++) {
        std::size_t aiId = entities[i];
        enemiesTypeEnum_t aiType = AIs[aiId]->getEnemyType();

        if (aiType == MINIKIT) {
            velocities[aiId]->setX(-0.025f);
        }
        if (aiType == PATAPATA) {
            float amplitude = 0.05f;
            float frequency = 2.0f;
            velocities[aiId]->setX(-0.05f);
            velocities[aiId]->setY(
                amplitude * std::sin(frequency * positions[aiId]->getX()));
        }
        if (aiType == BUG) {
            float amplitude = 0.025f;
            float frequency = 1.0f;
            float offset = 0.01f;
            if (positions[aiId]->getOriginalY() > 0)
                offset *= -1; 
            velocities[aiId]->setX(-0.05f);
            velocities[aiId]->setY(
                amplitude * std::sin(frequency * positions[aiId]->getX()) + offset);
        }
        if (aiType == BINK) {
            velocities[aiId]->setY(0.05);
            if (positions[aiId]->getY() > 4.5)
                velocities[aiId]->setY(0);
            if (AIs[aiId]->isFiring()) {
                velocities[aiId]->setX(-0.01);
                continue;
            }

            std::vector<std::pair<float, float>> playersPos;
            for (const auto& player : serverToLocalPlayersId)
                playersPos.push_back(positions[player.second]->getPosPair());
            std::size_t targetPlayer = ecsUtils::getClosestPlayer(
                positions[aiId]->getPosPair(), playersPos);
            for (const auto& player : serverToLocalPlayersId)
                if (positions[player.second]->getPosPair() == playersPos[targetPlayer])
                    targetPlayer = player.second;

            if (positions[aiId]->getX() > positions[targetPlayer]->getX())
                velocities[aiId]->setX(-0.033);
            else
                velocities[aiId]->setX(0.033);
        }
        if (aiType == BLASTER) {
            velocities[aiId]->setX(-0.01);
        }
        if (aiType == HOMINGSHOT) {
            std::vector<std::pair<float, float>> playersPos;
            for (const auto& player : serverToLocalPlayersId)
                playersPos.push_back(positions[player.second]->getPosPair());
            std::size_t targetPlayer = ecsUtils::getClosestPlayer(
                positions[aiId]->getPosPair(), playersPos);
            for (const auto& player : serverToLocalPlayersId)
                if (positions[player.second]->getPosPair() == playersPos[targetPlayer])
                    targetPlayer = player.second;
            float playerX = positions[targetPlayer]->getX();
            float playerY = positions[targetPlayer]->getY();
            float aiOrigX = positions[aiId]->getOriginalX();
            float aiX = positions[aiId]->getX();
            float aiY = positions[aiId]->getY();

            if (aiX > playerX + 1 && aiOrigX > playerX) {
                velocities[aiId]->setX(-0.1);
                velocities[aiId]->setY((playerY - aiY) / 25);
            }
        }
        if (aiType >= BOSS1_Tail0 && aiType <= BOSS1_Tail19) {
            float p1x = AIs[aiId]->getP1().first;
            float p1y = AIs[aiId]->getP1().second;
            float p2x = AIs[aiId]->getP2().first;
            float p2y = AIs[aiId]->getP2().second;
            float distanceBetweenXPoints = p2x - p1x;
            float deltaBetweenThePoints = distanceBetweenXPoints / 200;
            float curX = positions[aiId]->getX();
            float nextY = 0;

            if (curX >= p2x || (velocities[aiId]->getX() < 0 && curX > p1x))
                deltaBetweenThePoints *= -1;
            velocities[aiId]->setX(deltaBetweenThePoints);
            nextY = ((p1y - p2y) / 2) * std::sin(M_PI / (p1x - p2x)) * (curX - ((p1x + p2x) / 2)) + ((p1y + p2y) / 2);
            velocities[aiId]->setY(nextY - positions[aiId]->getY());
        }
        if (aiType >= BOSS2_Core && aiType <= BOSS2_Ball38) {
            if (aiType == BOSS2_Core && !AIs[aiId]->isFiring()) {
                std::srand(std::time(nullptr));
                int randX = std::rand() % 16 - 8;
                int randY = std::rand() % 8 - 4;
                AIs[aiId]->setFiring(true);
                AIs[aiId]->setCooldown(200);
                velocities[aiId]->setX((randX - positions[aiId]->getX()) / 200);
                velocities[aiId]->setY((randY - positions[aiId]->getY()) / 200);
                boss2CoreId = aiId;
                continue;
            }
            if (aiType == BOSS2_Core && AIs[aiId]->isFiring()) {
                AIs[aiId]->setCooldown(AIs[aiId]->getCooldown() - 1);
                boss2CoreId = aiId;
                continue;
            }
            if (!AIs[aiId]->isFiring() && AIs[aiId]->getCooldown() > 0) {
                velocities[aiId]->setX(velocities[boss2CoreId]->getX());
                velocities[aiId]->setY(velocities[boss2CoreId]->getY());
                AIs[aiId]->setCooldown(AIs[aiId]->getCooldown() - 1);
            }

            if (!AIs[aiId]->isFiring() && AIs[aiId]->getCooldown() == 0) {
                AIs[aiId]->setFiring(true);
                AIs[aiId]->setCooldown(200);
            }

            if (AIs[aiId]->isFiring() && AIs[aiId]->getCooldown() == 200) {
                std::vector<std::pair<float, float>> playersPos;
                for (const auto& player : serverToLocalPlayersId)
                    playersPos.push_back(positions[player.second]->getPosPair());
                std::size_t targetPlayer = ecsUtils::getClosestPlayer(
            positions[aiId]->getPosPair(), playersPos);
                for (const auto& player : serverToLocalPlayersId)
                    if (positions[player.second]->getPosPair() == playersPos[targetPlayer])
                        targetPlayer = player.second;
                float tempVelX = positions[targetPlayer]->getX() - positions[aiId]->getX();
                float tempVelY = positions[targetPlayer]->getY() - positions[aiId]->getY();
                velocities[aiId]->setX(tempVelX / 50);
                velocities[aiId]->setY(tempVelY / 50);
                AIs[aiId]->setCooldown(AIs[aiId]->getCooldown() - 1);
            }

            if (AIs[aiId]->isFiring() && AIs[aiId]->getCooldown() > 0)
                AIs[aiId]->setCooldown(AIs[aiId]->getCooldown() - 1);
            
            if (AIs[aiId]->isFiring() && AIs[aiId]->getCooldown() == 0) {
                AIs[aiId]->setFiring(false);
                AIs[aiId]->setCooldown(2500);
            }
        }
    }
}


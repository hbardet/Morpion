#include "AIFiringProjectile.hh"

std::vector<std::size_t> ECS::Systems::AIFiringProjectile::aiFiringBydoShots(
    ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    std::vector<std::size_t> & entities)
{
    std::vector<std::size_t> firingEntities;

    for (std::size_t i = 0; i < entities.size(); i++) {
        if (AIs[entities[i]]->isFiring() && AIs[entities[i]]->getCooldown() < 100)
            AIs[entities[i]]->setFiring(false);
        if (AIs[entities[i]]->getCooldown() > 0)
            AIs[entities[i]]->setCooldown(AIs[entities[i]]->getCooldown() - 1);
        if ((AIs[entities[i]]->getEnemyType() == PATAPATA || AIs[entities[i]]->getEnemyType() == BUG) &&
            positions[entities[i]]->getX() < 2.0 && AIs[entities[i]]->getCooldown() == 0) {
            AIs[entities[i]]->setFiring(true);
            AIs[entities[i]]->setCooldown(200);
            firingEntities.push_back(entities[i]);
        }
        if (AIs[entities[i]]->getEnemyType() == BINK && AIs[entities[i]]->getCooldown() == 0) {
            AIs[entities[i]]->setFiring(true);
            AIs[entities[i]]->setCooldown(150);
        }
        if (AIs[entities[i]]->getEnemyType() == BINK && AIs[entities[i]]->getCooldown() == 125)
            firingEntities.push_back(entities[i]);
    }
    return firingEntities;
}

std::vector<std::size_t> ECS::Systems::AIFiringProjectile::aiFiringHomingShots(
    ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
    std::vector<std::size_t> & entities)
{
    std::vector<std::size_t> firingEntities;

    for (std::size_t i = 0; i < entities.size(); i++) {
        if (AIs[entities[i]]->getEnemyType() == BLASTER && AIs[entities[i]]->getCooldown() == 0) {
            firingEntities.push_back(entities[i]);
            AIs[entities[i]]->setCooldown(250);
        }
    }
    return firingEntities;
}

std::vector<std::size_t> ECS::Systems::AIFiringProjectile::podFiringShots(
    ECS::ComponentManager::SparseArray<ECS::Components::Pod> & pods,
    std::vector<std::size_t> & entities)
{
    std::vector<std::size_t> firingEntities;

    for (std::size_t i = 0; i < entities.size(); i++) {
        if (pods[entities[i]]->getCooldown() > 0 && pods[entities[i]]->getLevel() > 0)
            pods[entities[i]]->setCooldown(pods[entities[i]]->getCooldown() -1);
        if (pods[entities[i]]->getCooldown() > 0 && pods[entities[i]]->getLevel() > 1)
            pods[entities[i]]->setCooldown(pods[entities[i]]->getCooldown() -1);

        if (pods[entities[i]]->getCooldown() == 0 && pods[entities[i]]->getLevel() > 0) {
            std::cout << "pods[" << i << "] cd: " << pods[entities[i]]->getCooldown() << " level: " << pods[entities[i]]->getLevel() << std::endl;
            pods[entities[i]]->setCooldown(50);
            firingEntities.push_back(entities[i]);
        }
    }
    for (int i = 0; i < firingEntities.size(); i++)
        std::cout << "firingEntities: " << firingEntities[i]<< std::endl;
    return firingEntities;
}

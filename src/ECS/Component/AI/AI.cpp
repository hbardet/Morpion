/*
** EPITECH PROJECT, 2024
** R-Type - Components : AI
** File description:
** AI Component
*/
#include "AI.hh"

ECS::Components::AI::AI(enemiesTypeEnum_t enemyType):
    _enemyType(enemyType), _p1(std::make_pair(0, 0)), _p2(std::make_pair(0, 0)),
    _isFiring(false), _cooldown(0)
{}

ECS::Components::AI::AI(enemiesTypeEnum_t enemyType, std::pair<float, float> p1,
                        std::pair<float, float> p2):
    _enemyType(enemyType), _p1(p1), _p2(p2), _isFiring(false), _cooldown(0)
{}

enemiesTypeEnum_t ECS::Components::AI::getEnemyType() const
{
    return _enemyType;
}

void ECS::Components::AI::setEnemyType(enemiesTypeEnum_t enemyType)
{
    _enemyType = enemyType;
}

void ECS::Components::AI::setFiring(bool isFiring)
{
    _isFiring = isFiring;
}

void ECS::Components::AI::flipFiring()
{
    _isFiring = !_isFiring;
}

bool ECS::Components::AI::isFiring() const
{
    return _isFiring;
}

void ECS::Components::AI::setCooldown(std::size_t cooldown)
{
    _cooldown = cooldown;
}

std::size_t ECS::Components::AI::getCooldown() const
{
    return _cooldown;
}

std::pair<float, float> ECS::Components::AI::getP1() const
{
    return _p1;
}

std::pair<float, float> ECS::Components::AI::getP2() const
{
    return _p2;
}

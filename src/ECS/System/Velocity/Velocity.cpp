/*
** EPITECH PROJECT, 2024
** SystemVelocity.cpp
** File description:
** SystemVelocity cpp
*/
#include "Velocity.hpp"

void ECS::Systems::SystemVelocity::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> &velocities,
    std::map<int, std::size_t> &players,
    std::vector<std::size_t> &entities)
{
    for (auto &entity : entities) {
        auto &position = positions[entity].value();
        auto &velocity = velocities[entity].value();
        position.setX(position.getX() + velocity.getX());
        position.setY(position.getY() + velocity.getY());
    }
    for (auto &player : players) {
        auto &velocity = velocities[player.second].value();
        velocity.setX(0.);
        velocity.setY(0.);
    }
}

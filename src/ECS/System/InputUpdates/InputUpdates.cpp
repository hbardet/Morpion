/*
** EPITECH PROJECT, 2024
** R-Type - Systems : InputUpdates
** File description:
** Updates information based on the inputs
*/
#include "InputUpdates.hh"
#include "../../Component/Input/enumInput.hpp"
#include <cstddef>

std::size_t ECS::Systems::InputUpdates::updateInputs(
    const std::vector<std::size_t> & inputs,
    ECS::ComponentManager::SparseArray<ECS::Components::Input> & inputComponents,
    std::vector<std::size_t> entities)
{
    for (std::size_t i = 0; i < entities.size(); i++) {
        inputComponents[entities[i]]->setInputs(inputs);
    }
    return 10001;
}

void ECS::Systems::InputUpdates::updateInputedVelocity(
    ECS::ComponentManager::SparseArray<ECS::Components::Input> & inputs,
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
    std::vector<std::size_t> entities)
{
    float velX = 0;
    float velY = 0;

    float veloValue = 0.1f;
    for (std::size_t i = 0; i < entities.size(); i++) {
        if (inputs[entities[i]]->contains(ECS::Components::RIGHT))
            velX += veloValue;
        if (inputs[entities[i]]->contains(ECS::Components::UP))
            velY -= veloValue;
        if (inputs[entities[i]]->contains(ECS::Components::LEFT))
            velX -= veloValue;
        if (inputs[entities[i]]->contains(ECS::Components::DOWN))
            velY += veloValue;
        velocities[entities[i]]->setVelPair(std::make_pair(velX, velY));
    }
    inputs.clear();
}

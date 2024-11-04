/*
** EPITECH PROJECT, 2024
** SystemLight.cpp
** File description:
** SystemLight cpp
*/
#include "Light.hh"

void ECS::Systems::SystemLight::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Light> &lights,
    std::vector<std::size_t> &entities,
    ECS::RessourcePool &ressourcePool
)
{
    for (auto &entity : entities) {
        if (!(lights[entity].has_value() || positions[entity].has_value())) {
            continue;
        }
        auto &position = positions[entity].value();
        auto &light = lights[entity].value();
        raylib::Vector3 pos(position.getX() , 0, position.getY());
        const std::string path = light.getPath();
        light.setPosition(raylib::Vector3(position.getX(), position.getY(), position.getZ()));
        light.update(ressourcePool.getShader(path));
    }
}

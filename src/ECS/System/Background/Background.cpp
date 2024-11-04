/*
** EPITECH PROJECT, 2024
** SystemBackground.cpp
** File description:
** SystemBackground cpp
*/
#include "Background.hh"

void ECS::Systems::SystemBackground::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Background> &backgrounds,
    std::vector<std::size_t> &entities)
{
    for (auto &entity : entities) {
        if (!(backgrounds[entity].has_value() || positions[entity].has_value())) {
            continue;
        }
        auto &position = positions[entity].value();
        auto &background = backgrounds[entity].value();
        raylib::Vector3 pos(position.getX() , position.getZ(), position.getY());

        if (pos.x < ((background.getWidth()) * -1))
            position.setX(background.getWidth() * 2);
    }
}

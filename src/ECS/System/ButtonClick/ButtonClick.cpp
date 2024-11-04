/*
** EPITECH PROJECT, 2024
** ButtonClick.cpp
** File description:
** ButtonClick system class
*/

#include "ButtonClick.hh"


void ECS::Systems::ButtonClickSystem::update(ECS::ComponentManager::SparseArray<ECS::Components::Button> &buttons,
            const std::vector<std::size_t> &entities) {
    Vector2 mousePosition = GetMousePosition();
    for (auto entity : entities) {
        if (buttons[entity].has_value()) {
            auto &button = buttons[entity].value();
            if (CheckCollisionPointRec(mousePosition, button.getBounds()) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                button.onClick();
            }
        }
    }
}

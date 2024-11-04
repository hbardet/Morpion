/*
** EPITECH PROJECT, 2024
** RenderText class.hh
** File description:
** RenderButton class
*/

#include "RenderButton.hh"

void ECS::Systems::RenderButtonSystem::update(ECS::ComponentManager::SparseArray<ECS::Components::Button> &buttons,
            ECS::ComponentManager::SparseArray<ECS::Components::Text> &texts,
            ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
            const std::vector<std::size_t> &entities) {
    for (auto entity : entities) {
        if (buttons[entity].has_value() && texts[entity].has_value() && positions[entity].has_value()) {
            auto &button = buttons[entity].value();
            auto &text = texts[entity].value();
            auto &pos = positions[entity].value();

            if (button.isSelected()) {
                text.setColor(YELLOW);
            } else {
                text.setColor(RAYWHITE);
            }

            raylib::DrawText(text.getText(), (int) pos.getX(), (int) pos.getY(),
                    text.getFontSize(), text.getColor());
        }
    }
}

/*
** EPITECH PROJECT, 2024
** R-Type - Systems : TextFieldRender
** File description:
** System to handle TextField render
*/

#include "RenderTextfield.hh"

void ECS::Systems::RenderTextFieldSystem::update(
    ECS::ComponentManager::SparseArray<ECS::Components::TextField> &textFields,
    ECS::ComponentManager::SparseArray<ECS::Components::Text> &texts,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    const std::vector<std::size_t> &entities
) {
    for (auto entity : entities) {
        if (textFields[entity].has_value() && texts[entity].has_value() && positions[entity].has_value()) {
            auto &textField = textFields[entity].value();
            auto &text = texts[entity].value();
            auto &pos = positions[entity].value();

            Color borderColor = textField.isActive() ? BLUE : DARKGRAY;

            DrawRectangleLinesEx(textField.getBounds(), 2, borderColor);
        }
    }
}

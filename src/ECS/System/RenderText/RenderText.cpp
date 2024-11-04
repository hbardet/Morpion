/*
** EPITECH PROJECT, 2024
** RenderText class.hh
** File description:
** RenderText class
*/

#include "RenderText.hh"

void ECS::Systems::RenderTextSystem::update(ECS::ComponentManager::SparseArray<ECS::Components::Text> &texts,
                ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                const std::vector<std::size_t> &entities)
{
    for (auto entity : entities) {
        if (texts[entity].has_value() && positions[entity].has_value()) {
            const auto &text = texts[entity].value();
            const auto &pos = positions[entity].value();

            raylib::DrawText(text.getText(), (int) pos.getX(), (int) pos.getY(),
                    text.getFontSize(), text.getColor());
        }
    }
}

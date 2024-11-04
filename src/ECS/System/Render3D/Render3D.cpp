/*
** EPITECH PROJECT, 2024
** SystemRender3D.cpp
** File description:
** SystemRender3D cpp
*/
#include "Render3D.hh"
#include <string>

void ECS::Systems::SystemRender3D::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Rotate> &rotates,
    ECS::ComponentManager::SparseArray<ECS::Components::Scale> &scales,
    ECS::ComponentManager::SparseArray<ECS::Components::Render3D> &renders,
    std::vector<std::size_t> &entities,
    ECS::RessourcePool &ressourcePool,
    raylib::Camera3D &camera)
{
    raylib::Vector3 rotation = {0.0f, 0.0f, 0.0f};
    raylib::Vector3 scale = {1.0f, 1.0f, 1.0f};
    bool drawHitBox = false;

    camera.BeginMode();
    for (auto &entity : entities) {
        rotation = raylib::Vector3(0.0f, 0.0f, 0.0f);
        scale = raylib::Vector3(1.0f, 1.0f, 1.0f);
        if (!(renders[entity].has_value() || positions[entity].has_value())) {
            continue;
        }
        if (rotates[entity].has_value()) {
            auto &rotate = rotates[entity].value();
            rotation = raylib::Vector3(rotate.getRoll(), rotate.getPitch(), rotate.getYaw());
        }
        if (scales[entity].has_value()) {
            auto &scaleComp = scales[entity].value();
            scale = raylib::Vector3(scaleComp.getScale(), scaleComp.getScale(), scaleComp.getScale());
        }
        auto &position = positions[entity].value();
        auto &render = renders[entity].value();
        raylib::Vector3 pos(position.getX() , position.getZ(), position.getY());
        const std::string path = render.getPath();

        if (drawHitBox) {
            std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(ressourcePool.getModel(path));
            DrawCubeWires(pos, TmpHitbox.first, 1.0f, TmpHitbox.second, RED);
        }
        render.render(ressourcePool.getModel(path), pos, rotation, scale);
    }
    camera.EndMode();
}

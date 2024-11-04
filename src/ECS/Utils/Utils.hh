/*
** EPITECH PROJECT, 2024
** Utils.hh
** File description:
** Utils class
*/

#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
#include "raylib-cpp.hpp"
#include "../Component/Position/Position.hpp"
#include "../Component/Hitbox/Hitbox.hh"

namespace ECS {

    class Utils {
    public:
        enum FileType {
            Unknown = 0,
            Texture,
            Model,
            Audio,
            Font,
            Shader,
            Data
        };
        static bool checkCollision(
            const ECS::Components::Position &posA,
            const ECS::Components::Hitbox &hitboxA,
            const ECS::Components::Position &posB,
            const ECS::Components::Hitbox &hitboxB);

        static FileType getRaylibFileType(const std::string& path);
        static std::pair<float, float> getModelSize(const raylib::Model &model);
    };
}

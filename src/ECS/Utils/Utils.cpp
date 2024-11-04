/*
** EPITECH PROJECT, 2024
** Utils.hh
** File description:
** Utils class
*/

#include "Utils.hh"

bool ECS::Utils::checkCollision(
    const ECS::Components::Position &posA, const ECS::Components::Hitbox &hitboxA,
    const ECS::Components::Position &posB, const ECS::Components::Hitbox &hitboxB)
{
    return (posA.getX() < posB.getX() + hitboxB.getWidth() &&
            posA.getX() + hitboxA.getWidth() > posB.getX() &&
            posA.getY() < posB.getY() + hitboxB.getHeight() &&
            posA.getY() + hitboxA.getHeight() > posB.getY());
}

ECS::Utils::FileType ECS::Utils::getRaylibFileType(const std::string& path) {
    std::string extension = std::filesystem::path(path).extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    if (extension == ".png" || extension == ".bmp" || extension == ".tga" || extension == ".jpg" || extension == ".gif") {
        return ECS::Utils::FileType::Texture;
    }
    else if (extension == ".obj" || extension == ".gltf" || extension == ".glb" || extension == ".iqm") {
        return ECS::Utils::FileType::Model;
    }
    else if (extension == ".wav" || extension == ".ogg" || extension == ".mp3") {
        return ECS::Utils::FileType::Audio;
    }
    else if (extension == ".ttf" || extension == ".otf") {
        return ECS::Utils::FileType::Font;
    }
    else if (extension == ".vs" || extension == ".fs") {
        return ECS::Utils::FileType::Shader;
    }
    else if (extension == ".txt" || extension == ".json") {
        return ECS::Utils::FileType::Data;
    }
    else {
        return ECS::Utils::FileType::Unknown;
    }
}

std::pair<float, float> ECS::Utils::getModelSize(const raylib::Model &model)
{
    raylib::BoundingBox box = model.GetBoundingBox();
    float width = box.max.x - box.min.x;
    float height = box.max.z - box.min.z;

    return std::make_pair(width, height);
}

/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Ressource class is the class to load one time each model and
** re use them after withtout reloading them.
*/

#include "RessourcePool.hh"

ECS::RessourcePool::RessourcePool()
{}

void ECS::RessourcePool::UnloadAll()
{
    for (auto &model : _models) {
        if (model.second.meshes != nullptr) {
            model.second.Unload();
            std::cout << "Unloaded model: " << model.first << std::endl;
        } else {
            std::cout << "Model: " << model.first << " already unloaded" << std::endl;
        }
    }
    for (auto &texture : _textures) {
        if (texture.second.id != 0) {
            texture.second.Unload();
            std::cout << "Unloaded texture: " << texture.first << std::endl;
        } else {
            std::cout << "Texture: " << texture.first << " already unloaded" << std::endl;
        }
    }
}

raylib::Model& ECS::RessourcePool::getModel(const std::string &modelPath)
{
    return _models.at(modelPath);
}

raylib::Texture& ECS::RessourcePool::getTexture(const std::string &texturePath)
{
    return _textures.at(texturePath);
}

void ECS::RessourcePool::addTexture(const std::string &TexturePath)
{
    std::string pathRessources = "./resources/" + TexturePath + "/" + TexturePath + ".png";
    raylib::Texture defaultTexture(pathRessources);

    _textures.emplace(TexturePath, std::move(defaultTexture));
}

void ECS::RessourcePool::addModel(const std::string &modelPath)
{
    std::string pathRessources = "./resources/" + modelPath + "/" + modelPath + ".obj";
    std::string pngTexturePath = pathRessources.substr(0, pathRessources.find_last_of('.')) + ".png";
    raylib::Model defaultModel(pathRessources);

    if (std::filesystem::exists(pngTexturePath)) {
        raylib::Texture texture(pngTexturePath.c_str());
        defaultModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
        _texturesModels.emplace(pngTexturePath, std::move(texture));
    }

    _models.emplace(modelPath, std::move(defaultModel));
}

void ECS::RessourcePool::queueModelLoad(const std::string &modelPath)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _pendingLoads.push(modelPath);
}

void ECS::RessourcePool::requestLoadTexture(const std::string &texturePath)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _pendingTextureLoads.push(texturePath);
}

void ECS::RessourcePool::processLoadQueue()
{
    std::lock_guard<std::mutex> lock(_mutex);

    while (!_pendingLoads.empty()) {
        std::string modelPath = _pendingLoads.front();
        _pendingLoads.pop();
        addModel(modelPath);
    }
    while (!_pendingTextureLoads.empty()) {
            std::string texturePath = _pendingTextureLoads.front();
            _pendingTextureLoads.pop();
            addTexture(texturePath);
        }
}

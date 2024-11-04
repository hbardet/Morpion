/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Ressource class is the class to load one time each model and
** re use them after withtout reloading them.
*/
#pragma once
#include <map>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif
#include <array>
#include <queue>
#include <mutex>

namespace ECS {
    class RessourcePool {
    public:
        RessourcePool();
        ~RessourcePool() = default;

        raylib::Model &getModel(const std::string &modelPath);
        raylib::Texture &getTexture(const std::string &texturePath);

        void queueModelLoad(const std::string& modelPath);
        void requestLoadTexture(const std::string &texturePath);
        void processLoadQueue();
        void addModel(const std::string &modelPath);
        void addTexture(const std::string &TexturePath);
        void UnloadAll();
    private:
        std::map<const std::string, raylib::Model> _models;
        std::map<const std::string, raylib::Texture> _texturesModels;
        std::map<const std::string, raylib::Texture> _textures;
        std::queue<std::string> _pendingLoads;
        std::queue<std::string> _pendingTextureLoads;
        std::mutex _mutex;
    };
}

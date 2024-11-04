/*
** EPITECH PROJECT, 2024
** R-Type - Components : Light
** File description:
** Light Component
*/
#pragma once

#include <iostream>
#if defined(_WIN32)           
	#define NOGDI
	#define NOUSER
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)
	#undef near
	#undef far
#endif

namespace ECS {
    namespace Components {
        typedef enum {
            LIGHT_DIRECTIONAL = 0,
            LIGHT_POINT
        } LightType;

        class Light {
        public:
            Light(const std::string& shader, int type = LIGHT_POINT, raylib::Vector3 position = raylib::Vector3(0.0f, 0.0f, 0.0f), raylib::Vector3 target = raylib::Vector3(0.0f, 0.0f, 0.0f), raylib::Color color = raylib::Color(255, 255, 255, 255));
            Light(const Light& other);
            Light& operator=(const Light& other);
            void initLight(int idLight, raylib::Shader &shader);
            void update(raylib::Shader &shader);
            void setPosition(raylib::Vector3 position);
            void setTarget(raylib::Vector3 target);
            void enable();
            void disable();
            std::string getPath();
            ~Light() = default;
        private:
            int _id;
            LightType _type;
            raylib::Vector3 _position;
            raylib::Vector3 _target;
            raylib::Color _color;
            std::string _shader;
            bool _enabled;
            float _attenuation;
            int _enabledLoc;
            int _typeLoc;
            int _positionLoc;
            int _targetLoc;
            int _colorLoc;
            int _attenuationLoc;
        };
    }
}

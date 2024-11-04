#pragma once
#include <iostream>
#include <string>
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

        class Render3D {
        public:
            Render3D(const std::string &path);
            Render3D(const Render3D& other);
            Render3D& operator=(const Render3D& other);
            ~Render3D() = default;

            void render(raylib::Model &model, raylib::Vector3 position, raylib::Vector3 rotation, raylib::Vector3 scale);
            const raylib::Color &getColor() const;
            void setColor(const raylib::Color &color);
            const std::string getPath() const;

        private:
            raylib::Color _color;
            std::string _path;
        };
    }
}

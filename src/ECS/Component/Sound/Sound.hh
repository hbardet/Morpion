/*
** EPITECH PROJECT, 2024
** R-Type - Components : Sound
** File description:
** Sound Component
*/

#pragma once
#if defined(_WIN32)           
	#define NOGDI
	#define NOUSER
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)
	#undef near
	#undef far
#endif

#include <string>

namespace ECS {
    namespace Components {

        class SoundEffect {
        public:
            SoundEffect(const std::string &filePath);
            ~SoundEffect() = default;

            void play();
            void stop();
            void setVolume(float volume);
            float getVolume() const;

        private:
            Sound _soundEffect;
            float _volume;
        };
    }
}

/*
** EPITECH PROJECT, 2024
** R-Type - Components : Music
** File description:
** Music Component
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
namespace ECS {
    namespace Components {

        class Musica {
        public:
            Musica(const std::string &filePath);
            ~Musica() = default;

            void play();
            void playFrom(float startTime);
            void stop();
            void pause();
            void resume();
            void update();
            float getTimePlayed() const;
            void setVolume(float volume);
            float getVolume() const;

        private:
            Music _musicStream;
            bool _isPaused;
            float _volume;
        };

    }
}

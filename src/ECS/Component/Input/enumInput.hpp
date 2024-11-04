/*
** EPITECH PROJECT, 2024
** R-Type - enumInput
** File description:
** enumInput
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

        typedef enum enumInput_e {
            MENU = 0,
            RIGHT = 1,
            UP = 2,
            LEFT = 3,
            DOWN = 4,
            SPACE = 5
        } enumInput_t;
    }
}

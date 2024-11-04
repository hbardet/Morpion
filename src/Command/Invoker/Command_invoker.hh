/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_invoker
*/

#pragma once
#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif
#include <iostream> 
#include <iostream>
#include <queue>
#include <string>
#include "../ACommand.hpp"

namespace Rtype
{
    namespace Command
    {
        class Command_invoker {
            public:
                Command_invoker(std::string invoker_type);
                ~Command_invoker();

                void executeCommand();

                void addCommand(std::unique_ptr<Rtype::Command::ACommand> cmd);

            protected:
            private:
                std::string _invokerType;
                std::queue<std::unique_ptr<Rtype::Command::ACommand>> _commandQueue;
        };
    }
}

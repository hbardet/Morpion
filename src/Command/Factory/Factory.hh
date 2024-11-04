/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Factory
*/

#pragma once
#if defined(_WIN32)           
	#define NOGDI
	#define NOUSER
#endif

#if defined(_WIN32)
	#undef near
	#undef far
#endif

#include "../ICommand.hh"
#include "../ACommand.hpp"
#include "../../Utils/ParametersMap/ParametersMap.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>

#include "../Commands/Game_info/Client_connection/Client_connection.hh"
#include "../Commands/Game_info/Create_game/Create_game.hh"
#include "../Commands/Game_info/Games_available/Games_available.hh"
#include "../Commands/Game_info/Game_result/Game_result.hh"
#include "../Commands/Game_info/Join_game/Join_game.hh"
#include "../Commands/Game_info/Client_disconnect/Client_disconnect.hh"
#include "../Commands/Game_info/Missing_packages/Missing_packages.hh"

#include "../Commands/Player/SetPawn/SetPawn.hh"

namespace Rtype
{
    namespace Command
    {
        class Factory {
            public:
                Factory();
                ~Factory() = default;

                std::unique_ptr<Rtype::Command::ACommand> createCommand(uint8_t cmd_category, uint8_t cmd_index);

            protected:
            private:
                std::map<std::pair<uint8_t, uint8_t>, std::function<std::unique_ptr<ACommand>()>> _commandMap;
        };
    }
}

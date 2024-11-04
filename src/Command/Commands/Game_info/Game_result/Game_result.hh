/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_result
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
#include "../../../ACommand.hpp"
#include "../../../../Server/Game_info.hh"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Game_result: public ACommand{
                public:
                    Game_result() = default;
                    ~Game_result();

                    void set_client();
                    void set_server(std::shared_ptr<Rtype::Game_info> game_info);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                std::shared_ptr<Rtype::Game_info> _gameInfo;
            };
        }
    }
}

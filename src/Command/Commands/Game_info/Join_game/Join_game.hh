/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Join_game
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
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Join_game: public ACommand{
                public:
                    Join_game() = default;
                    ~Join_game();

                    void set_client(int gameRoom);
                    void set_server();
                    void set_server(std::shared_ptr<Rtype::Game_info> game, std::shared_ptr<Rtype::client_info> client_info);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    bool _exist;
                    int _gameRoom;
                    std::shared_ptr<Rtype::Game_info> _gameInfo;
                    std::shared_ptr<Rtype::client_info> _clientInfo;
            };
        }
    }
}

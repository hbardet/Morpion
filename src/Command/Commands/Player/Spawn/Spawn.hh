/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
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
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            class Spawn: public ACommand{
                public:
                    Spawn() = default;
                    ~Spawn();

                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, int roomId, double x, double y);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _playerID;
                    int _roomId;
                    double _x;
                    double _y;
            };
        }
    }
}

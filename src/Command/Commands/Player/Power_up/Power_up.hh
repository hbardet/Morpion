/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Power_up
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
            class Power_up: public ACommand{
                public:
                    Power_up() = default;
                    ~Power_up();

                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, int powerUpID);
                    void set_client(int podId);

                    void execute_client_side();
                    void execute_server_side();
            
                protected:
                private:
                    udp::endpoint _endpoint;
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _playerID;
                    int _powerUpID;
            };
        }
    }
}

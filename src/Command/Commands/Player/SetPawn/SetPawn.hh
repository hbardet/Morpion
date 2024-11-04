/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SetPawn
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
            class SetPawn: public ACommand{
                public:
                    SetPawn() = default;
                    ~SetPawn();

                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int coo, int id);
                    void set_client(int coo);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    udp::endpoint _endpoint;
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _coo;
                    int _id;
            };
        }
    }
}

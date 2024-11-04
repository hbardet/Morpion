/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_connection
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
#include <map>

namespace Rtype
{

    namespace Command
    {
        namespace GameInfo
        {
            class Client_connection : public ACommand{
                public:
                    Client_connection() = default;
                    ~Client_connection();

                    void set_client();
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> &clients, int port, std::string addr);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    int get_available_client_id();

                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _clients;
                    int _port;
                    std::string _addr;
            };
        }
    }
}

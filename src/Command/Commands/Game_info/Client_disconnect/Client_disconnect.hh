/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_disconnect
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Game_info.hh"

namespace Rtype
{
    namespace Command
    {
        namespace GameInfo
        {
            class Client_disconnect: public ACommand {
                public:
                    Client_disconnect() = default;
                    ~Client_disconnect();

                    void set_client();
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int id);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    int _id;
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
            };
        }
    }
}

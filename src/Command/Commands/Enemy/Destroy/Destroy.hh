/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Destroy
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Enemy
        {
            class Destroy: public ACommand{
                public:
                    Destroy() = default;
                    ~Destroy();

                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int mobID, int roomId);
                    void set_client();

                    void execute_client_side();
                    void execute_server_side();
            
                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _mobID;
                    int _roomID;
            };
        }
    }
}

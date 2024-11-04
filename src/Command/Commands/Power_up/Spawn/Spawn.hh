/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#pragma once
#include "../../../ACommand.hpp"
#include "../../../../Server/Client_info.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace PowerUp
        {
            class Spawn: public ACommand{
                public:
                    Spawn() = default;
                    ~Spawn();

                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int podID, double x, double y);
                    void set_client(double x, double y);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _podID;
                    double _x;
                    double _y;
            };
        }
    }
}

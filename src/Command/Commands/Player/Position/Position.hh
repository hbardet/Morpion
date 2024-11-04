/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position.hpp
*/

#pragma once
#include "../../../ACommand.hpp"

namespace Rtype
{
    namespace Command
    {
        namespace Player
        {
            class Position: public ACommand
            {
            private:
                double _x;
                double _y;
                int _player_id;
            public:
                Position() = default;
                ~Position();

                void set_client();
                void set_server(int player_id, double x, double y);

                void execute_client_side();
                void execute_server_side();
            };
        }
    }
}
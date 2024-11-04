/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Games_available
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
            class Games_available: public ACommand{
                public:
                    Games_available() = default;
                    ~Games_available();

                    void set_client();
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> games);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> _games;
            };
        }
    }
}

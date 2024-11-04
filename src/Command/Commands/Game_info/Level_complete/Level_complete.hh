/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level_complete
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
            class Level_complete: public ACommand {
                public:
                    Level_complete() = default;
                    ~Level_complete();

                    void set_client();
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int level);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    int _level;
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
            };
        }
    }
}

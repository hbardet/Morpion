/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Create_game
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
            class Create_game: public ACommand{
                public:
                    Create_game() = default;
                    ~Create_game();

                    void set_client(int difficulty, int maxNbPlayer);
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> games, int difficulty, int maxNbPlayer);

                    void execute_client_side();
                    void execute_server_side();

                protected:
                private:
                    int getRoomIdAvailable(bool set_seed) const;

                    int _difficulty;
                    int _maxNbPlayer;
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> _games;
            };
        }
    }
}

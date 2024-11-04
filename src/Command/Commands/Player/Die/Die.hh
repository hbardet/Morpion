/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
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
            class Die: public ACommand{
                public:
                    Die() = default;
                    ~Die();

                    void set_client();
                    void set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID);

                    void execute_client_side();
                    void execute_server_side();
            
                protected:
                private:
                    std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
                    int _playerID;
            };
        }
    }
}

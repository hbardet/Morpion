/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ICommand
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

#include "../Client/Game/Game.hh"
#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace Rtype
{
    namespace Command
    {
        class ICommand {
            public:
                virtual ~ICommand() {}
                virtual void execute_client_side() = 0;
                virtual void execute_server_side() = 0;
                virtual void setOrigins(std::string origins) = 0;
        };
    }
}

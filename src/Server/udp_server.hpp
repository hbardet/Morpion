/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Server Class
** udp_server
*/

/**
 * @file udp_server.hpp
 * @brief Declaration of the Rtype::udpServer class for UDP server communication.
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
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <unordered_map>
#include "Client_info.hpp"
#include "Game_info.hh"

#include "../Utils/Response/Response.hpp"
#include "../Utils/Network/Network.hpp"

using boost::asio::ip::udp;
using boost::asio::ip::address;

namespace Rtype {
    /**
     * @class udpServer
     * @brief Class to manage an UDP server.
     */
    class udpServer
    {
        public:
            /**
             * @brief Constructor for the udpServer class.
             * @param port The port on which the server will listen.
             */
            udpServer(short port);

            /**
             * @brief Destructor for the udpServer class.
             */
            ~udpServer();

            /**
             * @brief Run the network thread and the game.
             */
            void run();

            /**
             * @brief Read asynchronously data from clients.
             */
            void read_clients();

        private:
            /**
             * @brief Retrieves the ID of the sender.
             * @return Sender's ID.
             */
            int get_sender_id();

            /**
             * @brief Retrieves the client ID by its address.
             * @param addr Client's IP address.
             * @param port Client's port number.
             * @return Client ID if found, -1 otherwise.
             */
            int get_client_id_by_addr(std::string addr, int port);

            /**
             * @brief Retrieves the last sender client ID.
             * @return Client ID if found, -1 otherwise.
             */
            int get_sender_client_id();

            /**
             * @brief Checks if a client exists by its address.
             * @param addr Client's IP address.
             * @param port Client's port number.
             * @return true if the client exists, false otherwise.
             */
            bool is_client_by_addr(std::string addr, int port);

            /**
             * @brief Disconnects a client by its ID.
             * @param client_id Client's ID.
             */
            void disconnect_client(int client_id);

            /**
             * @brief Run the IO service.
             */
            void runNetwork();

            template <typename T>
            std::unique_ptr<T> convertACommandToCommand(std::unique_ptr<Rtype::Command::ACommand> base) {
                static_assert(std::is_base_of<Rtype::Command::ACommand, T>::value);

                T* derived = dynamic_cast<T*>(base.get());
                if (derived) {
                    base.release();
                    return std::unique_ptr<T>(derived);
                } else
                    return nullptr;
            }

            void handleResponse(Utils::Network::Response clientResponse);

            void setHandleMaps();
            void setHandleGameInfoMap();
            void setHandlePlayerMap();

            std::unordered_map<Utils::GameInfoEnum, std::function<void(Utils::Network::Response)>> _handleGameInfoMap;
            std::unordered_map<Utils::PlayerEnum, std::function<void(Utils::Network::Response)>> _handlePlayerMap;
            void initSignalHandlers();

            boost::asio::io_service _ioService;
            std::shared_ptr<Rtype::Network> _network;
            udp::endpoint _senderEndpoint;
            enum { max_length = 1024 }; // Maximum length of the receive buffer.
            char _data[max_length];
            std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _clients;
            std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> _games;
            std::thread _networkThread;
            boost::asio::signal_set _signals;
            std::atomic<bool> _stop;
    };
}

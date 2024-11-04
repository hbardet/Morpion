/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client_info
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

#include <iostream>
#include <string>
#include <cstdarg>
#include <map>
#include <vector>
#include "../Utils/ParametersMap/ParametersMap.hpp"
#include "../Utils/Protocol/Protocol.hpp"
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using boost::asio::ip::address;

/**
 * @file Client_info.cpp
 * @brief Declaration of the client info class in order to handle information of the clients in the R-Type Game
 */


namespace Rtype {

    /**
     * @brief The client_info class represents information about a client in the R-Type game.
     * 
     * This class stores various attributes of a client such as their ID, position, address, 
     * and connection information. It also provides methods to manipulate and retrieve these attributes.
     */
    class client_info {
        public:
            /**
             * @brief Default constructor for client_info.
             */
            client_info();

            /**
             * @brief Parameterized constructor for client_info.
             * 
             * @param id The unique identifier for the client.
             * @param port The port number used by the client.
             * @param addr The IP address of the client.
             */
            client_info(int id, int port, std::string addr);

            /**
             * @brief Destructor for client_info.
             */
            ~client_info();

            /**
             * @brief Gets the unique identifier of the client.
             * 
             * @return The client's ID.
             */
            int getId() const;

            /**
             * @brief Sets the unique identifier of the client.
             * 
             * @param id The new ID for the client.
             */
            void setId(int id);

            /**
             * @brief Gets the expected ACK number for the client.
             * 
             * @return The expected ACK number.
             */
            int getAckToExpect() const;

            /**
             * @brief Increments the expected ACK number for the client.
             */
            void setAckToExpect();

            /**
             * @brief Gets the ACK number to be sent to the client.
             * 
             * @return The ACK number to be sent.
             */
            uint32_t getAckToSend() const;

            /**
             * @brief Increments the ACK number to be sent to the client.
             */
            void setAckToSend();

            /**
             * @brief Gets the game room number the client is in.
             * 
             * @return The game room number.
             */
            int getRoom() const;

            /**
             * @brief Sets the game room number for the client.
             * 
             * @param room The new game room number.
             */
            void setRoom(int room);

            /**
             * @brief Gets the port number used by the client.
             * 
             * @return The client's port number.
             */
            int getPort() const;

            /**
             * @brief Sets the port number for the client.
             * 
             * @param port The new port number.
             */
            void setPort(int port);

            /**
             * @brief Gets the IP address of the client.
             * 
             * @return The client's IP address.
             */
            std::string getAddr() const;

            /**
             * @brief Sets the IP address of the client.
             * 
             * @param address The new IP address.
             */
            void setAddr(std::string address);

            /**
             * @brief Adds a command to the client's command history.
             * 
             * This method handle a variadic list of parameters, converts them to strings,
             * and stores them in the client's history.
             * 
             * @param msg The command to add to the history.
             */
            void pushCmdToHistory(Utils::Network::bytes msg)
            {
                _history[_AckToSend] = msg;
                setAckToSend();
            }

            Utils::Network::bytes getCmdFromHistory(int ack)
            {
                return _history[ack];
            }

        private:
            int _id;
            float _x;
            float _y;
            int _AckExpected;
            uint32_t _AckToSend;
            int _gameRoom;
            bool _inGame;
            bool _isAlive;
            int _port;
            std::string _addr;
            std::map<int, Utils::Network::bytes> _history;
    };
}

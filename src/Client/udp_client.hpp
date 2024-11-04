/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

/**
 * @file udp_client.hpp
 * @brief Declaration of the Rtype::udpClient class for UDP communication with a server.
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

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <array>
#include <atomic>
#include <unordered_set>

#include "../Utils/Network/Network.hpp"

#define CONVERT_ACMD_TO_CMD(TYPE, CMD_CATEGORY, CMD_INDEX)  _network->convertACommandToCommand<TYPE>(_network->createCommand(static_cast<uint8_t>(CMD_CATEGORY), static_cast<uint8_t>(CMD_INDEX)))

using boost::asio::ip::udp;

namespace Rtype {

    class Network;
    /**
     * @class udpClient
     * @brief Class to manage a UDP client.
     */
    class udpClient
    {
    public:
        /**
         * @brief Constructor for the udpClient class.
         * @param serverAddr Server's IP address.
         * @param serverPort Server's port.
         */
        udpClient(const std::string &serverAddr, const int serverPort);

        /**
         * @brief Destructor for the udpClient class.
         */
        ~udpClient();

        /**
         * @brief Run the network thread and the game.
         */
        void run();

        std::vector<uint32_t> getMissingPackages(); // used in the time thread
    private:
        void read_server();

        /**
         * @brief Handle the response from the server.
         * @param clientResponse The response from the server.
         */
        void handleResponse(Utils::Network::Response clientResponse);

        void connectClient();

        void setHandleMaps();
        void setHandleGameInfoMap();
        void setHandlePlayerMap();
        void setHandleEnemyMap();
        void setHandlePowerUpMap();
        void setHandleProjectileMap();
        void setHandleBossMap();

        /**
         * @brief Run the IO context.
         */
        void runNetwork();

        std::unordered_map<Utils::GameInfoEnum, std::function<void(Utils::Network::Response)>> _handleGameInfoMap;
        std::unordered_map<Utils::PlayerEnum, std::function<void(Utils::Network::Response)>> _handlePlayerMap;
        std::unordered_map<Utils::PowerUpEnum, std::function<void(Utils::Network::Response)>> _handlePowerUpMap;
        std::unordered_map<Utils::ProjectileEnum, std::function<void(Utils::Network::Response)>> _handleProjectileMap;
        std::unordered_map<Utils::EnemyEnum, std::function<void(Utils::Network::Response)>> _handleEnemyMap;
        std::unordered_map<Utils::BossEnum, std::function<void(Utils::Network::Response)>> _handleBossMap;
        void initSignalHandlers();

        int _id;
        int _destroyMin;
        boost::asio::io_context _ioContext;
        std::unordered_set<uint32_t> _recivedPackages;
        uint32_t _biggestAck;
        std::shared_ptr<Rtype::Network> _network;
        std::array<char, 1024> _receiverBuffer;
        std::thread _networkThread;  // New thread for the network loop.
        std::thread _timeThread;  // New thread for the time loop.
        boost::asio::signal_set _signals;
        std::mutex _mutex;
        std::unique_ptr<Rtype::Game> _game;
        std::atomic<bool> _stop;
    };
}

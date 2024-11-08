    /*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_info
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
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <thread>
#include <stack>
#include "Client_info.hpp"
#include "Parser/LoadData/LoadData.hh"

#define MAX_UINT32  (4294967295U)

namespace Rtype
{
    class Game;

    class Network;

    class Game_info {
        public:
            Game_info();
            Game_info(int id);
            ~Game_info();

            // Game_info(const Game_info&) = delete;
            // Game_info& operator=(const Game_info&) = delete;

            // Game_info(Game_info&& other) noexcept;
            // Game_info& operator=(Game_info&& other) noexcept;

            void setNetwork(std::shared_ptr<Rtype::Network> network);
            std::shared_ptr<Rtype::Game> getGame();

            void runGame();
            void placePawn(int coo, int player);

            int getRoomId(void);
            char gameStatus(int id);
            bool isGameAvailable(void);
            bool getToSetNetwork();
            std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> getPlayers(void);
            int getNbMaxPlayers();

            void connectPlayer(std::shared_ptr<Rtype::client_info> player);
            void disconnectPlayer(int id);

        protected:
        private:
            int _id;
            std::map<char, char> _map;
            std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> _players;
            std::shared_ptr<Rtype::Network> _network;
            std::shared_ptr<Rtype::Game> _game;
            bool _toSetNetwork;
            std::thread _gameThread;
            std::mutex _playersMutex;
            // Todo compile with Game class
    };
}

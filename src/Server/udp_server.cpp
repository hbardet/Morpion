/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Server Class
** udp_server
*/

/**
 * @file udp_server.cpp
 * @brief Implementation of the Rtype::udpServer class for UDP server communication.
 */

#include "udp_server.hpp"

Rtype::udpServer::udpServer(short port)
    : _ioService(), _signals(_ioService, SIGINT),  _stop(false)
{
    _network = std::make_shared<Rtype::Network>(_ioService, port, "Server");
    _clients = std::make_shared<std::map<int, std::shared_ptr<Rtype::client_info>>>();
    _games = std::make_shared<std::map<int, std::shared_ptr<Rtype::Game_info>>>();
    Utils::ParametersMap::init_map();
    std::memset(_data, 0, max_length);
    setHandleMaps();
    read_clients();
    initSignalHandlers();
}

Rtype::udpServer::~udpServer()
{
    _ioService.stop();
    if (_networkThread.joinable())
        _networkThread.join();
}

void Rtype::udpServer::run()
{
    _networkThread = std::thread([this]() {
        this->runNetwork();
    });
    while (!_stop) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Rtype::udpServer::runNetwork()
{
    _ioService.run();
}

void Rtype::udpServer::initSignalHandlers()
{
    _signals.async_wait(
        [this](boost::system::error_code ec, int signal_number) {
            if (!ec) {
                _stop = true;
            }
        }
    );
}

void Rtype::udpServer::read_clients()
{
    _network->executeInvoker();
    _network->getSocket()->async_receive_from(boost::asio::buffer(_data, max_length), _senderEndpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
        Utils::Network::Response clientResponse;
        Utils::Network::bytes data;

        if (!ec && recvd_bytes > 0 && recvd_bytes < max_length) {
            _network->setSenderEndpoint(_senderEndpoint);
            std::memset(_data + recvd_bytes, 0, max_length - recvd_bytes);
            data = Utils::Network::bytes(std::begin(_data), std::end(_data));
            clientResponse = Utils::Network::Protocol::ParseMsg(false, data);
            handleResponse(clientResponse);
        }
        for (auto game: *_games)
            if (game.second->getToSetNetwork()) {
                game.second->setNetwork(_network);
                game.second->runGame();
            }
        read_clients();
    });
}

int Rtype::udpServer::get_sender_id()
{
    return get_client_id_by_addr(_network->getSenderEndpoint().address().to_string(), (int)_network->getSenderEndpoint().port());
}

int Rtype::udpServer::get_client_id_by_addr(std::string addr, int port)
{
    for (auto client: *_clients)
        if (client.second->getAddr() == addr && client.second->getPort() == port)
            return client.first;
    return -1;
}

int Rtype::udpServer::get_sender_client_id()
{
    return get_client_id_by_addr(_network->getSenderEndpoint().address().to_string(), (int)_network->getSenderEndpoint().port());
}

bool Rtype::udpServer::is_client_by_addr(std::string addr, int port)
{
    return get_client_id_by_addr(addr, port) != -1;
}

void Rtype::udpServer::disconnect_client(int client_id)
{
    _clients->erase(client_id);
}

void Rtype::udpServer::setHandleMaps() {
    setHandleGameInfoMap();
    setHandlePlayerMap();
}

void Rtype::udpServer::setHandleGameInfoMap() {

    _handleGameInfoMap[Utils::GameInfoEnum::NewClientConnected] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_connection, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);
        
        cmd->set_server(_clients, (int)_network->getSenderEndpoint().port(), _network->getSenderEndpoint().address().to_string());
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), 0);
        _network->addCommandToInvoker(std::move(cmd));
 
    };

    _handleGameInfoMap[Utils::GameInfoEnum::CreateGame] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::GameInfo::Create_game> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Create_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::CreateGame);
        int difficulty = clientResponse.PopParam<int>();
        int nbMaxPlayer = clientResponse.PopParam<int>();

        cmd->set_server(_games, difficulty, nbMaxPlayer);
        cmd->setClientInfo(_clients->at(get_sender_client_id()));
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::GamesAvailable] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::GameInfo::Games_available> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Games_available, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable);
        
        cmd->set_server(_games);
        cmd->setClientInfo(_clients->at(get_sender_client_id()));
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        _network->addCommandToInvoker(std::move(cmd));
    };

    _handleGameInfoMap[Utils::GameInfoEnum::JoinGame] = [this](Utils::Network::Response clientResponse) {
        int id_room = clientResponse.PopParam<int>();
        std::unique_ptr<Rtype::Command::GameInfo::Join_game> join_cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Join_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame);
        bool join_game = true;

        if (_games->find(id_room) != _games->end()) {
            join_cmd->set_server(_games->at(id_room), _clients->at(get_sender_client_id()));
            join_game = _games->at(id_room)->isGameAvailable();
        } else {
            join_cmd->set_server();
            join_game = false;
        }
        join_cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
        join_cmd->setClientInfo(_clients->at(get_sender_client_id()));
        _network->addCommandToInvoker(std::move(join_cmd));
        if (join_game) {
            CONSOLE_INFO("Player is joining game: ", id_room)
            CONSOLE_INFO("Player is spawning in game: ", id_room)
            //! Spawn mob of the game
        }
    };

    _handleGameInfoMap[Utils::GameInfoEnum::ClientDisconnect] = [this](Utils::Network::Response clientResponse) {
        std::unique_ptr<Rtype::Command::GameInfo::Client_disconnect> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_disconnect, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::ClientDisconnect);
        int gameID = _clients->at(get_sender_client_id())->getRoom();

        if (_games->find(gameID) != _games->end()) {
            CONSOLE_INFO("Client is disconnecting", "")
            cmd->set_server(_games->at(gameID)->getPlayers(), get_sender_client_id());
            cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _clients->at(get_sender_client_id())->getAckToSend());
            cmd->setClientInfo(_clients->at(get_sender_client_id()));
            _network->addCommandToInvoker(std::move(cmd));
            _games->at(gameID)->disconnectPlayer(get_sender_client_id());
        }
        disconnect_client(get_sender_client_id());
    };

    _handleGameInfoMap[Utils::GameInfoEnum::MissingPackages] = [this](Utils::Network::Response clientResponse) {
        int ack = 0;
        Utils::Network::bytes msg;
        std::unique_ptr<Rtype::Command::GameInfo::Missing_packages> cmd;

        for (std::size_t i = 0; i < 4; i++) {
            ack = clientResponse.PopParam<int>();
            if (ack == 0)
                break;
            msg = _clients->at(get_sender_client_id())->getCmdFromHistory(ack);
            cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Missing_packages, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::MissingPackages);
            cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            cmd->set_server(msg);
            _network->addCommandToInvoker(std::move(cmd));
        }
    };

    _handleGameInfoMap[Utils::GameInfoEnum::MissingPackages] = [this](Utils::Network::Response clientResponse) {
        int ack = 0;
        Utils::Network::bytes msg;
        std::unique_ptr<Rtype::Command::GameInfo::Missing_packages> cmd;

        for (std::size_t i = 0; i < 4; i++) {
            ack = clientResponse.PopParam<int>();
            if (ack == 0)
                break;
            msg = _clients->at(get_sender_client_id())->getCmdFromHistory(ack);
            cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Missing_packages, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::MissingPackages);
            cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            cmd->set_server(msg);
            _network->addCommandToInvoker(std::move(cmd));
        }
    };
}

void Rtype::udpServer::setHandlePlayerMap() {
    _handlePlayerMap[Utils::PlayerEnum::PlayerAttack] = [this](Utils::Network::Response clientResponse) {
   };
}

void Rtype::udpServer::handleResponse(Utils::Network::Response clientResponse)
{
    Utils::InfoTypeEnum cmd_category = clientResponse.GetInfoType();

    CONSOLE_INFO("Handle Response category: ", (int)cmd_category)
    CONSOLE_INFO("Handle Response index: ", (int)clientResponse.GetInfoFunction())
    switch (cmd_category)
    {
    case Utils::InfoTypeEnum::GameInfo:
        _handleGameInfoMap[static_cast<Utils::GameInfoEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case Utils::InfoTypeEnum::Player:
        _handlePlayerMap[static_cast<Utils::PlayerEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    default:
        std::cerr << "Unknown command" << std::endl;
        break;
    }
}

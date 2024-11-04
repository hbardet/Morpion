/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Client Class
** udp_client
*/

#include "./udp_client.hpp"
#include "../Utils/Protocol/Protocol.hpp"

Rtype::udpClient::udpClient(const std::string &serverAddr, const int serverPort):
    _id(-1), _destroyMin(-1), _ioContext(), _biggestAck(0), _signals(_ioContext, SIGINT),  _stop(false)
{
    _network = std::make_shared<Rtype::Network>(_ioContext, serverAddr, serverPort, "Client");
    _game = std::make_unique<Rtype::Game>(_network, true);

    setHandleMaps();
    connectClient();
    read_server();
    initSignalHandlers();

    _timeThread = std::thread([this]() {
        std::lock_guard<std::mutex> lock(_mutex);
        std::vector<uint32_t> missing_ack;
        std::size_t missing_ack_size = 0;
        std::size_t tail_size;

        while (_stop.load() == false) {
            std::cout << "stop :" << _stop.load() << std::endl;
            std::unique_ptr<Rtype::Command::GameInfo::Missing_packages> last_cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Missing_packages, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::MissingPackages);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            missing_ack = getMissingPackages();
            missing_ack_size = missing_ack.size();
            tail_size = missing_ack_size & 3;

            for (size_t i = 0; i < (missing_ack_size >> 2); i++) {
            std::unique_ptr<Rtype::Command::GameInfo::Missing_packages> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Missing_packages, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::MissingPackages);
                cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
                cmd->set_client(missing_ack[i * 4], missing_ack[i * 4 + 1], missing_ack[i * 4 + 2], missing_ack[i * 4 + 3]);
                _network->addCommandToInvoker(std::move(cmd));
            }

            if (tail_size) {
                last_cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
                last_cmd->set_client(
                    missing_ack[missing_ack_size - 1],
                    (tail_size & 2) ? missing_ack[missing_ack_size - 2] : 0,
                    (tail_size == 3) ? missing_ack[missing_ack_size - 3] : 0,
                    0
                );
                _network->addCommandToInvoker(std::move(last_cmd));
            }
        }
    });
}

Rtype::udpClient::~udpClient()
{
    std::unique_ptr<Rtype::Command::GameInfo::Client_disconnect> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_disconnect, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::ClientDisconnect);

    cmd->set_client();
    cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
    _network->addCommandToInvoker(std::move(cmd));
    if (_network->getSocket()->is_open()) {
        _network->getSocket()->cancel();
        _network->getSocket()->close();
    }
    _ioContext.stop();

    _stop.store(true);
    if (_networkThread.joinable()) {
        _networkThread.join();
    }
    if (_timeThread.joinable()) {
        _timeThread.join();
    }

    std::cout << "Client disconnected successfully." << std::endl;
}

void Rtype::udpClient::run()
{
    _networkThread = std::thread([this]() {
        this->runNetwork();
    });
    _game->run();
}

void Rtype::udpClient::runNetwork()
{
    _ioContext.run();
}

void Rtype::udpClient::initSignalHandlers()
{
    _signals.async_wait(
        [this](boost::system::error_code ec, int signal_number) {
            if (signal_number == SIGINT) {
                _stop.store(true);
                _ioContext.stop();
                _game->setIsRunning(false);
            }
        }
    );
}

void Rtype::udpClient::read_server()
{
    auto sender_endpoint = std::make_shared<udp::endpoint>();

    if (_stop)
        return;
    if (!_stop) {
        _network->getSocket()->async_receive_from(boost::asio::buffer(_receiverBuffer), *sender_endpoint,
        [this, sender_endpoint](const boost::system::error_code& error, std::size_t bytes_recv) {
            Utils::Network::Response clientResponse;
            Utils::Network::bytes data;

            if (!error && bytes_recv > 0) {
                data = Utils::Network::bytes(std::begin(_receiverBuffer), std::end(_receiverBuffer));
                clientResponse = Utils::Network::Protocol::ParseMsg(true, data);
                handleResponse(clientResponse);
            } else if (error) {
                std::cerr << "Error receiving data: " << error.message() << std::endl;
            }
            read_server();
        });
    }
}

void Rtype::udpClient::setHandleMaps()
{
    setHandleGameInfoMap();
    setHandlePlayerMap();
}

void Rtype::udpClient::setHandleGameInfoMap()
{
    _handleGameInfoMap[Utils::GameInfoEnum::NewClientConnected] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_connection, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);

        _id = response.PopParam<int>();
        _game->setIsConnectedToServer(true);
        CONSOLE_INFO("Id set on client: ", _id);
    };

    _handleGameInfoMap[Utils::GameInfoEnum::GamesAvailable] = [this](Utils::Network::Response response) {
        int codeRoom = response.PopParam<int>();
        std::unique_ptr<Rtype::Command::GameInfo::Join_game> join_cmd ;

        if (codeRoom == -1) {
            CONSOLE_INFO("No Room available.", "");
            return;
        }
        CONSOLE_INFO(codeRoom, ": is available");
        if (_game->getJoiningGame()) {
            join_cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Join_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame);
            _game->setIsJoiningGame(false);
            join_cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            join_cmd->set_client(codeRoom);
            _network->addCommandToInvoker(std::move(join_cmd));
        }
        if (_game->getIsAvailableGames()) {
            _game->addAvailableGames(codeRoom);
            _game->joinGame();
        }
    };

    _handleGameInfoMap[Utils::GameInfoEnum::CreateGame] = [this](Utils::Network::Response response) {
        int codeRoom = response.PopParam<int>();
        std::unique_ptr<Rtype::Command::GameInfo::Join_game> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Join_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame);

        if (codeRoom == -1) {
            CONSOLE_INFO("Game failed to create, too many game.", "")
        }
        CONSOLE_INFO("Game created: ", codeRoom)
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
        cmd->set_client(codeRoom);
        _network->addCommandToInvoker(std::move(cmd));
        CONSOLE_INFO("Join game sended: ", codeRoom)
    };

    _handleGameInfoMap[Utils::GameInfoEnum::JoinGame] = [this](Utils::Network::Response response) {
        bool accepted = response.PopParam<bool>();
        int level = response.PopParam<int>();
        int entityNb = response.PopParam<int>();

        if (!accepted) {
            _game->failToConnect();
            return;
        }
        CONSOLE_INFO("Joining game at level: ", level)
        _game->initGame(_id);
        CONSOLE_INFO("Destroy min is ", entityNb)
        _destroyMin = entityNb;
    };

    _handleGameInfoMap[Utils::GameInfoEnum::GameWonLost] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::GameInfo::Game_result> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Game_result, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GameWonLost);
        bool won = response.PopParam<bool>();

        if (won) {
            std::cerr << "You won!" << std::endl;
        } else {
            std::cerr << "You lost!" << std::endl;
        }
    };

    _handleGameInfoMap[Utils::GameInfoEnum::ClientDisconnect] = [this](Utils::Network::Response response) {
        int id = response.PopParam<int>();

        _game->destroyEntity(id);
    };
    
    _handleGameInfoMap[Utils::GameInfoEnum::MissingPackages] = [this](Utils::Network::Response response) {
        (void)response;
        std::cerr << "Missing packages should not be recived by the client" << std::endl;
    };
    
    _handleGameInfoMap[Utils::GameInfoEnum::MissingPackages] = [this](Utils::Network::Response response) {
        (void)response;
        std::cerr << "Missing packages should not be recived by the client" << std::endl;
    };
};


void Rtype::udpClient::setHandlePlayerMap()
{
    _handlePlayerMap[Utils::PlayerEnum::PlayerAttack] = [this](Utils::Network::Response response) {
        std::unique_ptr<Rtype::Command::Player::Attack> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::Player::Attack, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerAttack);

        int missileId = response.PopParam<int>();
    };
}

void Rtype::udpClient::handleResponse(Utils::Network::Response clientResponse)
{
    Utils::InfoTypeEnum cmd_category = clientResponse.GetInfoType();
    uint32_t ack = clientResponse.getACK();

    _recivedPackages.insert(ack);
    if (ack > _biggestAck)
        _biggestAck = ack;

    CONSOLE_INFO("Handle Response category: ", (int)cmd_category)
    CONSOLE_INFO("Handle Response index: ", (int)clientResponse.GetInfoFunction())

    try {
    switch (cmd_category) {
    case Utils::InfoTypeEnum::GameInfo:
        _handleGameInfoMap[static_cast<Utils::GameInfoEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    case Utils::InfoTypeEnum::Player:
        _handlePlayerMap[static_cast<Utils::PlayerEnum>(clientResponse.GetInfoFunction())](clientResponse);
        break;
    default:
        std::cerr << "Unknown command category." << std::endl;
        break;
    }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        switch (cmd_category) {
            case Utils::InfoTypeEnum::GameInfo:
                std::cerr << "GameInfoEnum: " << (int)clientResponse.GetInfoFunction() << std::endl;
                break;
            case Utils::InfoTypeEnum::Player:
                std::cerr << "PlayerEnum: " << (int)clientResponse.GetInfoFunction() << std::endl;
                break;
            default:
                std::cerr << "Unknown command category." << std::endl;
                break;
        }
        exit(84);

    };
}

void Rtype::udpClient::connectClient()
{
    std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd_connection = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_connection, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);
    cmd_connection->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
    _network->addCommandToInvoker(std::move(cmd_connection));
}

std::vector<uint32_t> Rtype::udpClient::getMissingPackages()
{
    std::vector<uint32_t> missingPackages;
    for (int i = 1; i < _biggestAck; i++) {
        if (_recivedPackages.find(i) == _recivedPackages.end())
            missingPackages.push_back(i);
    }
    return missingPackages;
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_connection
*/

#include "Client_connection.hh"

void Rtype::Command::GameInfo::Client_connection::set_client()
{
}

void Rtype::Command::GameInfo::Client_connection::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> &clients, int port, std::string addr)
{
    _clients = clients;
    _port = port;
    _addr = addr;
}

Rtype::Command::GameInfo::Client_connection::~Client_connection()
{
}

void Rtype::Command::GameInfo::Client_connection::execute_client_side()
{
	sendToEndpoint(Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);
}

void Rtype::Command::GameInfo::Client_connection::execute_server_side()
{
    int id = get_available_client_id();

    if (id == -1)
        return;
    _clients->insert({id, std::make_shared<Rtype::client_info>(Rtype::client_info(id, _port, _addr))});
	sendToEndpoint(*_clients->at(id), Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected, id);
}

int Rtype::Command::GameInfo::Client_connection::get_available_client_id()
{
    bool available = false;
    std::map<int, std::shared_ptr<Rtype::client_info>> tmp(*_clients);

    for (int i = 0; i < INT32_MAX; i++) {
        available = true;
        for (auto client: tmp)
            available &= client.second->getId() != i;
        if (available)
            return i;
    }
    return -1;
}

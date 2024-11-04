/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Missing_packages.cpp
*/

#include "Missing_packages.hh"

void Rtype::Command::GameInfo::Missing_packages::set_server(Utils::Network::bytes msg)
{
    _msg = msg;
}

void Rtype::Command::GameInfo::Missing_packages::execute_server_side()
{
    _senderSocket->async_send_to(boost::asio::buffer(_msg), _endpoint,
    [this] (boost::system::error_code ec, std::size_t recvd_bytes) {});
}

void Rtype::Command::GameInfo::Missing_packages::set_client(uint32_t ack0, uint32_t ack1, uint32_t ack2, uint32_t ack3)
{
    _ack0 = ack0;
    _ack1 = ack1;
    _ack2 = ack2;
    _ack3 = ack3;
}


void Rtype::Command::GameInfo::Missing_packages::execute_client_side()
{
    sendToEndpoint(Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::MissingPackages, _ack0, _ack1, _ack2, _ack3);
}

Rtype::Command::GameInfo::Missing_packages::~Missing_packages()
{
}

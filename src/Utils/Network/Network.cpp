/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Network
*/

#include "Network.hpp"

Rtype::Network::Network():
    _commandInvoker("client")
{}

Rtype::Network::Network(boost::asio::io_service &io_service, short port, std::string type):
	_ackToReceive(0), _ackToSend(0), _socket(std::make_shared<udp::socket>(udp::socket(io_service, udp::endpoint(udp::v4(), port)))),
	_endpoint(), _commandInvoker(type), _commandFactory()
{
}

Rtype::Network::Network(boost::asio::io_context &io_context, const std::string &serverAddr, const int serverPort, std::string type):
	_ackToReceive(0), _ackToSend(0), _socket(std::make_shared<udp::socket>(io_context, udp::endpoint(udp::v4(), 0))),
	_endpoint(boost::asio::ip::make_address(serverAddr), serverPort), _commandInvoker(type), _commandFactory()
{
}

Rtype::Network::~Network()
{
}

void Rtype::Network::accAckToSend()
{
	_ackToSend++;
}

void Rtype::Network::accAckToReceive()
{
	_ackToReceive++;
}

int Rtype::Network::getAckToSend()
{
	return _ackToSend;
}

int Rtype::Network::getAckToReceive()
{
	return _ackToReceive;
}

void Rtype::Network::addCommandToInvoker(std::unique_ptr<Rtype::Command::ACommand> cmd)
{
	_commandInvoker.addCommand(std::move(cmd));
	accAckToSend();
    executeInvoker();
}

void Rtype::Network::executeInvoker()
{
	_commandInvoker.executeCommand();
}

std::unique_ptr<Rtype::Command::ACommand> Rtype::Network::createCommand(uint8_t category, uint8_t index)
{
	return _commandFactory.createCommand(category, index);
}

std::shared_ptr<udp::socket> Rtype::Network::getSocket()
{
	return _socket;
}

void Rtype::Network::setSenderEndpoint(udp::endpoint endpoint)
{
	_endpoint = endpoint;
}

udp::endpoint Rtype::Network::getSenderEndpoint()
{
	return _endpoint;
}

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_info
*/

#include "Client_info.hpp"

/**
 * @file Client_info.cpp
 * @brief Implementation of the client info class in order to handle information of the clients in the R-Type Game
 */

Rtype::client_info::client_info():
	_id(-1), _x(0.), _y(0.), _AckExpected(0), _AckToSend(0), _gameRoom(-1),
	_inGame(false), _port(-1), _addr("")
{
}

Rtype::client_info::client_info(int id, int port, std::string addr):
	_id(id), _x(0.), _y(0.), _AckExpected(0), _AckToSend(0), _gameRoom(-1),
	_inGame(false), _port(port), _addr(addr)
{
}

Rtype::client_info::~client_info()
{
}

int Rtype::client_info::getId() const
{
	return _id;
}

void Rtype::client_info::setId(int id)
{
	_id = id;
}

float Rtype::client_info::getX() const
{
	return _x;
}

void Rtype::client_info::setX(float x)
{
	_x = x;
}

void Rtype::client_info::moveX(float x)
{
	_x += x;
}

float Rtype::client_info::getY() const
{
	return _y;
}

void Rtype::client_info::setY(float y)
{
	_y = y;
}

void Rtype::client_info::moveY(float y)
{
	_y += y;
}

int Rtype::client_info::getAckToExpect() const
{
	return _AckExpected;
}

void Rtype::client_info::setAckToExpect()
{
	_AckExpected++;
}

uint32_t Rtype::client_info::getAckToSend() const
{
	return _AckToSend;
}

void Rtype::client_info::setAckToSend()
{
	_AckToSend++;
}

int Rtype::client_info::getRoom() const
{
	return _gameRoom;
}

void Rtype::client_info::setRoom(int room)
{
	_gameRoom = room;
	if (room == -1)
		_inGame = false;
	else
		_inGame = true;
}

int Rtype::client_info::getPort() const
{
	return _port;
}

void Rtype::client_info::setPort(int port)
{
	_port = port;
}

std::string Rtype::client_info::getAddr() const
{
	return _addr;
}

void Rtype::client_info::setAddr(std::string address)
{
	_addr = address;
}

bool Rtype::client_info::isAlive() const
{
	return _isAlive;
}

void Rtype::client_info::setAliveStatus(bool is_alive)
{
	_isAlive = is_alive;
}


/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocol.cpp
*/

#include <doctest/doctest.h>
#include "Utils/Protocol/Protocol.hpp"

void printByteAsBits(uint8_t byte) 
{
    for (int i = 7; i >= 0; --i) {  // Start from the most significant bit
        std::cout << ((byte >> i) & 1);
    }
    std::cout << std::endl;
}

TEST_CASE("Protocol with data compression") {
    uint32_t ack = 4;
    bool param1 = true;
    int param2 = 42;
    bool new_param1;
    int new_param2;

    //                                 | ack        |I|F  |args_bytes |P1| P2
    Utils::Network::bytes msg_exemple = {4, 0, 0, 0, 0, 3, 0xfd, 0xff, 1, 42};
    std::size_t size_of_the_msg = msg_exemple.size();
    std::vector<Utils::PrimitiveType> args = {param1, param2};

    // Let say that the Server send a message to the Client
    Utils::Network::bytes msg = Utils::Network::Protocol::CreateMsg(ack, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame, args);
    CHECK(msg.size() == size_of_the_msg);
    for (size_t i = 0; i < msg_exemple.size(); i++) {
        std::cout << std::hex << (unsigned int)msg_exemple[i] << ", ";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < msg.size(); i++) {
        std::cout << std::hex << (unsigned int)msg[i] << ", ";
    }
    std::cout << std::endl;
    
    for (unsigned int i = 0; i < size_of_the_msg; i++) {
        CHECK(msg[i] == msg_exemple[i]);
    }

    // Let say the Client want to decode the Msg
    Utils::Network::Response resp = Utils::Network::Protocol::ParseMsg(true, msg);
    new_param1 = resp.PopParam<bool>();
    new_param2 = resp.PopParam<int32_t>();  

    CHECK(resp.getACK() == ack);
    CHECK(resp.GetInfoType() == Utils::InfoTypeEnum::GameInfo);
    CHECK(resp.GetInfoFunction() == static_cast<uint8_t>(Utils::GameInfoEnum::JoinGame));

    CHECK(new_param1 == param1);
    CHECK(new_param2 == param2);
}

TEST_CASE("Protocol without data compression") {
    uint32_t ack = 4;
    bool param1 = true;
    int param2 = -2022;
    bool new_param1;
    int new_param2;

    //                                 | ack        |I|F  |args_bytes |P1| P2
    Utils::Network::bytes msg_exemple = {4, 0, 0, 0, 0, 3, 0xf9, 0xff, 1, 0x1a, 0xf8};
    std::size_t size_of_the_msg = msg_exemple.size();
    std::vector<Utils::PrimitiveType> args = {param1, param2};

    // Let say that the Server send a message to the Client
    Utils::Network::bytes msg = Utils::Network::Protocol::CreateMsg(ack, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame, args);
    CHECK(msg.size() == size_of_the_msg);
    for (unsigned int i = 0; i < size_of_the_msg; i++) {
        if (msg[i] != msg_exemple[i])
            std::cout << "fail for i:" << i << std::endl;
        CHECK(msg[i] == msg_exemple[i]);
    }

    // Let say the Client want to decode the Msg
    Utils::Network::Response resp = Utils::Network::Protocol::ParseMsg(true, msg);
    new_param1 = resp.PopParam<bool>();
    new_param2 = resp.PopParam<int32_t>();  

    CHECK(resp.getACK() == ack);
    CHECK(resp.GetInfoType() == Utils::InfoTypeEnum::GameInfo);
    CHECK(resp.GetInfoFunction() == static_cast<uint8_t>(Utils::GameInfoEnum::JoinGame));

    CHECK(new_param1 == param1);
    CHECK(new_param2 == param2);
}

TEST_CASE("Protocol with float") 
{
    uint32_t ack = 42;
    double param1 = 12.8;
    double new_param1;
    double param2 = -21.42;
    double new_param2;

    //                                 | ack        | I| F|args_bytes |    P1     |     P2
    Utils::Network::bytes msg_exemple = {42, 0, 0, 0, 1, 2, 0xf3, 0xff, 0x00, 0x32, 0x54, 0xac}; 
    std::size_t size_of_the_msg = msg_exemple.size();
    std::vector<Utils::PrimitiveType> args = {param1, param2};

    // Let say that the Client send a message to the Server
    Utils::Network::bytes msg = Utils::Network::Protocol::CreateMsg(ack, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove, args);
    CHECK(msg.size() == size_of_the_msg);
    for (unsigned int i = 0; i < size_of_the_msg; i++) {
        if (msg[i] != msg_exemple[i]) {
            std::cout << "fail for i:" << i << std::endl;
            std::cout << std::hex << (unsigned int)msg[i] << " == " << std::dec;
            printByteAsBits(msg[i]);
            std::cout << std::hex << (unsigned int)msg_exemple[i] << " == " << std::dec;
            printByteAsBits(msg_exemple[i]);
        }
        CHECK(msg[i] == msg_exemple[i]);
    }

    // Let say the Client want to decode the Msg
    Utils::Network::Response resp = Utils::Network::Protocol::ParseMsg(false, msg);
    new_param1 = resp.PopParam<double>();
    new_param2 = resp.PopParam<double>();  

    CHECK(resp.getACK() == ack);
    CHECK(resp.GetInfoType() == Utils::InfoTypeEnum::Player);
    CHECK(resp.GetInfoFunction() == static_cast<uint8_t>(Utils::PlayerEnum::PlayerMove));

    CHECK(new_param1 == param1);
    CHECK(new_param2 == param2);
}
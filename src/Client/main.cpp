/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Main of the Client
** main
*/

#include "udp_client.hpp"

bool isValidIpAddress(std::string ipAddress)
{
    boost::system::error_code err;
    boost::asio::ip::address::from_string(ipAddress, err);
    return !err;
}

bool is_number(std::string str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool isValidPort(std::string str)
{
    int port = 0;

    if (is_number(str)) {
        port = std::stoi(str);
        return (port > 0 && port < 10000);
    }
    return false;
}


int main(int argc, char **argv)
{
    if (argc != 3 || (!isValidIpAddress(argv[1]) && std::strcmp(argv[1], "localhost") != 0) || !isValidPort(argv[2])) {
        std::cout << "Usage: udp_client [address] [port]" << std::endl;
        return 84;
    }
    if (std::strcmp(argv[1], "localhost") == 0) {
        Rtype::udpClient localClient("127.0.0.1", std::atoi(argv[2]));
        localClient.run();
    } else {
        Rtype::udpClient localClient(argv[1], std::atoi(argv[2]));
        localClient.run();
    }
    return 0;
}

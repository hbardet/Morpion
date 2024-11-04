/*
** EPITECH PROJECT, 2024
** R-Type
** File description: Main of the Server
** main
*/

#include "udp_server.hpp"

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

int main(int argc, char* argv[])
{
    if (argc != 2 || !isValidPort(argv[1])) {
        std::cerr << "Usage: udp_server <port>\n";
        return 1;
    }
    try {
        Rtype::udpServer server(std::atoi(argv[1]));
        server.run();
    }
    catch (std::exception &error) {
        std::cerr << "Exception: " << error.what() << "\n";
    }
    return 0;
}

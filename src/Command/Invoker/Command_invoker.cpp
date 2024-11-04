/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_invoker
*/

#include "Command_invoker.hh"

Rtype::Command::Command_invoker::Command_invoker(std::string invoker_type):
    _invokerType(invoker_type), _commandQueue()
{
}

Rtype::Command::Command_invoker::~Command_invoker()
{
}

void Rtype::Command::Command_invoker::executeCommand()
{
    while (!_commandQueue.empty()) {
        if (_invokerType == "Server") {
            _commandQueue.front()->execute_server_side();
            _commandQueue.pop();
        } else if (_invokerType == "Client") {
            _commandQueue.front()->execute_client_side();
            _commandQueue.pop();
        } else
            std::cerr << "Wrong invoker type set. No commands executed." << std::endl;
    }

}

void Rtype::Command::Command_invoker::addCommand(std::unique_ptr<Rtype::Command::ACommand> cmd)
{
    cmd->setOrigins(_invokerType);
    _commandQueue.push(std::move(cmd));
}

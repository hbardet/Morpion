/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Network
*/

#pragma once

#include "../ParametersMap/ParametersMap.hpp"
#include "../../Command/Factory/Factory.hh"
#include "../../Command/Invoker/Command_invoker.hh"

#include <boost/asio.hpp>
#include <iostream>

namespace Rtype
{

    class Network {
        public:
            Network();
            Network(boost::asio::io_service &io_service, short port, std::string type);
            Network(boost::asio::io_context &io_context, const std::string &serverAddr, const int serverPort, std::string type);
            ~Network();

            void accAckToSend();
            void accAckToReceive();

            int getAckToSend();
            int getAckToReceive();

            void addCommandToInvoker(std::unique_ptr<Rtype::Command::ACommand> cmd);
            void executeInvoker();

            std::unique_ptr<Rtype::Command::ACommand> createCommand(uint8_t category, uint8_t index);

            std::shared_ptr<udp::socket> getSocket();

            void setSenderEndpoint(udp::endpoint endpoint);
            udp::endpoint getSenderEndpoint();

            template <typename T>
            std::unique_ptr<T> convertACommandToCommand(std::unique_ptr<Rtype::Command::ACommand> base) {
                static_assert(std::is_base_of<Rtype::Command::ACommand, T>::value);
                T* derived = dynamic_cast<T*>(base.get());

                if (derived) {
                    base.release();
                    return std::unique_ptr<T>(derived);
                } else
                    return nullptr;
        }
        protected:
        private:
            int _ackToSend;
            int _ackToReceive;
            std::shared_ptr<udp::socket> _socket;
            udp::endpoint _endpoint;
            Rtype::Command::Command_invoker _commandInvoker;
            Rtype::Command::Factory _commandFactory;
    };
} // namespace Rtype

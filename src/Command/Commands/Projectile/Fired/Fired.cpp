/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Fired
*/

#include "Fired.hh"

void Rtype::Command::Projectile::Fired::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int entityID, int projectileID)
{
    _players = players;
    _entityID = entityID;
    _projectileID = projectileID;
}

void Rtype::Command::Projectile::Fired::set_client()
{
}

Rtype::Command::Projectile::Fired::~Fired()
{
}

void Rtype::Command::Projectile::Fired::execute_client_side()
{
    sendToEndpoint(Utils::InfoTypeEnum::Projectile, Utils::ProjectileEnum::ProjectileFired);
}

void Rtype::Command::Projectile::Fired::execute_server_side()
{
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Projectile, Utils::ProjectileEnum::ProjectileFired, _entityID, _projectileID);
    }
}

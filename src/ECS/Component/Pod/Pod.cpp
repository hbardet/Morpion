#include "Pod.hh"

ECS::Components::Pod::Pod(std::size_t player):
    _player(player), _level(0), _isUp(false), _cooldown(50)
{}

std::size_t ECS::Components::Pod::getPlayer()
{
    return _player;
}

void ECS::Components::Pod::setPlayer(std::size_t player)
{
    _player = player;
}

int ECS::Components::Pod::getLevel()
{
    return _level;
}

void ECS::Components::Pod::setLevel(int level)
{
    _level = level;
}

bool ECS::Components::Pod::isUp()
{
    return _isUp;
}

void ECS::Components::Pod::setIsUp(bool isUp)
{
    _isUp = isUp;
}

int ECS::Components::Pod::getCooldown()
{
    return _cooldown;
}

void ECS::Components::Pod::setCooldown(int cooldown)
{
    _cooldown = cooldown;
}

/*
** EPITECH PROJECT, 2024
** R-Type - Components : Sound
** File description:
** Sound Component
*/

#include "Sound.hh"

ECS::Components::SoundEffect::SoundEffect(const std::string &filePath)
{
    _soundEffect = LoadSound(filePath.c_str());
}

void ECS::Components::SoundEffect::play()
{
    PlaySound(_soundEffect);
}

void ECS::Components::SoundEffect::stop()
{
    StopSound(_soundEffect);
}

void ECS::Components::SoundEffect::setVolume(float volume)
{
    _volume = volume;
    SetSoundVolume(_soundEffect, _volume);
}

float ECS::Components::SoundEffect::getVolume() const
{
    return _volume;
}

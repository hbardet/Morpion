/*
** EPITECH PROJECT, 2024
** R-Type - Components : Music
** File description:
** Music Component
*/

#include "Music.hh"

ECS::Components::Musica::Musica(const std::string &filePath):
    _isPaused(false), _volume(1.0f)
{
    _musicStream = LoadMusicStream(filePath.c_str());
}

void ECS::Components::Musica::play()
{
    PlayMusicStream(_musicStream);
}

void ECS::Components::Musica::playFrom(float startTime)
{
    SeekMusicStream(_musicStream, startTime);
    PlayMusicStream(_musicStream);
}

void ECS::Components::Musica::stop()
{
    StopMusicStream(_musicStream);
    UnloadMusicStream(_musicStream);
}

void ECS::Components::Musica::pause()
{
    PauseMusicStream(_musicStream);
    _isPaused = true;
}

void ECS::Components::Musica::resume()
{
    if (_isPaused) {
        ResumeMusicStream(_musicStream);
        _isPaused = false;
    }
}

void ECS::Components::Musica::update()
{
    UpdateMusicStream(_musicStream);
}

float ECS::Components::Musica::getTimePlayed() const
{
    return GetMusicTimePlayed(_musicStream) / GetMusicTimeLength(_musicStream);
}

void ECS::Components::Musica::setVolume(float volume)
{
    _volume = volume;
    SetMusicVolume(_musicStream, volume);
}

float ECS::Components::Musica::getVolume() const
{
    return _volume;
}

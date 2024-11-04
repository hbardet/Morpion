/*
** EPITECH PROJECT, 2024
** R-Type - Components : Render2D
** File description:
** Render2D Component
*/

#include "Render2D.hh"

ECS::Components::Render2D::Render2D(const std::string path):
    _color(WHITE), _path(path)
{
}

ECS::Components::Render2D::Render2D(const Render2D& other):
    _color(other._color),
    _path(other._path)
{
}

ECS::Components::Render2D& ECS::Components::Render2D::operator=(const Render2D& other)
{
    if (this != &other) {
        _color = other._color;
        _path = other._path;
    }
    return *this;
}


void ECS::Components::Render2D::render(raylib::Texture &texture, raylib::Vector3 position, raylib::Vector3 rotation, raylib::Vector3 scale)
{
    Vector2 pos = {position.GetX(), position.GetY()};

    texture.Draw(pos, rotation.GetZ(), scale.GetX(), _color);
}

const raylib::Color& ECS::Components::Render2D::getColor() const
{
    return _color;
}

void ECS::Components::Render2D::setColor(const raylib::Color& color)
{
    _color = color;
}

const std::string ECS::Components::Render2D::getPath() const
{
    return _path;
}

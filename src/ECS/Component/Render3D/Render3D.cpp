/*
** EPITECH PROJECT, 2024
** R-Type - Components : Render3D
** File description:
** Render3D Component
*/

#include "Render3D.hh"

ECS::Components::Render3D::Render3D(const std::string& path) : _color(WHITE), _path(path)
{
}

ECS::Components::Render3D::Render3D(const Render3D& other) :
    _color(other._color),
    _path(other._path)
{
}

ECS::Components::Render3D& ECS::Components::Render3D::operator=(const Render3D& other)
{
       if (this != &other) {
           _color = other._color;
           _path = other._path;
       }
       return *this;
   }

void ECS::Components::Render3D::render(raylib::Model &model, raylib::Vector3 position, raylib::Vector3 rotation, raylib::Vector3 scale)
{
    raylib::Matrix rotationMatrix = MatrixRotateXYZ(raylib::Vector3(
        rotation.x * DEG2RAD,
        rotation.y * DEG2RAD,
        rotation.z * DEG2RAD
    ));
    model.SetTransform(rotationMatrix);
    model.Draw(position, scale.x, _color);
}

void ECS::Components::Render3D::setPath(const std::string& path)
{
    _path = path;
}

const raylib::Color& ECS::Components::Render3D::getColor() const
{
    return _color;
}

void ECS::Components::Render3D::setColor(const raylib::Color& color)
{
    _color = color;
}

const std::string ECS::Components::Render3D::getPath() const
{
    return _path;
}

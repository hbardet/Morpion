/*
** EPITECH PROJECT, 2024
** R-Type - Components : Light
** File description:
** Light Component
*/
#include "Light.hh"

ECS::Components::Light::Light(const std::string& shader, int type, raylib::Vector3 position, raylib::Vector3 target, raylib::Color color)
    : _id(0),
      _type(static_cast<LightType>(type)),
      _position(position),
      _target(target),
      _color(color),
      _shader(shader),
      _enabled(true),
      _attenuation(0.0F),
      _enabledLoc(0),
      _typeLoc(0),
      _positionLoc(0),
      _targetLoc(0),
      _colorLoc(0),
      _attenuationLoc(0)
{
}

ECS::Components::Light::Light(const Light& other)
    : _id(other._id),
      _type(other._type),
      _position(other._position),
      _target(other._target),
      _color(other._color),
      _shader(other._shader),
      _enabled(other._enabled),
      _attenuation(other._attenuation),
      _enabledLoc(other._enabledLoc),
      _typeLoc(other._typeLoc),
      _positionLoc(other._positionLoc),
      _targetLoc(other._targetLoc),
      _colorLoc(other._colorLoc),
      _attenuationLoc(other._attenuationLoc)
{
}

ECS::Components::Light& ECS::Components::Light::operator=(const Light& other)
{
    if (this != &other) {
        _id = other._id;
        _type = other._type;
        _position = other._position;
        _target = other._target;
        _color = other._color;
        _shader = other._shader;
        _enabled = other._enabled;
        _attenuation = other._attenuation;
        _enabledLoc = other._enabledLoc;
        _typeLoc = other._typeLoc;
        _positionLoc = other._positionLoc;
        _targetLoc = other._targetLoc;
        _colorLoc = other._colorLoc;
        _attenuationLoc = other._attenuationLoc;
    }
    return *this;
}

void ECS::Components::Light::initLight(int idLight, raylib::Shader &shader)
{
    std::cout << "Init Light" << std::endl;
   _id = idLight;
   _enabledLoc = shader.GetLocation(TextFormat("lights[%i].enabled", idLight));
   _typeLoc = shader.GetLocation(TextFormat("lights[%i].type", idLight));
   _positionLoc = shader.GetLocation(TextFormat("lights[%i].position", idLight));
   _targetLoc = shader.GetLocation(TextFormat("lights[%i].target", idLight));
   _colorLoc = shader.GetLocation(TextFormat("lights[%i].color", idLight));
   update(shader);
}



void ECS::Components::Light::update(raylib::Shader &shader)
{
    shader.SetValue(_enabledLoc, &_enabled, SHADER_UNIFORM_INT);
    shader.SetValue(_typeLoc, &_type, SHADER_UNIFORM_INT);

    float position[3] = { _position.x, _position.y, _position.z };
    shader.SetValue(_positionLoc, position, SHADER_UNIFORM_VEC3);

    float target[3] = { _target.x, _target.y, _target.z };
    shader.SetValue(_targetLoc, target, SHADER_UNIFORM_VEC3);

    float color[4] = { (float)_color.r / 255.0f, (float)_color.g / 255.0f, (float)_color.b / 255.0f, (float)_color.a / 255.0f };
    shader.SetValue(_colorLoc, color, SHADER_UNIFORM_VEC4);
}

std::string ECS::Components::Light::getPath()
{
    return _shader;
}

void ECS::Components::Light::setPosition(raylib::Vector3 position)
{
    _position = position;
}

void ECS::Components::Light::setTarget(raylib::Vector3 target)
{
    _target = target;
}

void ECS::Components::Light::enable()
{
    _enabled = true;
}

void ECS::Components::Light::disable()
{
    _enabled = false;
}

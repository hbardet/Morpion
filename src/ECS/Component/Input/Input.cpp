/*
** EPITECH PROJECT, 2024
** R-Type - Components : Input
** File description:
** Input Component
*/
#include "Input.hh"

ECS::Components::Input::Input():
    _lastInputs(std::vector<std::size_t>())
{}

void ECS::Components::Input::setInputs(const std::vector<std::size_t> & inputs)
{
    _lastInputs = inputs;
}

std::vector<std::size_t> ECS::Components::Input::getInputs() const
{
    return _lastInputs;
}

bool ECS::Components::Input::contains(std::size_t toSearch)
{
    for (std::size_t i = 0; i < _lastInputs.size(); i++)
        if (_lastInputs[i] == toSearch)
            return true;
    return false;
}

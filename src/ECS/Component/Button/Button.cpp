/*
** EPITECH PROJECT, 2024
** R-Type - Components : Button
** File description:
** Button Component Implementation
*/

#include "Button.hh"


ECS::Components::Button::Button(const Rectangle &bounds, bool isSelected, std::function<void()> onClick)
            : _bounds(bounds), _originalBounds(bounds), _isSelected(false), _onClick(onClick)
{}

Rectangle ECS::Components::Button::getBounds() const
{
    return _bounds;
}

Rectangle ECS::Components::Button::getOriginalBounds() const
{
    return _originalBounds;
}

void ECS::Components::Button::setBounds(const Rectangle &bounds)
{
    _bounds = bounds;
}

void ECS::Components::Button::setOriginalBounds(const Rectangle &bounds)
{
    _originalBounds = bounds;
}

bool ECS::Components::Button::isSelected() const
{
    return _isSelected;
}

void ECS::Components::Button::setSelected(bool isSelected)
{
    _isSelected = isSelected;
}

void ECS::Components::Button::setOnClick(std::function<void()> onClick)
{
    _onClick = onClick;
}

void ECS::Components::Button::onClick() {
    if (_onClick)
        _onClick();
}

bool ECS::Components::Button::isMouseOver(int mouseX, int mouseY) const
{
    return (mouseX >= _bounds.x && mouseX <= (_bounds.x + _bounds.width) &&
            mouseY >= _bounds.y && mouseY <= (_bounds.y + _bounds.height));
}

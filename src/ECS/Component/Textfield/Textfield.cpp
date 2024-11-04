/*
** EPITECH PROJECT, 2024
** R-Type - Components : TextField
** File description:
** TextField Component
*/


#include "Textfield.hh"

ECS::Components::TextField::TextField(const Rectangle &bounds, bool isActive, const std::string &initialText,
int fontSize, Color color):
    _bounds(bounds), _isActive(isActive), _text(initialText), _onTextChange(nullptr)
{}

Rectangle ECS::Components::TextField::getBounds() const
{
    return _bounds;
}

std::string ECS::Components::TextField::getText() const
{
    return _text;
}

void ECS::Components::TextField::setText(const std::string &text) {
    _text = text;
    if (_onTextChange) {
        _onTextChange(_text);
    }
}

bool ECS::Components::TextField::isActive() const
{
    return _isActive;
}

void ECS::Components::TextField::setActive(bool isActive)
{
    _isActive = isActive;
}

void ECS::Components::TextField::onTextChange(std::function<void(const std::string&)> callback)
{
    _onTextChange = callback;
}

bool ECS::Components::TextField::isMouseOver(int mouseX, int mouseY) const
{
    return CheckCollisionPointRec({static_cast<float>(mouseX), static_cast<float>(mouseY)}, _bounds);
}

bool ECS::Components::TextField::canAddCharacter(char newChar, int fontSize) const {
    std::string testText = _text + newChar;
    int textWidth = MeasureText(testText.c_str(), fontSize);

    return textWidth < _bounds.width - 10;
}

int ECS::Components::TextField::getFontSize() const
{
    return _fontSize;
}

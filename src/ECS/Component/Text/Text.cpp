/*
** EPITECH PROJECT, 2024
** R-Type - Components : Text
** File description:
** Text Component
*/

#include "Text.hh"

/**
 * @brief Constructor of Text component.
 *
 * @tparam std::string text.
 * @return void.
 */
ECS::Components::Text::Text(std::string text, int fontSize, raylib::Color color):
    _text(text), _fontSize(fontSize), _color(color)
{}

/**
 * @brief Get the text of the component.
 *
 * @tparam void.
 * @return std::string.
*/
std::string ECS::Components::Text::getText() const
{
    return _text;
}

/**
 * @brief Set the text of the component.
 *
 * @tparam std::string text.
 * @return void.
 */
void ECS::Components::Text::setText(std::string text)
{
    _text = text;
}

/**
 * @brief Set the font size of the component.
 *
 * @tparam int fontSize.
 * @return void.
 */
void ECS::Components::Text::setFontSize(int fontSize)
{
    _fontSize = fontSize;
}

/**
 * @brief Get the font size of the component.
 *
 * @tparam void.
 * @return int.
 */
int ECS::Components::Text::getFontSize() const
{
    return _fontSize;
}

/**
 * @brief Set the color of the component.
 *
 * @tparam raylib::Color color.
 * @return void.
 */
void ECS::Components::Text::setColor(raylib::Color color)
{
    _color = color;
}

/**
 * @brief Get the color of the component.
 *
 * @tparam void.
 * @return raylib::Color.
 */
raylib::Color ECS::Components::Text::getColor() const
{
    return _color;
}

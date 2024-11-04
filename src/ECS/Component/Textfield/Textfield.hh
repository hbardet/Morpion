/*
** EPITECH PROJECT, 2024
** R-Type - Components : TextField
** File description:
** TextField Component
*/

#pragma once

#include <string>
#include <functional>
#include "raylib-cpp.hpp"

namespace ECS {
    namespace Components {

        class TextField {
        public:
            TextField(const Rectangle &bounds, bool isActive = false, const std::string &initialText = "", int fontSize = 20, Color color = RAYWHITE);
            ~TextField() = default;

            Rectangle getBounds() const;
            std::string getText() const;
            void setText(const std::string &text);

            bool isActive() const;
            void setActive(bool isActive);

            void onTextChange(std::function<void(const std::string&)> callback);

            bool isMouseOver(int mouseX, int mouseY) const;
            bool canAddCharacter(char newChar, int fontSize) const;
            int getFontSize() const;

        private:
            Rectangle _bounds;
            bool _isActive;
            std::string _text;
            std::function<void(const std::string&)> _onTextChange;
            int _fontSize;
            Color _color;

        };

    }
}

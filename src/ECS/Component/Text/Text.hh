/*
** EPITECH PROJECT, 2024
** R-Type - Components : Text
** File description:
** Text Component
*/
#pragma once

#include <iostream>
#if defined(_WIN32)           
	#define NOGDI
	#define NOUSER
#endif

#include "raylib-cpp.hpp"

#if defined(_WIN32)
	#undef near
	#undef far
#endif
namespace ECS {
    namespace Components {

        class Text {
        public:
            Text(std::string text, int fontSize, raylib::Color color);
            ~Text() = default;

            std::string getText() const;
            void setText(std::string text);
            void setFontSize(int size);
            int getFontSize() const;
            void setColor(raylib::Color color);
            raylib::Color getColor() const;

        protected:

        private:
            std::string _text;
            int _fontSize;
            raylib::Color _color;
        };
    }
}

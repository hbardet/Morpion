/*
** EPITECH PROJECT, 2024
** R-Type - Components : Button
** File description:
** Button Component
*/

#pragma once

#include <functional>

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

        class Button {
        public:
            Button(const Rectangle &bounds, bool isSelected = false, std::function<void()> onClick = nullptr);
            ~Button() = default;

            Rectangle getBounds() const;
            Rectangle getOriginalBounds() const;
            void setBounds(const Rectangle &bounds);
            void setOriginalBounds(const Rectangle &bounds);

            bool isSelected() const;
            void setSelected(bool isSelected);

            void setOnClick(std::function<void()> onClick);

            void onClick();
            bool isMouseOver(int mouseX, int mouseY) const;

        private:
            Rectangle _bounds;
            Rectangle _originalBounds;
            bool _isSelected;
            std::function<void()> _onClick;
        };

    }
}

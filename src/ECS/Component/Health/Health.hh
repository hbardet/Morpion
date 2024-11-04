/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Health {
        public:
            Health(int health, int invincibility = 0);
            ~Health() = default;

            int getHealth() const;
            void setHealth(int health);
            void modifyHealthBy(int delta);

            int getInvincibility() const;
            void setInvincibility(int invincibility);
            void modifyInvincibilityBy(int delta);
        private:
            int _health;
            int _invincibility;
        };
    }
}

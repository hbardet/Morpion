/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** It will handle game and state.
*/

#pragma once

#include "../../ECS/Core/Core.hpp"

#include "../../ECS/Entity/Button/Button.hh"

#include "../../ECS/Component/Health/Health.hh"
#include "../../ECS/Component/Position/Position.hpp"
#include "../../ECS/Component/Velocity/Velocity.hh"
#include "../../ECS/Component/Hitbox/Hitbox.hh"
#include "../../ECS/Component/Text/Text.hh"
#include "../../ECS/Component/Input/Input.hh"
#include "../../ECS/Component/Projectile/Projectile.hh"
#include "../../ECS/Component/Background/Background.hpp"
#include "../../ECS/Component/AI/AI.hh"
#include "../../ECS/Component/Button/Button.hh"
#include "../../ECS/Component/Light/Light.hh"
#include "../../ECS/Component/Music/Music.hh"
#include "../../ECS/Component/Sound/Sound.hh"
#include "../../ECS/Component/Textfield/Textfield.hh"
#include "../../ECS/Component/Pod/Pod.hh"

#include "../../ECS/System/SystemManager/SystemManager.hpp"

#include "../../ECS/System/Velocity/Velocity.hpp"
#include "../../ECS/System/Collision/Collision.hh"
#include "../../ECS/System/ProjectileCollision/ProjectileCollision.hh"
#include "../../ECS/System/InputUpdates/InputUpdates.hh"
#include "../../ECS/System/Render3D/Render3D.hh"
#include "../../ECS/System/Render2D/Render2D.hh"
#include "../../ECS/System/Background/Background.hh"
#include "../../ECS/System/UpdateVelocityAI/UpdateVelocityAI.hh"
#include "../../ECS/System/RenderText/RenderText.hh"
#include "../../ECS/System/RenderButton/RenderButton.hh"
#include "../../ECS/System/ButtonClick/ButtonClick.hh"
#include "../../ECS/System/GetDeadEntities/GetDeadEntities.hh"
#include "../../ECS/System/AIFiringProjectile/AIFiringProjectile.hh"
#include "../../ECS/System/TextfieldInput/TextfieldInput.hh"
#include "../../ECS/System/RenderTextfield/RenderTextfield.hh"

#include "../../Utils/enemiesTypeEnum.hpp"
#include "../../ECS/RessourcePool/RessourcePool.hh"

#include <cstdlib>
#include <thread>

#define CONVERT_ACMD_TO_CMD(TYPE, CMD_CATEGORY, CMD_INDEX)  _network->convertACommandToCommand<TYPE>(_network->createCommand(static_cast<uint8_t>(CMD_CATEGORY), static_cast<uint8_t>(CMD_INDEX)))

namespace Rtype {
    enum GameState {
        MENU,
        PLAY,
    };

    class Network;

    class Game {
    public:
        Game(std::shared_ptr<Rtype::Network> network, bool render);
        ~Game();

        void run();
        void runServer();
        void movePlayer(int id, double x, double y);
        void initGame(int id);

        bool getJoiningGame();
        void setIsJoiningGame(bool state);
        bool getIsAvailableGames();
        void setIsAvailableGames(bool state);

        std::vector<std::tuple<int, int, int>> getAvailableGames();
        void addAvailableGames(int game_id);
        void clearAvailableGames();
        void createPlayer(int id, float pos_x, float pos_y, int invincibility);
        void createOtherPlayer(int id, float pos_x, float pos_y);
        std::size_t createEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int health);
        std::size_t createEnemy(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int health);
        void createBoss(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int health);
        void movePlayer(int id, float x, float y);
        void setPlayerPos(int id, double x, double y);
        void failToConnect();
        void joinGame();
        void createProjectile(int entityId, int projectileId);
        void createPod(int entityId, float posX, float posY);
        void damageEntity(int entityId);
        void destroyEntity(int entityId);
        void setIsConnectedToServer(bool state);
        void setIsRunning(bool state);
        void equipPod(int playerId, int podId);

        std::vector<int> getAIProjectile();
        std::vector<int> getDamagedEntities();
        std::vector<int> getDeadEntities();

    private:
        std::size_t createCyclingEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y, float dest_x, float dest_y);
        void createEnemyProjectile(int entityId, int projectileId, enemiesTypeEnum_t projectileType);
        void createPlayerProjectile(int entityId, int projectileId);
        void createPodProjectile(int entityId, int projectileId);
        void loadMusic();
        void destroyProjectile(std::size_t entityID);
        void createBackgroundLayers(float speed, std::string modelPath, int numberOfPanel);
        void update();
        void updateMenu();
        void render();
        void renderMenu();
        void switchState(GameState newState);
        void initMenu();
        void initOptions();
        void joinRandomGame();
        void joinGameID();
        void initPlayOption();
        void initCreationGame();
        void destroyEntityMenu();
        void destroyEntityLayer();
        void destroyEntityText();
        void destroyMusic();
        void createMusic(std::string path, std::string name);
        void playMusic(std::string name);
        void stopMusic(std::string name);
        void playFromMusic(std::string name, float sec);
        void updateMusic(std::string name);
        void playSound(std::string name);
        void createSound(std::string path, std::string name);
        void updatePlayerCountText();
        void DrawProgressBar(int progress);
        void LoadAssets();
        std::vector<std::size_t> getAllInputs();
        void sendInput(std::vector<std::size_t> vec);
        void sendProjectile();
        void sendPods(std::size_t podId);
        void createBoss1(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int life);
        void createBoss2(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int life);

        std::map<std::string, ECS::Components::Musica> _musicMap;
        std::map<std::string, ECS::Components::SoundEffect> _soundMap;
        GameState _currentState;
        bool _isRunning;
        short _playerCount;
        short _selectedDifficulty;
        std::size_t _playerCountTextEntity;
        std::unique_ptr<ECS::Core::Core> _core;
        raylib::Window _window;
        raylib::Camera3D _camera;
        std::map<int, std::size_t> _serverToLocalPlayersId;
        std::map<int, std::size_t> _serverToLocalEnemiesId;
        std::map<int, std::size_t> _serverToLocalProjectilesId;
        std::map<int, std::size_t> _serverToLocalPodsId;
        std::map<std::string, std::size_t> _mapEntityMusic;
        ECS::RessourcePool _ressourcePool;
        std::vector<std::size_t> _boss2Balls;

        std::shared_ptr<Rtype::Network> _network;
        bool _isJoiningGame;
        bool _isAvailableGames;
        bool _isRendering;
        bool _modelCreated;
        bool _isConnectedToServer;
        std::vector<std::tuple<int, int, int>> _availableGames;
        std::vector<std::size_t> _projectilesToSend;
        std::vector<std::size_t> _deadEntities;
        std::vector<std::size_t> _damagedEntities;
        std::thread _localServer;
    };
};

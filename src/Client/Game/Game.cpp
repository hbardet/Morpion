/*
** EPITECH PROJECT, 2024
** R-Type - Game : Game
** File description:
** Game class is the main class to game.
** Implementation of the main game loop, window, and integration with ECS.
*/

#include "Game.hh"

#include "../../Utils/Network/Network.hpp"
#include <thread>
// #include<unistd.h>

std::size_t ECS::CTypeRegistry::nextTypeIndex = 0;
std::unordered_map<std::size_t, std::function<std::type_index()>> ECS::CTypeRegistry::indexToTypeMap;
int menuOption = 0;
std::vector<std::string> options = {"Start Game", "Options", "Quit"};

Rtype::Game::Game(std::shared_ptr<Rtype::Network> network, bool render)
    : _network(network), _isRunning(true), _playerCount(2), _selectedDifficulty(1), _currentState(MENU),
    _isJoiningGame(false), _isAvailableGames(false), _isRendering(render), _modelCreated(false), _isConnectedToServer(false)
{
    _core = std::make_unique<ECS::Core::Core>();

    if (render) {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        SetTargetFPS(60);
        _window.Init(1280, 720, "R-Type Game");
        SetWindowMinSize(1280, 720);
        _camera = raylib::Camera3D({ 0.0f, 10.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, 60.0f);
        _ressourcePool.addModel("enemy_one");
        _ressourcePool.addModel("turret");
        _ressourcePool.addModel("boss_two_part");
        _ressourcePool.addModel("bydo_shot");
        _ressourcePool.addModel("ship_yellow");
        _ressourcePool.addModel("boss_one");
        _ressourcePool.addModel("player_shot");
        _ressourcePool.addModel("boss_two");
        _ressourcePool.addModel("patapata");
        _ressourcePool.addModel("homing_shot");
        _ressourcePool.addModel("bink");
        _ressourcePool.addModel("boss_one_part");
        _ressourcePool.addModel("base_projectile");
        _ressourcePool.addModel("player");
        _ressourcePool.addModel("enemy_one");
        _ressourcePool.addTexture("bg_menu");
        _ressourcePool.addTexture("background");
        _ressourcePool.addTexture("background_layer0");
        _ressourcePool.addTexture("background_layer1");
        _ressourcePool.addTexture("background_layer2");
    }
    _core->registerComponent<ECS::Components::Position>();
    _core->registerComponent<ECS::Components::Rotate>();
    _core->registerComponent<ECS::Components::Scale>();
    _core->registerComponent<ECS::Components::Velocity>();
    _core->registerComponent<ECS::Components::Hitbox>();
    _core->registerComponent<ECS::Components::Input>();
    _core->registerComponent<ECS::Components::Render2D>();
    _core->registerComponent<ECS::Components::Render3D>();
    _core->registerComponent<ECS::Components::Projectile>();
    _core->registerComponent<ECS::Components::Background>();
    _core->registerComponent<ECS::Components::AI>();
    _core->registerComponent<ECS::Components::Text>();
    _core->registerComponent<ECS::Components::Button>();
    _core->registerComponent<ECS::Components::Health>();
    _core->registerComponent<ECS::Components::Musica>();
    _core->registerComponent<ECS::Components::SoundEffect>();
    _core->registerComponent<ECS::Components::TextField>();
    _core->registerComponent<ECS::Components::Pod>();

    _core->registerSystem<ECS::Systems::SystemVelocity>();
    _core->registerSystem<ECS::Systems::Collision>();
    _core->registerSystem<ECS::Systems::ProjectileCollision>();
    _core->registerSystem<ECS::Systems::InputUpdates>();
    _core->registerSystem<ECS::Systems::SystemRender2D>();
    _core->registerSystem<ECS::Systems::SystemRender3D>();
    _core->registerSystem<ECS::Systems::SystemBackground>();
    _core->registerSystem<ECS::Systems::UpdateVelocityAI>();
    _core->registerSystem<ECS::Systems::RenderTextSystem>();
    _core->registerSystem<ECS::Systems::RenderButtonSystem>();
    _core->registerSystem<ECS::Systems::ButtonClickSystem>();
    _core->registerSystem<ECS::Systems::GetDeadEntities>();
    _core->registerSystem<ECS::Systems::AIFiringProjectile>();
    _core->registerSystem<ECS::Systems::TextFieldInputSystem>();
    _core->registerSystem<ECS::Systems::RenderTextFieldSystem>();

    Signature velocitySystemSignature;
    velocitySystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    velocitySystemSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Velocity>());
    _core->setSystemSignature<ECS::Systems::SystemVelocity>(velocitySystemSignature);

    Signature collisionSignature;
    collisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    collisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Hitbox>());
    collisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::AI>());
    _core->setSystemSignature<ECS::Systems::Collision>(collisionSignature);

    Signature projectileCollisionSignature;
    projectileCollisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    projectileCollisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Hitbox>());
    projectileCollisionSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Projectile>());
    _core->setSystemSignature<ECS::Systems::ProjectileCollision>(projectileCollisionSignature);

    Signature inputUpdatesSignature;
    inputUpdatesSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Input>());
    _core->setSystemSignature<ECS::Systems::InputUpdates>(inputUpdatesSignature);

    Signature renderSignature3D;
    renderSignature3D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderSignature3D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Rotate>());
    renderSignature3D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Scale>());
    renderSignature3D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Render3D>());
    _core->setSystemSignature<ECS::Systems::SystemRender3D>(renderSignature3D);

    Signature renderSignature2D;
    renderSignature2D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderSignature2D.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Render2D>());
    _core->setSystemSignature<ECS::Systems::SystemRender2D>(renderSignature2D);

    Signature backgroundSignature;
    backgroundSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    backgroundSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Background>());
    _core->setSystemSignature<ECS::Systems::SystemBackground>(backgroundSignature);

    Signature updateVelocityAISignature;
    updateVelocityAISignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Velocity>());
    updateVelocityAISignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::AI>());
    _core->setSystemSignature<ECS::Systems::UpdateVelocityAI>(updateVelocityAISignature);

    Signature renderTextSignature;
    renderTextSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderTextSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Text>());
    _core->setSystemSignature<ECS::Systems::RenderTextSystem>(renderTextSignature);

    Signature renderButtonSignature;
    renderButtonSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderButtonSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Button>());
    _core->setSystemSignature<ECS::Systems::RenderButtonSystem>(renderButtonSignature);

    Signature buttonClickSignature;
    buttonClickSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    buttonClickSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Button>());
    _core->setSystemSignature<ECS::Systems::ButtonClickSystem>(buttonClickSignature);

    Signature getDeadEntitiesSignature;
    getDeadEntitiesSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Health>());
    getDeadEntitiesSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::AI>());
    _core->setSystemSignature<ECS::Systems::GetDeadEntities>(getDeadEntitiesSignature);

    Signature AIFiringProjectileSignature;
    AIFiringProjectileSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    AIFiringProjectileSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::AI>());
    _core->setSystemSignature<ECS::Systems::AIFiringProjectile>(AIFiringProjectileSignature);

    Signature textFieldInputSignature;
    textFieldInputSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::TextField>());
    _core->setSystemSignature<ECS::Systems::TextFieldInputSystem>(textFieldInputSignature);

    Signature renderTextFieldSignature;
    renderTextFieldSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Position>());
    renderTextFieldSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::TextField>());
    renderTextFieldSignature.set(
        ECS::CTypeRegistry::getTypeId<ECS::Components::Text>());
    _core->setSystemSignature<ECS::Systems::RenderTextFieldSystem>(renderTextFieldSignature);
}

void Rtype::Game::loadMusic()
{
    InitAudioDevice();
    createMusic("./resources/stage1/stage1.mp3", "stage1");
    createMusic("./resources/menuMusic/menuMusic.mp3", "menu");
    createSound("./resources/blasterLego/blasterLego.mp3", "blasterLego");
    createSound("./resources/breakLego/breakLego.mp3", "breakLego");
}

Rtype::Game::~Game()
{
    _ressourcePool.UnloadAll();
    _boss2Balls.clear();

    if (_localServer.joinable())
        _localServer.join();
}

void Rtype::Game::createBoss(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int life)
{
    switch (enemyType) {
        case enemiesTypeEnum_t::BOSS1_Core:
            createBoss1(entityId, enemyType, pos_x, pos_y, life);
            break;
        case enemiesTypeEnum_t::BOSS2_Core:
            createBoss2(entityId, enemyType, pos_x, pos_y, life);
            break;
        default:
            std::cerr << "Boss not recognized in createBoss method." << std::endl;
            break;
    }
}


std::size_t Rtype::Game::createEnemy(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int life)
{
    std::size_t enemy = _core->createEntity();

    if (_isRendering) {
        std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("enemy_one"));
        _core->addComponent(enemy, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
        _core->addComponent(enemy, ECS::Components::Render3D{"enemy_one"});
    }
    _core->addComponent(enemy, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(enemy, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Scale{1.0f});
    _core->addComponent(enemy, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::AI{enemyType});
    _core->addComponent(enemy, ECS::Components::Health{life});
    _serverToLocalEnemiesId[entityId] = enemy;
    return enemy;
}

std::size_t Rtype::Game::createEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int life)
{
    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("enemy_one"));
    std::size_t enemy = _core->createEntity();
    _core->addComponent(enemy, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(enemy, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Scale{1.0f});
    _core->addComponent(enemy, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(enemy, ECS::Components::Render3D{"enemy_one"});
    _core->addComponent(enemy, ECS::Components::AI{enemyType});
    _core->addComponent(enemy, ECS::Components::Health{life});
    _serverToLocalEnemiesId[enemy] = enemy;
    return enemy;
}

std::size_t Rtype::Game::createCyclingEnemy(enemiesTypeEnum_t enemyType, float pos_x, float pos_y, float dest_x, float dest_y)
{
    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("enemy_one"));
    std::size_t enemy = _core->createEntity();
    _core->addComponent(enemy, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(enemy, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Scale{1.0f});
    _core->addComponent(enemy, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(enemy, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(enemy, ECS::Components::Render3D{"boss_one_part"});
    _core->addComponent(enemy, ECS::Components::AI{enemyType, std::make_pair(pos_x, pos_y), std::make_pair(dest_x, dest_y)});
    _serverToLocalEnemiesId[enemy] = enemy;
    return enemy;
}

void Rtype::Game::movePlayer(int id, double x, double y)
{
    auto &velocity = _core->getComponent<ECS::Components::Velocity>(_serverToLocalPlayersId[id]);

    velocity.setX(x);
    velocity.setY(y);
}

void Rtype::Game::setPlayerPos(int id, double x, double y)
{
    auto &position = _core->getComponent<ECS::Components::Position>(_serverToLocalPlayersId[id]);

    position.setX(x);
    position.setY(y);
}

void Rtype::Game::createPlayer(int id, float pos_x, float pos_y, int invincibility)
{
    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("ship_yellow"));
    std::size_t player = _core->createEntity();

    _core->addComponent(player, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(player, ECS::Components::Rotate{-90.0f, 0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Scale{1.0f});
    _core->addComponent(player, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(player, ECS::Components::Input{});
    _core->addComponent(player, ECS::Components::Health{5, -1// invincibility
        });
    _core->addComponent(player, ECS::Components::Render3D{"ship_yellow"});
    _serverToLocalPlayersId[id] = player;

    std::size_t boss = _core->createEntity();
    _core->addComponent(boss, ECS::Components::Position{8.0f, 2.0f, -1.0f});
    _core->addComponent(boss, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(boss, ECS::Components::Scale{1.0f});
    _core->addComponent(boss, ECS::Components::Render3D{"boss_one"});
}

void Rtype::Game::createOtherPlayer(int id, float pos_x, float pos_y)
{
    std::size_t otherPlayer = _core->createEntity();

    if (_isRendering) {
        std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("ship_yellow"));
        _core->addComponent(otherPlayer, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
        _core->addComponent(otherPlayer, ECS::Components::Render3D{"ship_yellow"});
    }

    _core->addComponent(otherPlayer, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(otherPlayer, ECS::Components::Rotate{-90.0f, 0.0f, 0.0f});
    _core->addComponent(otherPlayer, ECS::Components::Scale{1.0f});
    _core->addComponent(otherPlayer, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(otherPlayer, ECS::Components::Health{1, -1});
    _serverToLocalPlayersId[id] = otherPlayer;
}

void Rtype::Game::destroyEntityMenu(void)
{
    std::vector<std::size_t> entitiesMenu = _core->getEntitiesWithComponent<ECS::Components::Button>();

    for (auto &entity : entitiesMenu)
        _core->destroyEntity(entity);
}

void Rtype::Game::destroyEntityLayer(void)
{
    std::vector<std::size_t> entitiesLayer = _core->getEntitiesWithComponent<ECS::Components::Background>();

    for (auto &entity : entitiesLayer)
        _core->destroyEntity(entity);
}

void Rtype::Game::destroyMusic()
{
    std::vector<std::size_t> entitiesMusic = _core->getEntitiesWithComponent<ECS::Components::Musica>();

    for (auto &entity : entitiesMusic)
        _core->destroyEntity(entity);
}

void Rtype::Game::destroyEntityText(void)
{
    std::vector<std::size_t> entitiesText = _core->getEntitiesWithComponent<ECS::Components::Text>();

    for (auto &entity : entitiesText)
        _core->destroyEntity(entity);
}

void Rtype::Game::initOptions(void)
{
    destroyEntityMenu();
    destroyEntityLayer();

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 200});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 190, 300, 60}, true, [this]() {
        initMenu();
    }});

    std::size_t musicIncrease = _core->createEntity();
    _core->addComponent(musicIncrease, ECS::Components::Position{400, 300});
    _core->addComponent(musicIncrease, ECS::Components::Text{"Music +", 30, RAYWHITE});
    _core->addComponent(musicIncrease, ECS::Components::Button{Rectangle{350, 290, 300, 60}, true, [this]() {
        std::vector<std::size_t> entitiesMusic = _core->getEntitiesWithComponent<ECS::Components::Musica>();
        for (auto &entity : entitiesMusic) {
            auto &musicComponent = _core->getComponent<ECS::Components::Musica>(entity);
            float newVolume = std::min(musicComponent.getVolume() + 0.1f, 1.0f);
            musicComponent.setVolume(newVolume);
        }
    }});

    std::size_t musicDecrease = _core->createEntity();
    _core->addComponent(musicDecrease, ECS::Components::Position{400, 400});
    _core->addComponent(musicDecrease, ECS::Components::Text{"Music -", 30, RAYWHITE});
    _core->addComponent(musicDecrease, ECS::Components::Button{Rectangle{350, 390, 300, 60}, true, [this]() {
        std::vector<std::size_t> entitiesMusic = _core->getEntitiesWithComponent<ECS::Components::Musica>();
        for (auto &entity : entitiesMusic) {
            auto &musicComponent = _core->getComponent<ECS::Components::Musica>(entity);
            float newVolume = std::max(musicComponent.getVolume() - 0.1f, 0.0f);
            musicComponent.setVolume(newVolume);
        }
    }});

    std::size_t soundEffectIncrease = _core->createEntity();
    _core->addComponent(soundEffectIncrease, ECS::Components::Position{400, 500});
    _core->addComponent(soundEffectIncrease, ECS::Components::Text{"Sound Effect +", 30, RAYWHITE});
    _core->addComponent(soundEffectIncrease, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        std::vector<std::size_t> entitiesSoundEffect = _core->getEntitiesWithComponent<ECS::Components::SoundEffect>();
        for (auto &entity : entitiesSoundEffect) {
            auto &soundEffectComponent = _core->getComponent<ECS::Components::SoundEffect>(entity);
            float newVolume = std::min(soundEffectComponent.getVolume() + 0.1f, 1.0f);
            soundEffectComponent.setVolume(newVolume);
        }
    }});

    std::size_t soundEffectDecrease = _core->createEntity();
    _core->addComponent(soundEffectDecrease, ECS::Components::Position{400, 600});
    _core->addComponent(soundEffectDecrease, ECS::Components::Text{"Sound Effect -", 30, RAYWHITE});
    _core->addComponent(soundEffectDecrease, ECS::Components::Button{Rectangle{350, 590, 300, 60}, true, [this]() {
        std::vector<std::size_t> entitiesSoundEffect = _core->getEntitiesWithComponent<ECS::Components::SoundEffect>();
        for (auto &entity : entitiesSoundEffect) {
            auto &soundEffectComponent = _core->getComponent<ECS::Components::SoundEffect>(entity);
            float newVolume = std::max(soundEffectComponent.getVolume() - 0.1f, 0.0f);
            soundEffectComponent.setVolume(newVolume);
        }
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::joinGame()
{
    destroyEntityMenu();
    destroyEntityLayer();
    float yOffset = 200.0f;
    short buttonCount = 0;

    for (const auto &game : _availableGames) {
        if (buttonCount >= 5)
            break;
        int gameID = std::get<0>(game);
        int currentPlayerCount = std::get<1>(game);
        int maxPlayerCount = std::get<2>(game);

        std::size_t gameButton = _core->createEntity();

        _core->addComponent(gameButton, ECS::Components::Position{400, yOffset});

        std::string buttonText = "Game " + std::to_string(gameID) + " [" +
                                std::to_string(currentPlayerCount) + "/" +
                                 std::to_string(maxPlayerCount) + "]";
        _core->addComponent(gameButton, ECS::Components::Text{buttonText, 20, RAYWHITE});

        _core->addComponent(gameButton, ECS::Components::Button{Rectangle{350, yOffset - 10, 300, 40}, true, [this, gameID]() {
            std::unique_ptr<Rtype::Command::GameInfo::Join_game> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Join_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame);
            cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            cmd->set_client(gameID);
            _network->addCommandToInvoker(std::move(cmd));
            std::cout << "Joining game with ID: " << gameID << std::endl;
        }});

        yOffset += 60.0f;
        buttonCount++;
    }

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 500});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        initPlayOption();
    }});
    for (auto available_game: _availableGames)
        std::cout << "Game available: " << std::get<0>(available_game) << std::endl;
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::failToConnect()
{
    std::cout << "There is no room available with this ID." << std::endl;
}

void Rtype::Game::setIsConnectedToServer(bool state)
{
    _isConnectedToServer = state;
}

void Rtype::Game::setIsRunning(bool state)
{
    _isRunning = state;
}


void Rtype::Game::joinGameID(void)
{
    destroyEntityMenu();
    destroyEntityLayer();
    destroyEntityText();

    std::size_t textFieldEntity = _core->createEntity();
    _core->addComponent(textFieldEntity, ECS::Components::Position{400, 200});
    _core->addComponent(textFieldEntity, ECS::Components::Text{"", 30, RAYWHITE});

    ECS::Components::TextField textField(Rectangle{350, 190, 300, 60}, true, "");
    textField.onTextChange([this, textFieldEntity](const std::string &newText) {
        auto &text = _core->getComponent<ECS::Components::Text>(textFieldEntity);
        text.setText(newText);
    });
    _core->addComponent(textFieldEntity, std::move(textField));

    std::size_t joinButton = _core->createEntity();
    _core->addComponent(joinButton, ECS::Components::Position{400, 300});
    _core->addComponent(joinButton, ECS::Components::Text{"Join", 30, RAYWHITE});
    _core->addComponent(joinButton, ECS::Components::Button{Rectangle{350, 290, 300, 60}, true, [this, textFieldEntity]() {
        auto &textField = _core->getComponent<ECS::Components::TextField>(textFieldEntity);
        std::string friendGameID = textField.getText();

        if (!friendGameID.empty() && friendGameID.size() == 4 && std::all_of(friendGameID.begin(), friendGameID.end(), ::isdigit)) {
            std::unique_ptr<Rtype::Command::GameInfo::Join_game> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Join_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame);
            cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            cmd->set_client(std::stoi(friendGameID));
            _network->addCommandToInvoker(std::move(cmd));
            std::cout << "Joining game with ID: " << friendGameID << std::endl;
        } else if (friendGameID.empty() || friendGameID.size() != 4 || !std::all_of(friendGameID.begin(), friendGameID.end(), ::isdigit)) {
            std::cout << "A game ID can't be empty and is only a number of 4 digits only." << friendGameID << std::endl;
        }
    }});

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 500});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        initPlayOption();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::joinRandomGame(void)
{
    destroyEntityMenu();
    destroyEntityLayer();

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 200});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 190, 300, 60}, true, [this]() {
        initPlayOption();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::updatePlayerCountText(void)
{
    auto &textComponent = _core->getComponent<ECS::Components::Text>(_playerCountTextEntity);
    textComponent.setText(std::to_string(_playerCount));
}

void Rtype::Game::initCreationGame(void)
{
    destroyEntityMenu();
    destroyEntityLayer();

    _playerCount = 2;
    std::size_t easyButtonEntity = _core->createEntity();
    _core->addComponent(easyButtonEntity, ECS::Components::Position{100, 200});
    _core->addComponent(easyButtonEntity, ECS::Components::Text{"Facile", 20, RAYWHITE});
    _core->addComponent(easyButtonEntity, ECS::Components::Button{Rectangle{100, 190, 300, 60}, true, [this]() {
        _selectedDifficulty = 0;
    }});

    std::size_t normalButtonEntity = _core->createEntity();
    _core->addComponent(normalButtonEntity, ECS::Components::Position{100, 250});
    _core->addComponent(normalButtonEntity, ECS::Components::Text{"Normal", 20, RAYWHITE});
    _core->addComponent(normalButtonEntity, ECS::Components::Button{Rectangle{100, 240, 300, 60}, true, [this]() {
        _selectedDifficulty = 1;
    }});

    std::size_t hardButtonEntity = _core->createEntity();
    _core->addComponent(hardButtonEntity, ECS::Components::Position{100, 300});
    _core->addComponent(hardButtonEntity, ECS::Components::Text{"Difficile", 20, RAYWHITE});
    _core->addComponent(hardButtonEntity, ECS::Components::Button{Rectangle{100, 290, 300, 60}, true, [this]() {
        _selectedDifficulty = 2;
    }});

    std::size_t decreaseButtonEntity = _core->createEntity();
    _core->addComponent(decreaseButtonEntity, ECS::Components::Position{400, 400});
    _core->addComponent(decreaseButtonEntity, ECS::Components::Text{"-", 30, RAYWHITE});
    _core->addComponent(decreaseButtonEntity, ECS::Components::Button{Rectangle{370, 390, 60, 60}, true, [this]() {
        if (_playerCount > 1) {
            _playerCount--;
            updatePlayerCountText();
        }
    }});

    std::size_t playerCountTextEntity = _core->createEntity();
    _playerCountTextEntity = playerCountTextEntity;
    _core->addComponent(playerCountTextEntity, ECS::Components::Position{460, 400});
    _core->addComponent(playerCountTextEntity, ECS::Components::Text{std::to_string(_playerCount), 30, RAYWHITE});

    std::size_t increaseButtonEntity = _core->createEntity();
    _core->addComponent(increaseButtonEntity, ECS::Components::Position{520, 400});
    _core->addComponent(increaseButtonEntity, ECS::Components::Text{"+", 30, RAYWHITE});
    _core->addComponent(increaseButtonEntity, ECS::Components::Button{Rectangle{510, 390, 60, 60}, true, [this]() {
        if (_playerCount < 6) {
            _playerCount++;
            updatePlayerCountText();
        }
    }});

    std::size_t createButtonEntity = _core->createEntity();
    _core->addComponent(createButtonEntity, ECS::Components::Position{400, 500});
    _core->addComponent(createButtonEntity, ECS::Components::Text{"Create Game", 30, RAYWHITE});
    _core->addComponent(createButtonEntity, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        if (!_isConnectedToServer) {
            if (system("ls | grep -q r-type_server") == 0 && !_localServer.joinable()) {
                _network->setSenderEndpoint(udp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 2442)); //! Tmp get available port
                int port = static_cast<int>(_network->getSenderEndpoint().port());

                CONSOLE_INFO("A local server is now set.\nTo access to the server your local address is used (127.0.0.1) on the port ", port);
                _localServer = std::thread([this, port]() {
                    std::string cmd("./r-type_server " + std::to_string(port));

                    system(cmd.c_str());
                });

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd_connection = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_connection, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);
                cmd_connection->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
                _network->addCommandToInvoker(std::move(cmd_connection));
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        if (_isConnectedToServer) {
            std::unique_ptr<Rtype::Command::GameInfo::Create_game> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Create_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::CreateGame);

            cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            cmd->set_client();
            _network->addCommandToInvoker(std::move(cmd));
            CONSOLE_INFO("Create game: ", " Sended")
        }
    }});

    std::size_t back = _core->createEntity();
    _core->addComponent(back, ECS::Components::Position{400, 600});
    _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
    _core->addComponent(back, ECS::Components::Button{Rectangle{350, 590, 300, 60}, true, [this]() {
        initPlayOption();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::initPlayOption(void)
{
    destroyEntityMenu();
    destroyEntityLayer();
    destroyEntityText();

    std::size_t createGame = _core->createEntity();
    _core->addComponent(createGame, ECS::Components::Position{400, 200});
    _core->addComponent(createGame, ECS::Components::Text{"Create Game", 30, RAYWHITE});
    _core->addComponent(createGame, ECS::Components::Button{Rectangle{350, 190, 300, 60}, true, [this]() {
        initCreationGame();
    }});

    std::size_t joinRandomGameEntity = _core->createEntity();
    _core->addComponent(joinRandomGameEntity, ECS::Components::Position{400, 300});
    _core->addComponent(joinRandomGameEntity, ECS::Components::Text{"Join Game", 30, RAYWHITE});
    _core->addComponent(joinRandomGameEntity, ECS::Components::Button{Rectangle{350, 290, 300, 60}, true, [this]() {
        CONSOLE_INFO("Join game", "")
        _isAvailableGames = false;
        _isJoiningGame = true;
        std::unique_ptr<Rtype::Command::GameInfo::Games_available> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Games_available, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable);
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
        cmd->set_client();
        _network->addCommandToInvoker(std::move(cmd));
        joinRandomGame();
    }});

    std::size_t joinGameEntity = _core->createEntity();
    _core->addComponent(joinGameEntity, ECS::Components::Position{400, 400});
    _core->addComponent(joinGameEntity, ECS::Components::Text{"Search available game", 30, RAYWHITE});
    _core->addComponent(joinGameEntity, ECS::Components::Button{Rectangle{350, 390, 300, 60}, true, [this]() {
        CONSOLE_INFO("Get available game", "")
        _isJoiningGame = false;
        _isAvailableGames = true;
        clearAvailableGames();
        std::unique_ptr<Rtype::Command::GameInfo::Games_available> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Games_available, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable);
        cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
        cmd->set_client();
        _network->addCommandToInvoker(std::move(cmd));
    }});

    std::size_t joinGameId = _core->createEntity();
    _core->addComponent(joinGameId, ECS::Components::Position{400, 500});
    _core->addComponent(joinGameId, ECS::Components::Text{"Join friends game", 30, RAYWHITE});
    _core->addComponent(joinGameId, ECS::Components::Button{Rectangle{350, 490, 300, 60}, true, [this]() {
        CONSOLE_INFO("Join Game by ID", "")
        joinGameID();
    }});

    std::size_t back = _core->createEntity();
        _core->addComponent(back, ECS::Components::Position{400, 600});
        _core->addComponent(back, ECS::Components::Text{"Back", 30, RAYWHITE});
        _core->addComponent(back, ECS::Components::Button{Rectangle{350, 590, 300, 60}, true, [this]() {
        initMenu();
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

void Rtype::Game::initMenu(void)
{
    destroyEntityMenu();
    destroyEntityLayer();
    playMusic("menu");

    std::size_t startGameButton = _core->createEntity();
    _core->addComponent(startGameButton, ECS::Components::Position{400, 200});
    _core->addComponent(startGameButton, ECS::Components::Text{"Play", 30, RAYWHITE});
    _core->addComponent(startGameButton, ECS::Components::Button{Rectangle{350, 190, 300, 60}, true, [this]() {
        initPlayOption();
    }});

    std::size_t option = _core->createEntity();
    _core->addComponent(option, ECS::Components::Position{400, 300});
    _core->addComponent(option, ECS::Components::Text{"Option", 30, RAYWHITE});
    _core->addComponent(option, ECS::Components::Button{Rectangle{350, 290, 300, 60}, true, [this]() {
        initOptions();
    }});

    std::size_t quitButton = _core->createEntity();
    _core->addComponent(quitButton, ECS::Components::Position{400, 400});
    _core->addComponent(quitButton, ECS::Components::Text{"Quit", 30, RAYWHITE});
    _core->addComponent(quitButton, ECS::Components::Button{Rectangle{350, 390, 300, 60}, true, [this]() {
        _isRunning = false;
    }});
    createBackgroundLayers(0.f, "bg_menu", 1);
}

std::vector<int> Rtype::Game::getAIProjectile()
{
    std::vector<int> serverProjectile;

    serverProjectile.insert(serverProjectile.end(), _projectilesToSend.begin(), _projectilesToSend.end());
    _projectilesToSend.clear();
    for (std::size_t i; i < serverProjectile.size(); i++) {
        for (const auto& Ids : _serverToLocalEnemiesId)
            if (Ids.second == serverProjectile[i]) {
                serverProjectile[i] = Ids.first;
            }
        for (const auto& Ids : _serverToLocalPodsId)
            if (Ids.second == serverProjectile[i]) {
                serverProjectile[i] = Ids.first;
            }
    }
    // for (int i = 0; i < serverProjectile.size(); i++) {
    //     std::cout << "serverId[" << i << "]:" << serverProjectile[i];
    //     std::cout << "==> localId[" << i << "]:" << _serverToLocalEnemiesId[serverProjectile[i]] << std::endl;
    // }
    return serverProjectile;
}

std::vector<int> Rtype::Game::getDamagedEntities()
{
    std::vector<int> serverDamagedEntities;

    serverDamagedEntities.insert(serverDamagedEntities.end(), _damagedEntities.begin(), _damagedEntities.end());
    for (std::size_t i; i < serverDamagedEntities.size(); i++)
        for (const auto& Ids : _serverToLocalPlayersId)
            if (Ids.second == serverDamagedEntities[i])
                serverDamagedEntities[i] = Ids.first;
    _damagedEntities.clear();
    return serverDamagedEntities;
}

std::vector<int> Rtype::Game::getDeadEntities()
{
    std::vector<int> serverDeadEntities;

    serverDeadEntities.insert(serverDeadEntities.end(), _deadEntities.begin(), _deadEntities.end());
    for (std::size_t i; i < serverDeadEntities.size(); i++) {
        for (const auto& Ids : _serverToLocalPlayersId)
            if (Ids.second == serverDeadEntities[i])
                serverDeadEntities[i] = Ids.first;
        for (const auto& Ids : _serverToLocalEnemiesId)
            if (Ids.second == serverDeadEntities[i])
                serverDeadEntities[i] = Ids.first;
        for (const auto& Ids : _serverToLocalProjectilesId)
            if (Ids.second == serverDeadEntities[i])
                serverDeadEntities[i] = Ids.first;
    }
    //for (int i = 0; i < serverDeadEntities.size(); i++)
        //std::cout << "serverDeadEntities[" << i << "] :" << serverDeadEntities[i] << std::endl;
    _deadEntities.clear();
    return serverDeadEntities;
}

void Rtype::Game::createBoss1(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int life)
{
    createEnemy(entityId, BOSS1_Core, pos_x, pos_y, life);
    createCyclingEnemy(BOSS1_Tail0, 6.0f, 3.0f, 6.05f, 2.95f);
    createCyclingEnemy(BOSS1_Tail1, 5.5f, 2.8f, 6.1f, 2.7f);
    createCyclingEnemy(BOSS1_Tail2, 5.1f, 2.5f, 5.8f, 2.4f);
    createCyclingEnemy(BOSS1_Tail3, 4.7f, 2.9f, 6.2f, 2.1f);
    createCyclingEnemy(BOSS1_Tail4, 4.2f, 2.8f, 6.0f, 1.8f);
    createCyclingEnemy(BOSS1_Tail5, 3.8f, 3.1f, 6.1f, 1.5f);
    createCyclingEnemy(BOSS1_Tail6, 3.3f, 3.0f, 5.9f, 1.2f);
    createCyclingEnemy(BOSS1_Tail7, 2.9f, 2.7f, 5.8f, 0.9f);
    createCyclingEnemy(BOSS1_Tail8, 2.5f, 3.1f, 6.1f, 0.6f);
    createCyclingEnemy(BOSS1_Tail9, 2.0f, 3.0f, 6.0f, 0.3f);
    createCyclingEnemy(BOSS1_Tail10, 1.6f, 2.6f, 6.2f, 0.0f);
    createCyclingEnemy(BOSS1_Tail11, 1.2f, 2.9f, 5.9f, -0.3f);
    createCyclingEnemy(BOSS1_Tail12, 0.8f, 3.1f, 5.7f, -0.6f);
    createCyclingEnemy(BOSS1_Tail13, 0.3f, 3.0f, 6.0f, -0.9f);
    createCyclingEnemy(BOSS1_Tail14, -0.1f, 3.2f, 6.1f, -1.2f);
    createCyclingEnemy(BOSS1_Tail15, -0.5f, 2.9f, 5.9f, -1.5f);
    createCyclingEnemy(BOSS1_Tail16, -0.9f, 2.7f, 5.7f, -1.8f);
    createCyclingEnemy(BOSS1_Tail17, -1.4f, 3.0f, 6.0f, -2.1f);
    createCyclingEnemy(BOSS1_Tail18, -1.9f, 3.1f, 5.9f, -2.4f);
    createCyclingEnemy(BOSS1_Tail19, -2.4f, 2.9f, 6.2f, -2.7f);
}

void Rtype::Game::createBoss2(int entityId, enemiesTypeEnum_t enemyType, float pos_x, float pos_y, int life)
{
    float bossCoreX = pos_x;
    float bossCoreY = pos_y;

    createEnemy(entityId, BOSS2_Core, bossCoreX, bossCoreY, life);
    _boss2Balls.push_back(createEnemy(BOSS2_Ball0, bossCoreX - 0.2, bossCoreY - 0.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball1, bossCoreX + 0.3, bossCoreY - 0.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball2, bossCoreX + 0.8, bossCoreY -0.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball3, bossCoreX + 0.8, bossCoreY + 0.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball4, bossCoreX + 0.8, bossCoreY + 0.8, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball5, bossCoreX + 0.3, bossCoreY + 0.8, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball6, bossCoreX - 0.2, bossCoreY + 0.8, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball7, bossCoreX - 0.2, bossCoreY + 0.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball8, bossCoreX + 0.3, bossCoreY + 0.3, 1));

    _boss2Balls.push_back(createEnemy(BOSS2_Ball9, bossCoreX - 0.7, bossCoreY - 0.7, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball10, bossCoreX -0.2, bossCoreY - 0.7, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball11, bossCoreX + 0.3, bossCoreY - 0.7, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball12, bossCoreX + 0.8, bossCoreY - 0.7, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball13, bossCoreX + 1.3, bossCoreY - 0.7, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball14, bossCoreX + 1.3, bossCoreY -0.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball15, bossCoreX + 1.3, bossCoreY + 0.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball16, bossCoreX + 1.3, bossCoreY + 0.8, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball17, bossCoreX + 0.8, bossCoreY + 1.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball18, bossCoreX + 0.3, bossCoreY + 1.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball19, bossCoreX - 0.2, bossCoreY + 1.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball20, bossCoreX - 0.7, bossCoreY + 1.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball21, bossCoreX - 0.7, bossCoreY + 0.8, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball22, bossCoreX - 0.7, bossCoreY + 0.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball23, bossCoreX - 0.7, bossCoreY - 0.2, 1));

    _boss2Balls.push_back(createEnemy(BOSS2_Ball24, bossCoreX - 1.2, bossCoreY - 1.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball25, bossCoreX - 0.7, bossCoreY - 1.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball26, bossCoreX - 0.2, bossCoreY - 1.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball27, bossCoreX + 0.3, bossCoreY - 1.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball28, bossCoreX + 1.8, bossCoreY - 0.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball29, bossCoreX + 1.8, bossCoreY + 0.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball30, bossCoreX + 0.8, bossCoreY + 1.8, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball31, bossCoreX + 0.3, bossCoreY + 1.8, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball32, bossCoreX - 0.2, bossCoreY + 1.8, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball33, bossCoreX - 1.2, bossCoreY - 0.2, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball34, bossCoreX - 1.2, bossCoreY - 0.7, 1));

    _boss2Balls.push_back(createEnemy(BOSS2_Ball35, bossCoreX - 1.2, bossCoreY - 1.7, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball36, bossCoreX - 0.7, bossCoreY - 1.7, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball37, bossCoreX + 0.3, bossCoreY + 2.3, 1));
    _boss2Balls.push_back(createEnemy(BOSS2_Ball38, bossCoreX - 1.7, bossCoreY - 1.2, 1));
    for (std::size_t i = 0; i < _boss2Balls.size(); i++) {
        _core->getComponents<ECS::Components::AI>()[_boss2Balls[i]]->setCooldown(250 * (_boss2Balls.size() - i));
    }
}

void Rtype::Game::initGame(int id)
{
    stopMusic("menu");
    destroyEntityMenu();
    destroyEntityLayer();
    destroyMusic();
    playMusic("stage1");
    createBackgroundLayers(2.f , "background_layer0", 3);
    createBackgroundLayers(3.f , "background_layer1", 3);
    createBackgroundLayers(5.f , "background_layer2", 3);
    createPlayer(id, -10.0f, 0.0f, 50);

    switchState(GameState::PLAY);

    // createPlayer(0, -10.0f, 0.0f, 50);
    // createOtherPlayer(1, -10.0f, 0.0f);

    // createBoss1();

    // createBoss1Tail(BOSS1_Tail0, 6.0f, 3.0f);
    // createBoss1Tail(BOSS1_Tail1, 6.1f, 2.7f);
    // createBoss1Tail(BOSS1_Tail2, 5.8f, 2.4f);
    // createBoss1Tail(BOSS1_Tail3, 6.2f, 2.1f);
    // createBoss1Tail(BOSS1_Tail4, 6.0f, 1.8f);
    // createBoss1Tail(BOSS1_Tail5, 6.1f, 1.5f);
    // createBoss1Tail(BOSS1_Tail6, 5.9f, 1.2f);
    // createBoss1Tail(BOSS1_Tail7, 5.8f, 0.9f);
    // createBoss1Tail(BOSS1_Tail8, 6.1f, 0.6f);
    // createBoss1Tail(BOSS1_Tail9, 6.0f, 0.3f);
    // createBoss1Tail(BOSS1_Tail10, 6.2f, 0.0f);
    // createBoss1Tail(BOSS1_Tail11, 5.9f, -0.3f);
    // createBoss1Tail(BOSS1_Tail12, 5.7f, -0.6f);
    // createBoss1Tail(BOSS1_Tail13, 6.0f, -0.9f);
    // createBoss1Tail(BOSS1_Tail14, 6.1f, -1.2f);
    // createBoss1Tail(BOSS1_Tail15, 5.9f, -1.5f);
    // createBoss1Tail(BOSS1_Tail16, 5.7f, -1.8f);
    // createBoss1Tail(BOSS1_Tail17, 6.0f, -2.1f);
    // createBoss1Tail(BOSS1_Tail18, 5.9f, -2.4f);
    // createBoss1Tail(BOSS1_Tail19, 6.2f, -2.7f);

    //ay = ((by - cy) / 2) * sin((π / (bx - cx)) * (ax - ((bx + cx) / 2))) + ((by + cy) / 2)

    // createEnemy(PATAPATA, 15.5f, -3.0f, 1);
    // createEnemy(PATAPATA, 16.5f, -2.9f, 1);
    // createEnemy(PATAPATA, 17.5f, -2.8f, 1);
    // createEnemy(PATAPATA, 18.5f, -3.0f, 1);
    // createEnemy(PATAPATA, 19.5f, -3.2f, 1);

    // createEnemy(PATAPATA, 15.5f, 3.0f, 1);
    // createEnemy(PATAPATA, 16.5f, 2.9f, 1);
    // createEnemy(PATAPATA, 17.5f, 2.8f, 1);
    // createEnemy(PATAPATA, 18.5f, 3.2f, 1);
    // createEnemy(PATAPATA, 19.5f, 2.0f, 1);

    // createEnemy(BUG, 15.5f, 0.25f, 1);
    // createEnemy(BUG, 16.25f, 0.25f, 1);
    // createEnemy(BUG, 17.0f, 0.25f, 1);
    // createEnemy(BUG, 17.75f, 0.25f, 1);
    // createEnemy(BUG, 18.5f, 0.25f, 1);
    // createEnemy(BUG, 19.25f, 0.25f, 1);


    // createEnemy(BUG, 15.5f, 3.25f, 1);
    // createEnemy(BUG, 16.25f, 3.25f, 1);
    // createEnemy(BUG, 17.0f, 3.25f, 1);
    // createEnemy(BUG, 17.75f, 3.25f, 1);
    // createEnemy(BUG, 18.5f, 3.25f, 1);
    // createEnemy(BUG, 19.25f, 3.25f, 1);

    // createEnemy(MINIKIT, 17.0f, -4.0f);
}

void Rtype::Game::run()
{
    // std::thread musicThread(&Rtype::Game::loadMusic, this);

    // musicThread.join();
    initMenu();
    while (!_window.ShouldClose() && _isRunning) {
        switch (_currentState) {
            case MENU:
                // updateMusic("menu");
                updateMenu();
                renderMenu();
                break;
            case PLAY:
                // updateMusic("stage1");
                update();
                render();
                break;
        }
    }
    CloseAudioDevice();
}

void Rtype::Game::runServer()
{
    _currentState = PLAY;

    while (_isRunning)
        switch (_currentState) {
            case PLAY:
                update();
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
}


std::vector<std::size_t> Rtype::Game::getAllInputs() {
    std::vector<std::size_t> vec;

    if (IsKeyDown(KEY_RIGHT))
        vec.push_back(1);
    if (IsKeyDown(KEY_UP))
        vec.push_back(2);
    if (IsKeyDown(KEY_LEFT))
        vec.push_back(3);
    if (IsKeyDown(KEY_DOWN))
        vec.push_back(4);
    if (IsKeyPressed(KEY_SPACE))
        vec.push_back(5);
    return vec;
}

void Rtype::Game::switchState(GameState newState)
{
    _currentState = newState;
}

void Rtype::Game::createEnemyProjectile(int entityId, int projectileId, enemiesTypeEnum_t projectileType)
{
    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();
    std::size_t localEntityId = _serverToLocalEnemiesId[entityId];
    auto &ai = _core->getComponent<ECS::Components::AI>(localEntityId);
    const ECS::Components::Position &enemyPos = positions[localEntityId].value();
    const ECS::Components::Hitbox &enemyHitbox = hitboxes[localEntityId].value();
    std::size_t projectile = _core->createEntity();
    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("base_projectile"));
    float projectileStartX = enemyPos.getX() - (enemyHitbox.getWidth() / 2) - TmpHitbox.first;

    std::vector<std::pair<float, float>> playersPos;
    for (const auto& player : _serverToLocalPlayersId)
        playersPos.push_back(positions[player.second]->getPosPair());
    std::size_t targetPlayer = ecsUtils::getClosestPlayer(
        positions[localEntityId]->getPosPair(), playersPos);
    for (const auto& player : _serverToLocalPlayersId)
        if (positions[player.second]->getPosPair() == playersPos[targetPlayer])
            targetPlayer = player.second;

    float tmpVeloX = positions[targetPlayer]->getX() - positions[localEntityId]->getX();
    float tmpVeloY = positions[targetPlayer]->getY() - positions[localEntityId]->getY();
    float tmpMagnitude = std::sqrt(tmpVeloX * tmpVeloX + tmpVeloY * tmpVeloY);

    _core->addComponent(projectile, ECS::Components::Position{
        projectileStartX,
        enemyPos.getY()
    });
    _core->addComponent(projectile, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Scale{1.0f});
    _core->addComponent(projectile, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(projectile, ECS::Components::Velocity{tmpVeloX / tmpMagnitude * 0.075f, tmpVeloY / tmpMagnitude * 0.075f});
    _core->addComponent(projectile, ECS::Components::Projectile{});
    _core->addComponent(projectile, ECS::Components::AI{projectileType});
    _core->addComponent(projectile, ECS::Components::Render3D{"base_projectile"});
    //std::cout << "createProjectile : server("  << projectileId << ")" << " local(" << projectile << ")" << std::endl;
    _serverToLocalProjectilesId[projectileId] = projectile;
}

void Rtype::Game::createPlayerProjectile(int entityId, int projectileId)
{
    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();

    if (!positions[_serverToLocalPlayersId[entityId]].has_value()) {
        return;
    }
    const ECS::Components::Position &entityPos = positions[_serverToLocalPlayersId[entityId]].value();
    const ECS::Components::Hitbox &entityHitbox = hitboxes[_serverToLocalPlayersId[entityId]].value();

    std::size_t projectile = _core->createEntity();

    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("base_projectile"));
    _core->addComponent(projectile, ECS::Components::Position{entityPos.getX() + entityHitbox.getWidth(), entityPos.getY()});
    _core->addComponent(projectile, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Scale{1.0f});
    //_core->addComponent(projectile, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(projectile, ECS::Components::Velocity{0.2f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Projectile{});
    _core->addComponent(projectile, ECS::Components::Render3D{"base_projectile"});


    playSound("blasterLego");
    _serverToLocalProjectilesId[projectileId] = projectile;
}

void Rtype::Game::createPodProjectile(int entityId, int projectileId)
{
    auto &positions = _core->getComponents<ECS::Components::Position>();
    auto &hitboxes = _core->getComponents<ECS::Components::Hitbox>();

    if (!positions[_serverToLocalPodsId[entityId]].has_value()) {
        return;
    }
    const ECS::Components::Position &entityPos = positions[_serverToLocalPodsId[entityId]].value();
    const ECS::Components::Hitbox &entityHitbox = hitboxes[_serverToLocalPodsId[entityId]].value();

    std::size_t projectile = _core->createEntity();

    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("base_projectile"));
    _core->addComponent(projectile, ECS::Components::Position{entityPos.getX() + entityHitbox.getWidth(), entityPos.getY()});
    _core->addComponent(projectile, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Scale{1.0f});
    _core->addComponent(projectile, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(projectile, ECS::Components::Velocity{0.2f, 0.0f});
    _core->addComponent(projectile, ECS::Components::Projectile{});
    _core->addComponent(projectile, ECS::Components::Render3D{"base_projectile"});
    playSound("blasterLego");
    _serverToLocalProjectilesId[projectileId] = projectile;
}

void Rtype::Game::createProjectile(int entityId, int projectileId)
{
    std::cout << "==== createProjectile() -> entityId: " << entityId << std::endl;
    if (_serverToLocalEnemiesId.find(entityId) != _serverToLocalEnemiesId.end()) {
        if (_core->getComponents<ECS::Components::AI>()[_serverToLocalEnemiesId[entityId]]->getEnemyType() == BLASTER)
            createEnemyProjectile(entityId, projectileId, HOMINGSHOT);
        else
            createEnemyProjectile(entityId, projectileId, BYDOSHOT);
    }
    else if (_serverToLocalPlayersId.find(entityId) != _serverToLocalPlayersId.end())
        createPlayerProjectile(entityId, projectileId);
    else if (_serverToLocalPodsId.find(entityId) != _serverToLocalPodsId.end()){
        std::cout << "====== jaj ======" << std::endl;
        createPodProjectile(entityId, projectileId);
    }
}

void Rtype::Game::createPod(int entityId, float posX, float posY)
{
    std::size_t pod = _core->createEntity();
    std::cout << "==== createPod() -> (local)podId " << pod << " (server)podId: " << entityId << std::endl;

    if (_isRendering) {
        std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("enemy_one"));
        _core->addComponent(pod, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
        _core->addComponent(pod, ECS::Components::Render3D{"enemy_one"});
    }
    _core->addComponent(pod, ECS::Components::Pod{});
    _core->addComponent(pod, ECS::Components::Position{posX, posY});
    _core->addComponent(pod, ECS::Components::Rotate{0.0f, 0.0f, 0.0f});
    _core->addComponent(pod, ECS::Components::Scale{1.0f});
    _serverToLocalPodsId[entityId] = pod;
    std::cout << "==== createPod() -> (local)podId " << _serverToLocalPodsId[entityId] << " (server)podId: " << entityId << std::endl;
}

void Rtype::Game::damageEntity(int entityId)
{
    std::size_t toDamage;
    if (_serverToLocalPlayersId.find(entityId) != _serverToLocalPlayersId.end())
        toDamage = _serverToLocalPlayersId.at(entityId);
    if (_serverToLocalEnemiesId.find(entityId) != _serverToLocalEnemiesId.end())
        toDamage = _serverToLocalEnemiesId.at(entityId);
    std::size_t currentHealth = _core->getComponent<ECS::Components::Health>(toDamage).getHealth();

    _core->getComponent<ECS::Components::Health>(toDamage).setHealth(currentHealth - 1);
    _core->getComponent<ECS::Components::Health>(toDamage).setInvincibility(15);
}

void Rtype::Game::destroyEntity(int entityId)
{
    std::size_t toDestroy;

    if (_serverToLocalPlayersId.find(entityId) != _serverToLocalPlayersId.end()) {
        toDestroy = _serverToLocalPlayersId.at(entityId);
        _serverToLocalPlayersId.erase(entityId);
    }
    if (_serverToLocalEnemiesId.find(entityId) != _serverToLocalEnemiesId.end()) {
        if (_core->getComponents<ECS::Components::AI>()[_serverToLocalEnemiesId.at(entityId)]->getEnemyType() == MINIKIT && _isRendering) {
        }
        toDestroy = _serverToLocalEnemiesId.at(entityId);
        _serverToLocalEnemiesId.erase(entityId);
    }
    if (_serverToLocalProjectilesId.find(entityId) != _serverToLocalProjectilesId.end()) {
        std::cout << "====== Destroy " << _serverToLocalProjectilesId.at(entityId) << " in destroyEntity() ======" << std::endl;
        toDestroy = _serverToLocalProjectilesId.at(entityId);
        _serverToLocalProjectilesId.erase(entityId);
    }
    _core->destroyEntity(toDestroy);
}

void Rtype::Game::createBackgroundLayers(float speed, std::string modelPath, int numberOfPanel)
{
    float width = _ressourcePool.getTexture(modelPath).GetWidth();

    for (int i = 0; i < numberOfPanel; i++) {
        std::size_t background = _core->createEntity();

        _core->addComponent(background, ECS::Components::Position{0.0f + (width * i) - 1, 0.0f});
        _core->addComponent(background, ECS::Components::Velocity{-speed, 0.0f});
        _core->addComponent(background, ECS::Components::Render2D{modelPath});
        _core->addComponent(background, ECS::Components::Background{width, speed});
    }
}

//!FUNCTIONS TO UPDATE GAME AND MENU -------------------------------------------

void Rtype::Game::updateMenu() {
    auto clicSystem = _core->getSystem<ECS::Systems::ButtonClickSystem>();
    auto inputTextfieldSystem = _core->getSystem<ECS::Systems::TextFieldInputSystem>();

    auto buttonEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::ButtonClickSystem>());
    auto textfieldEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::TextFieldInputSystem>());

    clicSystem->update(_core->getComponents<ECS::Components::Button>(),
                        buttonEntities);
    inputTextfieldSystem->update(_core->getComponents<ECS::Components::TextField>(),
                                 textfieldEntities);
}

void Rtype::Game::sendPods(std::size_t podId)
{
    int serverPodId;

    for (const auto& pod : _serverToLocalPodsId)
        if (pod.second == podId)
            serverPodId = pod.first;

    std::cout << "podServerId: " << serverPodId << std::endl;
}

void Rtype::Game::update() {
    auto velocitySystem = _core->getSystem<ECS::Systems::SystemVelocity>();
    auto collisionSystem = _core->getSystem<ECS::Systems::Collision>();
    auto projectileCollisionSystem = _core->getSystem<ECS::Systems::ProjectileCollision>();
    auto inputUpdatesSystem = _core->getSystem<ECS::Systems::InputUpdates>();
    auto backgroundSystem = _core->getSystem<ECS::Systems::SystemBackground>();
    auto AIVelocitySystem = _core->getSystem<ECS::Systems::UpdateVelocityAI>();
    auto AIFiringProjectileSystem = _core->getSystem<ECS::Systems::AIFiringProjectile>();
    auto getDeadEntitiesSystem = _core->getSystem<ECS::Systems::GetDeadEntities>();

    std::vector<std::size_t> velocityEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemVelocity>());
    std::vector<std::size_t> playerCollisionEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::Collision>());
    std::vector<std::size_t> projectileEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::ProjectileCollision>());
    std::vector<std::size_t> inputEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::InputUpdates>());
    std::vector<std::size_t> backgroundEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemBackground>());
    std::vector<std::size_t> AIEntities = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::UpdateVelocityAI>());
    std::vector<std::size_t> AIs = _core->getEntitiesWithComponent<ECS::Components::AI>();
    std::vector<std::size_t> collisionEntities = _core->getEntitiesWithComponent<ECS::Components::Position,
                                                                                 ECS::Components::Hitbox>();
    std::vector<std::size_t> damageableEntities = _core->getEntitiesWithComponent<ECS::Components::Health>();
    std::vector<std::size_t> playerEntities;
    for (const auto& Ids : _serverToLocalPlayersId)
        playerEntities.push_back(Ids.second);

    AIVelocitySystem->update(_core->getComponents<ECS::Components::Velocity>(),
                             _core->getComponents<ECS::Components::Position>(),
                             _core->getComponents<ECS::Components::AI>(),
                             AIEntities, _serverToLocalPlayersId);

    std::vector<std::size_t> inputs = getAllInputs();
    inputUpdatesSystem->updateInputs(inputs,
                        _core->getComponents<ECS::Components::Input>(),
                        inputEntities);

    inputUpdatesSystem->updateInputedVelocity(_core->getComponents<ECS::Components::Input>(),
                                              _core->getComponents<ECS::Components::Velocity>(),
                                              inputEntities);

    backgroundSystem->update(_core->getComponents<ECS::Components::Position>(),
                             _core->getComponents<ECS::Components::Background>(),
                             backgroundEntities);

    velocitySystem->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Velocity>(),
                           _serverToLocalPlayersId,
                           velocityEntities);

    if (_isRendering && _currentState == PLAY) {
        collisionSystem->playerIsHit(_core->getComponents<ECS::Components::Position>(),
                                     _core->getComponents<ECS::Components::Hitbox>(),
                                     _core->getComponents<ECS::Components::Health>(),
                                     _core->getEntitiesWithComponent<ECS::Components::Input>()[0],
                                     playerCollisionEntities);
    }

    std::vector<std::size_t> damageableAIs = _core->getEntitiesWithComponent<ECS::Components::AI, ECS::Components::Health>();
    for (std::size_t i = 0; i < damageableAIs.size(); i++) {
        if (_core->getComponents<ECS::Components::Health>()[damageableAIs[i]]->getInvincibility() > 0)
            _core->getComponents<ECS::Components::Health>()[damageableAIs[i]]->modifyInvincibilityBy(-1);
    }

    if (_isRendering) {
        std::vector<std::size_t> projectileEntityId = projectileCollisionSystem->projectileIsHit(
            _core->getComponents<ECS::Components::Position>(),
            _core->getComponents<ECS::Components::Hitbox>(),
            _core->getComponents<ECS::Components::AI>(),
            projectileEntities, collisionEntities, AIs);
        auto healthComponents = _core->getComponents<ECS::Components::Health>();
        auto podsEntities = _core->getEntitiesWithComponent<ECS::Components::Pod>();
        auto pods = _core->getComponents<ECS::Components::Pod>();
        _damagedEntities.insert(_damagedEntities.end(), projectileEntityId.begin(), projectileEntityId.end());
        projectileEntityId.clear();

        std::vector<std::size_t> hitByPodEntity = collisionSystem->AIHitPod(
            _core->getComponents<ECS::Components::Position>(), _core->getComponents<ECS::Components::Hitbox>(),
            _core->getComponents<ECS::Components::Health>(), _core->getComponents<ECS::Components::Pod>(),
            podsEntities, _core->getEntitiesWithComponent<ECS::Components::AI, ECS::Components::Health>());
        _damagedEntities.insert(_damagedEntities.end(), hitByPodEntity.begin(), hitByPodEntity.end());
        hitByPodEntity.clear();

        for (int i = 0; i < _damagedEntities.size(); i++) {
            for (int j = 0; j < damageableEntities.size(); j++) {
                if (damageableEntities[j] == _damagedEntities[i] && healthComponents[damageableEntities[j]]->getInvincibility() == 0) {
                    // _damagedEntities.push_back(damageableEntities[j]);
                    // for (std::size_t i; i < serverDamagedEntities.size(); i++)
                }
            }
            for (int j = 0; j < projectileEntities.size(); j++)
                if (projectileEntities[j] == _damagedEntities[i]) {
                    //std::cout << "destroy projectile : " << projectileEntities[j] << std::endl;
                    // for (const auto& Ids : _serverToLocalProjectilesId)
                    //     if (Ids.second == projectileEntities[j])
                    //         _serverToLocalProjectilesId.erase(Ids.first);
                    _core->destroyEntity(projectileEntities[j]);
                }
        }
        _damagedEntities.clear();

        std::vector<std::size_t> podsToSend;
        if (_isRendering) {
            std::size_t player = _core->getEntitiesWithComponent<ECS::Components::Input>()[0];

            std::vector<std::size_t> pickedUpPod = collisionSystem->PlayerPickedUpPod(
                _core->getComponents<ECS::Components::Position>(), _core->getComponents<ECS::Components::Hitbox>(),
                _core->getComponents<ECS::Components::Pod>(),
                podsEntities, player);

            for (int i = 0; i < pickedUpPod.size(); i++) {
                std::cout << "pod is picked up hassoul!!" << std::endl;
                std::size_t pod = pickedUpPod[i];
                int nbPods = 0;
                int indexPod1 = -1;
                int indexPod2 = -1;
                for (int i = 0; i < podsEntities.size(); i++)
                    if (pods[podsEntities[i]]->getPlayer() == player){
                        if (nbPods == 0)
                            indexPod1 = podsEntities[i];
                        if (nbPods == 1)
                            indexPod2 = podsEntities[i];
                        nbPods++;
                    }
                std::cout << "nbPods: " << nbPods << std::endl;
                if (nbPods < 2) {
                    std::cout << "sendPods: " << pod << std::endl;
                    podsToSend.push_back(pod);
                    continue;
                }
                std::cout << "pod level: " << pods[indexPod1]->getLevel() << std::endl;
                if (pods[indexPod1]->getLevel() == 0) {
                    podsToSend.push_back(pod);
                    continue;
                }
                if (pods[indexPod2]->getLevel() == 0) {
                    podsToSend.push_back(pod);
                    continue;
                }
                if (pods[indexPod1]->getLevel() == 1 && pods[indexPod1]->getLevel() == 1) {
                    podsToSend.push_back(pod);
                    continue;
                }
            }

            for (int i = 0; i < podsToSend.size(); i++) {
                sendPods(podsToSend[i]);
            }
        }

        for (int i = 0; i < podsEntities.size(); i++) {
            std::size_t pod = podsEntities[i];
            std::size_t player = _core->getComponents<ECS::Components::Pod>()[pod]->getPlayer();
            if (player == 10000)
                continue;
            std::pair<float, float> playerPos = _core->getComponents<ECS::Components::Position>()[player]->getPosPair();

            _core->getComponents<ECS::Components::Position>()[pod]->setX(playerPos.first + 0.25);
            if (_core->getComponents<ECS::Components::Pod>()[pod]->isUp())
                _core->getComponents<ECS::Components::Position>()[pod]->setY(playerPos.second - 0.50);
            else
                _core->getComponents<ECS::Components::Position>()[pod]->setY(playerPos.second + 0.75);
        }
    }

    if (!_isRendering) {
        std::vector<std::size_t> deadEntities = getDeadEntitiesSystem->getDeadEntities(
            _core->getComponents<ECS::Components::Health>(),
            _core->getComponents<ECS::Components::Position>(),
            damageableEntities);
        _deadEntities.insert(_deadEntities.end(), deadEntities.begin(), deadEntities.end());
        for (int i = 0; i < deadEntities.size(); i++)
            _core->destroyEntity(deadEntities[i]);
        deadEntities.clear();
    }
/*
    for (std::size_t i = 0; i < deadEntities.size(); i++) {
        if (_isRendering) {
            if (deadEntities[i] == _core->getEntitiesWithComponent<ECS::Components::Input>()[0])
                sleep(3000);//GAMEOVER
        }
        if (_core->getComponent<ECS::Components::AI>(deadEntities[i]).getEnemyType() == BOSS1_Core) {
        if (deadEntities[i] == _core->getEntitiesWithComponent<ECS::Components::Input>()[0])
            //sleep(3000);//GAMEOVER
            std::cout << "SEGV LOL" << std::endl;
        else if (_core->getComponent<ECS::Components::AI>(deadEntities[i]).getEnemyType() == BOSS1_Core) {
            for (int i = BOSS1_Tail0; i <= BOSS1_Tail19; i++) {
                auto AIs = _core->getEntitiesWithComponent<ECS::Components::AI>();
                int tailId = 0;
                for (std::size_t j = 0; j < AIs.size(); j++)
                    if (_core->getComponent<ECS::Components::AI>(AIs[j]).getEnemyType() == i) {
                        tailId = AIs[j];
                        break;
                    }
                _core->destroyEntity(tailId);
            }
        }
        if (_core->getComponent<ECS::Components::AI>(deadEntities[i]).getEnemyType() == BOSS2_Core) {
            for (std::size_t balls = 0; balls < _boss2Balls.size(); balls++)
                if (_boss2Balls[balls] < 10000)
                    _core->destroyEntity(_boss2Balls[balls]);
        }
        for (std::size_t balls = 0; balls < _boss2Balls.size(); balls++)
            if (_boss2Balls[balls] == deadEntities[i])
                _boss2Balls[balls] = 10001;
        _core->destroyEntity(deadEntities[i]);
        deadEntities.clear();
    }
*/
    auto podEntities = _core->getEntitiesWithComponent<ECS::Components::Pod>();
    std::vector<std::size_t> AIBydoShots = AIFiringProjectileSystem->aiFiringBydoShots(
        _core->getComponents<ECS::Components::AI>(),
        _core->getComponents<ECS::Components::Position>(),
        AIEntities);
    if (!_isRendering && AIBydoShots.size() > 0)
        _projectilesToSend.insert(_projectilesToSend.end(), AIBydoShots.begin(), AIBydoShots.end());

    std::vector<std::size_t> AIHomingShots = AIFiringProjectileSystem->aiFiringHomingShots(
        _core->getComponents<ECS::Components::AI>(), AIEntities);
    if (!_isRendering && AIHomingShots.size() > 0)
        _projectilesToSend.insert(_projectilesToSend.end(), AIHomingShots.begin(), AIHomingShots.end());

    std::vector<std::size_t> podShots = AIFiringProjectileSystem->podFiringShots(
        _core->getComponents<ECS::Components::Pod>(), podEntities);
    if (!_isRendering && podShots.size() > 0)
        _projectilesToSend.insert(_projectilesToSend.end(), podShots.begin(), podShots.end());

    for (int i = 0; i < _projectilesToSend.size(); i++)
        std::cout << "all Projectiles: " << _projectilesToSend[i]<< std::endl;

    if (false)
        _camera.Update(CAMERA_FREE);
}

void Rtype::Game::equipPod(int playerId, int podId)
{
    std::cout << "pod " << podId << " is picked up by " << playerId << " hassoul!!" << std::endl;
    if (_serverToLocalPlayersId.begin() == _serverToLocalPlayersId.end())
        std::cout << "jaj" << std::endl;
    std::size_t player = _serverToLocalPlayersId.at(playerId);
    std::size_t pod = _serverToLocalPodsId.at(podId);
    auto pods = _core->getComponents<ECS::Components::Pod>();
    std::vector<std::size_t> podsEntities = _core->getEntitiesWithComponent<ECS::Components::Pod>();
    int nbPods = 0;
    int indexPod1 = -1;
    int indexPod2 = -1;
    for (int i = 0; i < podsEntities.size(); i++)
        if (pods[podsEntities[i]]->getPlayer() == player){
            if (nbPods == 0)
                indexPod1 = podsEntities[i];
            if (nbPods == 1)
                indexPod2 = podsEntities[i];
            nbPods++;
        }
    std::cout << "nbPods: " << nbPods << std::endl;
    if (nbPods < 2) {
        std::cout << "first two pod picked up hassoul!!" << std::endl;
        if (nbPods == 0)
            _core->getComponents<ECS::Components::Pod>()[pod]->setIsUp(true);
        _core->getComponents<ECS::Components::Pod>()[pod]->setPlayer(player);
        return;
    }
    std::cout << "pod level: " << pods[indexPod1]->getLevel() << std::endl;
    if (pods[indexPod1]->getLevel() == 0) {
        std::cout << "pod1 +1 level!!" << std::endl;
        _core->getComponents<ECS::Components::Pod>()[indexPod1]->setLevel(1);
        std::cout << "pod to destroy: " << pod << std::endl;
        _core->destroyEntity(pod);
        //destroy_current_pod
        return;
    }
    if (pods[indexPod2]->getLevel() == 0) {
        std::cout << "pod2 +1 level!!" << std::endl;
        _core->getComponents<ECS::Components::Pod>()[indexPod2]->setLevel(1);
        _core->destroyEntity(pod);
        //destroy_current_pod
        return;
    }
    if (pods[indexPod1]->getLevel() == 1 && pods[indexPod1]->getLevel() == 1) {
        std::cout << "pod1 & pod2 +1 level!!" << std::endl;
        _core->getComponents<ECS::Components::Pod>()[indexPod1]->setLevel(2);
        _core->getComponents<ECS::Components::Pod>()[indexPod2]->setLevel(2);
        _core->destroyEntity(pod);
        //destroy_current_pod
        return;
    }
}

bool Rtype::Game::getJoiningGame()
{
    return _isJoiningGame;
}

void Rtype::Game::setIsJoiningGame(bool state)
{
    _isJoiningGame = state;
}

bool Rtype::Game::getIsAvailableGames()
{
    return _isAvailableGames;
}

void Rtype::Game::setIsAvailableGames(bool state)
{
    _isAvailableGames = state;
}

std::vector<std::tuple<int, int, int>> Rtype::Game::getAvailableGames()
{
    return _availableGames;
}

void Rtype::Game::addAvailableGames(int game_id)
{
    _availableGames.push_back({game_id, 1, 2});
}

void Rtype::Game::clearAvailableGames()
{
    _availableGames.clear();
}

//!FUNCTIONS TO RENDER GAME AND MENU -------------------------------------------

void Rtype::Game::renderMenu() {
    BeginDrawing();
    _window.ClearBackground(BLACK);

    float currentWidth = GetScreenWidth();
    float currentHeight = GetScreenHeight();

    float scaleX = currentWidth / 1280.0f;
    float scaleY = currentHeight / 720.0f;

    auto renderSystemText = _core->getSystem<ECS::Systems::RenderTextSystem>();
    auto renderButtons = _core->getSystem<ECS::Systems::RenderButtonSystem>();
    auto renderSystem2D = _core->getSystem<ECS::Systems::SystemRender2D>();
    auto renderTextfield = _core->getSystem<ECS::Systems::RenderTextFieldSystem>();

    auto renderEntities2D  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender2D>());
    auto renderEntitiesText  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::RenderTextSystem>());
    auto renderEntitiesButton  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::RenderButtonSystem>());
    auto renderEntitiesTextfield  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::RenderTextFieldSystem>());


    for (auto entity : renderEntitiesButton) {
        auto &buttonPosition = _core->getComponent<ECS::Components::Position>(entity);
        auto &buttonComponent = _core->getComponent<ECS::Components::Button>(entity);
        float x = buttonPosition.getOriginalX();
        float y = buttonPosition.getOriginalY();
        Rectangle rect = buttonComponent.getOriginalBounds();

        buttonPosition.setX(x * scaleX);
        buttonPosition.setY(y * scaleY);
        rect.x *= scaleX;
        rect.y *= scaleY;
        buttonComponent.setBounds(rect);
    }

    renderSystem2D->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Render2D>(),
                           renderEntities2D,
                           _ressourcePool);

    renderTextfield->update(_core->getComponents<ECS::Components::TextField>(),
                            _core->getComponents<ECS::Components::Text>(),
                            _core->getComponents<ECS::Components::Position>(),
                            renderEntitiesTextfield);

    renderSystemText->update(_core->getComponents<ECS::Components::Text>(),
                            _core->getComponents<ECS::Components::Position>(),
                            renderEntitiesText);

    renderButtons->update(_core->getComponents<ECS::Components::Button>(),
                          _core->getComponents<ECS::Components::Text>(),
                          _core->getComponents<ECS::Components::Position>(),
                          renderEntitiesButton);
    EndDrawing();
}

void Rtype::Game::render() {
    BeginDrawing();
    _window.ClearBackground(RAYWHITE);

    float currentWidth = GetScreenWidth();
    float currentHeight = GetScreenHeight();

    float scaleX = currentWidth / 1280.0f;
    float scaleY = currentHeight / 720.0f;

    auto renderSystem2D = _core->getSystem<ECS::Systems::SystemRender2D>();
    auto renderEntities2D  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender2D>());

    auto renderSystem3D = _core->getSystem<ECS::Systems::SystemRender3D>();
    auto renderEntities3D  = _core->getEntitiesWithSignature(_core->getSystemSignature<ECS::Systems::SystemRender3D>());

    renderSystem2D->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Render2D>(),
                           renderEntities2D,
                           _ressourcePool);

    DrawFPS(100, 100);
    renderSystem3D->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Rotate>(),
                           _core->getComponents<ECS::Components::Scale>(),
                           _core->getComponents<ECS::Components::Render3D>(),
                           renderEntities3D,
                           _ressourcePool,
                           _camera);


    EndDrawing();
}

//!FUNCTIONS TO HANDLE MUSIC AND SOUND -----------------------------------------


void Rtype::Game::createMusic(std::string path, std::string name) {
    std::size_t musicEntity = _core->createEntity();
    ECS::Components::Musica musicaComponent{path};

    _core->addComponent(musicEntity, musicaComponent);
    _musicMap.emplace(name, std::move(musicaComponent));
}

void Rtype::Game::createSound(std::string path, std::string name) {
    std::size_t soundEntity = _core->createEntity();
    ECS::Components::SoundEffect soundComponent{path};

    _core->addComponent(soundEntity, soundComponent);
    _soundMap.emplace(name, std::move(soundComponent));
}

void Rtype::Game::updateMusic(std::string name) {
    auto it = _musicMap.find(name);

    if (it != _musicMap.end()) {
        it->second.update();
    }
}

void Rtype::Game::playFromMusic(std::string name, float sec) {
    auto it = _musicMap.find(name);

    if (it != _musicMap.end()) {
        it->second.playFrom(sec);
    }
}

void Rtype::Game::stopMusic(std::string name) {
    auto it = _musicMap.find(name);

    if (it != _musicMap.end()) {
        it->second.stop();
    }
}

void Rtype::Game::playMusic(std::string name) {
    auto it = _musicMap.find(name);

    if (it != _musicMap.end()) {
        it->second.play();
    }
}

void Rtype::Game::playSound(std::string name) {
    auto it = _soundMap.find(name);

    if (it != _soundMap.end()) {
        it->second.play();
    } else {
        std::cout << "Sound not found" << std::endl;
    }
}

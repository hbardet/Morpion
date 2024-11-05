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
    _isJoiningGame(false), _isAvailableGames(false), _isRendering(render), _modelCreated(false), _isConnectedToServer(false), _vectorMorpion(), _turnPlayer(false), _collision(false, 0.0f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.f})
{
    _vectorMorpion[0] = -1;
    _vectorMorpion[1] = -1;
    _vectorMorpion[2] = -1;
    _vectorMorpion[3] = -1;
    _vectorMorpion[4] = -1;
    _vectorMorpion[5] = -1;
    _vectorMorpion[6] = -1;
    _vectorMorpion[7] = -1;
    _vectorMorpion[7] = -1;
    _vectorMorpion[8] = -1;
    _core = std::make_unique<ECS::Core::Core>();

    if (render) {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        SetTargetFPS(60);
        _window.Init(1280, 720, "MorpionXOX");
        SetWindowMinSize(1280, 720);
        _camera = raylib::Camera3D({ -5.0f, 5.0f, 0.0f}, {0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 60.0f);
        _ressourcePool.addModel("boss_one_part");
        _ressourcePool.addModel("patapata");
        _ressourcePool.addTexture("bg_menu");
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
    std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("boss_one_part"));
    std::size_t player = _core->createEntity();

    _core->addComponent(player, ECS::Components::Position{pos_x, pos_y});
    _core->addComponent(player, ECS::Components::Rotate{-90.0f, 0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Scale{1.0f});
    _core->addComponent(player, ECS::Components::Velocity{0.0f, 0.0f});
    _core->addComponent(player, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
    _core->addComponent(player, ECS::Components::Input{});
    _core->addComponent(player, ECS::Components::Health{5, -1// invincibility
        });
    _core->addComponent(player, ECS::Components::Render3D{"boss_one_part"});
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
        std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(_ressourcePool.getModel("boss_one_part"));
        _core->addComponent(otherPlayer, ECS::Components::Hitbox{TmpHitbox.first, TmpHitbox.second});
        _core->addComponent(otherPlayer, ECS::Components::Render3D{"boss_one_part"});
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

void Rtype::Game::setIdPlayer(int id)
{
    _idPlayer = id;
    if (_idPlayer == 0)
        _turnPlayer = true;
    else
        _turnPlayer = false;

    std::cout << "ID PLAYER: " << _idPlayer << std::endl;
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
        // if (!_isConnectedToServer) {
        //     if (system("ls | grep -q r-type_server") == 0 && !_localServer.joinable()) {
        //         _network->setSenderEndpoint(udp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 2442)); //! Tmp get available port
        //         int port = static_cast<int>(_network->getSenderEndpoint().port());

        //         CONSOLE_INFO("A local server is now set.\nTo access to the server your local address is used (127.0.0.1) on the port ", port);
        //         _localServer = std::thread([this, port]() {
        //             std::string cmd("./r-type_server " + std::to_string(port));

        //             system(cmd.c_str());
        //         });

        //         std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //         std::unique_ptr<Rtype::Command::GameInfo::Client_connection> cmd_connection = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Client_connection, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::NewClientConnected);
        //         cmd_connection->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
        //         _network->addCommandToInvoker(std::move(cmd_connection));
        //         std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //     }
        // }
        // if (_isConnectedToServer) {

        // }
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
            std::unique_ptr<Rtype::Command::GameInfo::Create_game> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::GameInfo::Create_game, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::CreateGame);

            cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
            cmd->set_client();
            _network->addCommandToInvoker(std::move(cmd));
            CONSOLE_INFO("Create game: ", " Sended")
        initGame(1);
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

void Rtype::Game::initGame(int id)
{
    destroyEntityMenu();
    destroyEntityLayer();

    switchState(GameState::PLAY);
    for (float y = -1; y < 2; y++){
        for (float x = -1; x < 2; x++) {
            std::size_t entity = _core->createEntity();
            _core->addComponent(entity, ECS::Components::Position{x * 1.5f, y * 1.5f});
            _core->addComponent(entity, ECS::Components::Rotate{-90.0f, 45.0f, 0.0f});
            _core->addComponent(entity, ECS::Components::Scale{2.0f});
            _core->addComponent(entity, ECS::Components::Render3D{""});
            _vecIdMorpion.push_back(entity);
            raylib::BoundingBox box = {
                Vector3{x * 1.5f - 0.5f, -0.5f, y * 1.5f - 0.5f},
                Vector3{x * 1.5f + 0.5f, 0.5f, y * 1.5f + 0.5f}
            };
            _vecBoxMorpion.push_back(box);
        }
    }
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
                updateMorpion();
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
                updateMorpion();
                std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
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

void Rtype::Game::updateMorpion()
{
    int index = 0;

    for (auto &entity : _vecIdMorpion){
        auto &caseGame = _core->getComponent<ECS::Components::Render3D>(entity);

        switch (_vectorMorpion[index]) {
            case 0 :
                caseGame.setPath("patapata");
                break;
            case 1 :
                caseGame.setPath("boss_one_part");
                break;
            default:
                caseGame.setPath("");
       }
       index++;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        _ray = raylib::Ray(raylib::Mouse::GetPosition(), _camera);

        for (int i = 0; i < _vecBoxMorpion.size(); i++) {
            raylib::RayCollision tmpCollision(_ray, _vecBoxMorpion[i]);
            if (tmpCollision.GetHit()) {
                _collision = tmpCollision;
                if (_turnPlayer) {
                    std::unique_ptr<Rtype::Command::Player::SetPawn> cmd = CONVERT_ACMD_TO_CMD(Rtype::Command::Player::SetPawn, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::SetPawn);
                    cmd->setCommonPart(_network->getSocket(), _network->getSenderEndpoint(), _network->getAckToSend());
                    cmd->set_client(i); //! Index to adapt 0-8
                    _network->addCommandToInvoker(std::move(cmd));
                }
                break;
            }
        }
    }
    _camera.Update(CAMERA_ORBITAL);
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
    _availableGames.push_back({game_id , 1, 2});
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

void Rtype::Game::placeMorpion(int idPlayer, int pos)
{
    if (pos < 9 && _vectorMorpion[pos] == -1)
        _vectorMorpion[pos] = idPlayer;
    _turnPlayer = !_turnPlayer;
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
    std::vector<raylib::BoundingBox> tmp;
    for (size_t i = 0; i < _vectorMorpion.size(); i++) {
        if (_vectorMorpion[i] == -1) {
            tmp.push_back(_vecBoxMorpion[i]);
        }
    }
    renderSystem3D->update(_core->getComponents<ECS::Components::Position>(),
                           _core->getComponents<ECS::Components::Rotate>(),
                           _core->getComponents<ECS::Components::Scale>(),
                           _core->getComponents<ECS::Components::Render3D>(),
                           renderEntities3D,
                           _ressourcePool,
                           _camera,
                           tmp);


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

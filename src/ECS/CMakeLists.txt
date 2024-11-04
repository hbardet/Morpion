project(R-Type-ECS)

set(NAME_LIB ${RTYPE} CACHE INTERNAL "")
set(NAME_DEBUG_EXE "${RTYPE}-ECS-Debug")

set(LIB_SOURCES
    ./Core/Core.cpp
    ./Utils/Utils.cpp
    ./Entity/Missile/Missile.cpp
    ./Entity/Enemy/Enemy.cpp
    ./Entity/EntityManager/EntityManager.cpp
    ./Entity/Button/Button.cpp
    ./Entity/Player/Player.cpp
    ./Component/Position/Position.cpp
    ./Component/Health/Health.cpp
    ./Component/Projectile/Projectile.cpp
    ./Component/Velocity/Velocity.cpp
    ./Component/Hitbox/Hitbox.cpp
    ./Component/Text/Text.cpp
    ./Component/Music/Music.cpp
    ./Component/Rotate/Rotate.cpp
    ./Component/Scale/Scale.cpp
    ./Component/Sound/Sound.cpp
    ./Component/Input/Input.cpp
    ./Component/Render2D/Render2D.cpp
    ./Component/Render3D/Render3D.cpp
    ./Component/Button/Button.cpp
    ./Component/Light/Light.cpp
    ./Component/AI/AI.cpp
    ./Component/Textfield/Textfield.cpp
    ./Component/Pod/Pod.cpp
    ./System/Velocity/Velocity.cpp
    ./System/Collision/Collision.cpp
    ./System/UpdateVelocityAI/UpdateVelocityAI.cpp
    ./System/ProjectileCollision/ProjectileCollision.cpp
    ./System/InputUpdates/InputUpdates.cpp
    ./System/Render2D/Render2D.cpp
    ./System/Render3D/Render3D.cpp
    ./System/Background/Background.cpp
    ./System/RenderText/RenderText.cpp
    ./System/ButtonClick/ButtonClick.cpp
    ./System/RenderButton/RenderButton.cpp
    ./System/GetDeadEntities/GetDeadEntities.cpp
    ./System/AIFiringProjectile/AIFiringProjectile.cpp
    ./System/TextfieldInput/TextfieldInput.cpp
    ./System/RenderTextfield/RenderTextfield.cpp
    ./RessourcePool/RessourcePool.cpp

)
# Créer la bibliothèque
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_library(${NAME_LIB} STATIC ${LIB_SOURCES})
set_target_properties(${NAME_LIB} PROPERTIES
    OUTPUT_NAME ${NAME_LIB}
    SUFFIX ".a"
)
target_link_libraries(${NAME_LIB} PUBLIC raylib raylib_cpp)

# Inclure les répertoires des headers
target_include_directories(${NAME_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}Core
    ${CMAKE_CURRENT_SOURCE_DIR}Utils
    ${CMAKE_CURRENT_SOURCE_DIR}Entity
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/Missile
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/Enemy
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/EntityManager
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/Button
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/Player
    ${CMAKE_CURRENT_SOURCE_DIR}Component
    ${CMAKE_CURRENT_SOURCE_DIR}Component/ComponentManager
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Position
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Health
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Render
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Velocity
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Hitbox
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Text
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Volume
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Projectile
    ${CMAKE_CURRENT_SOURCE_DIR}Component/AI
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Pod
    ${CMAKE_CURRENT_SOURCE_DIR}System
    ${CMAKE_CURRENT_SOURCE_DIR}System/ButtonClick
    ${CMAKE_CURRENT_SOURCE_DIR}System/SystemManager
    ${CMAKE_CURRENT_SOURCE_DIR}System/Velocity
    ${CMAKE_CURRENT_SOURCE_DIR}System/System
    ${CMAKE_CURRENT_SOURCE_DIR}System/Collision
    ${CMAKE_CURRENT_SOURCE_DIR}System/ProjectileCollision
    ${CMAKE_CURRENT_SOURCE_DIR}System/InputUpdates
)
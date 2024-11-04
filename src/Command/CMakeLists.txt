project(R-Type-Server-Cmd)

set(NAME_LIB_CMD ${RTYPE}-cmd CACHE INTERNAL "")

set(LIB_CMD_SRC
    ./Factory/Factory.cpp
    ./Commands/Game_info/Create_game/Create_game.cpp
    ./Commands/Game_info/Game_result/Game_result.cpp
    ./Commands/Game_info/Join_game/Join_game.cpp
    ./Commands/Game_info/Games_available/Games_available.cpp
    ./Commands/Game_info/Client_connection/Client_connection.cpp
    ./Commands/Game_info/Client_disconnect/Client_disconnect.cpp
    ./Commands/Game_info/Missing_packages/Missing_packages.cpp
    ./Commands/Player/SetPawn/SetPawn.cpp
    ./Invoker/Command_invoker.cpp
    ../Utils/ParametersMap/ParametersMap.cpp
)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_library(${NAME_LIB_CMD} STATIC ${LIB_CMD_SRC})
set_target_properties(${NAME_LIB_CMD} PROPERTIES
    OUTPUT_NAME ${NAME_LIB_CMD}
    SUFFIX ".a"
)

target_link_libraries(${NAME_LIB_CMD} PRIVATE Boost::asio)
target_link_libraries(${NAME_LIB_CMD} PRIVATE ${NAME_LIB})

target_include_directories(${NAME_LIB_CMD} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Game_info
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Game_info/Create_game
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Game_info/Game_result
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Game_info/Join_game
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Game_info/Games_available
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Game_info/Client_connection
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Game_info/Missing_packages
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/Player/Attack
    ${CMAKE_CURRENT_SOURCE_DIR}/Invoker
    ${CMAKE_CURRENT_SOURCE_DIR}/Factory
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utils/ParametersMap
)

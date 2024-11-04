project(R-Type-Client)

set(NAME_CLIENT "${RTYPE}_client")
set(CLIENT_SOURCES
    ./main.cpp
    ./Game/Game.cpp
    ./udp_client.cpp
    ../Utils/Network/Network.cpp
    ../Server/Client_info.cpp
    ../Server/Game_info.cpp
    ../Utils/Protocol/Protocol.cpp
    ../Utils/Response/Response.cpp
    ../Server/Parser/LoadData/LoadData.cpp         # Ajout de LoadData.cpp
    ../Server/Parser/EnemySpawnData/EnemySpawnData.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../Server/Parser/LoadData
    ../Server/Parser/EnemySpawnData
    ../Utils
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../Server/Parser/LoadData
    ../Server/Parser/EnemySpawnData
    ../Utils
)

if (WIN32)
    add_executable(${NAME_CLIENT} ${CLIENT_SOURCES})

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${NAME_CLIENT} PUBLIC Boost::asio)
    target_link_libraries(${NAME_CLIENT} PUBLIC raylib raylib_cpp ${NAME_LIB})
    target_link_libraries(${NAME_CLIENT} PUBLIC JsonCpp::JsonCpp)
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_CMD})
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_UTILS})
else()
    add_executable(${NAME_CLIENT} ${CLIENT_SOURCES})

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${NAME_CLIENT} PUBLIC Boost::asio)
    target_link_libraries(${NAME_CLIENT} PUBLIC raylib raylib_cpp ${NAME_LIB})
    target_link_libraries(${NAME_CLIENT} PUBLIC jsoncpp)
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_CMD})
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_UTILS})
endif()
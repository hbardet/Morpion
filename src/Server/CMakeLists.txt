project(r-type_server)

set(NAME_SERVER "${RTYPE}_server")
set(SERVER_SOURCES
    ./Client_info.cpp
    ./Game_info.cpp
    ./udp_server.cpp
    ./Parser/LoadData/LoadData.cpp
    ./Parser/EnemySpawnData/EnemySpawnData.cpp
    ./main.cpp
    ${CMAKE_SOURCE_DIR}/src/Utils/ParametersMap/ParametersMap.cpp
    ${CMAKE_SOURCE_DIR}/src/Utils/Protocol/Protocol.cpp
    ${CMAKE_SOURCE_DIR}/src/Utils/Response/Response.cpp
    ${CMAKE_SOURCE_DIR}/src/Client/Game/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/Utils/Network/Network.cpp
)
if (WIN32)
    add_executable(${NAME_SERVER} ${SERVER_SOURCES})
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${NAME_SERVER} PRIVATE Boost::asio)
    target_link_libraries(${NAME_SERVER} PRIVATE JsonCpp::JsonCpp)
    target_link_libraries(${NAME_SERVER} PRIVATE ${NAME_LIB_UTILS})
    target_link_libraries(${NAME_SERVER} PRIVATE ${NAME_LIB_CMD})
    target_link_libraries(${NAME_SERVER} PRIVATE ${NAME_LIB})
else()
    add_executable(${NAME_SERVER} ${SERVER_SOURCES})
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${NAME_SERVER} PRIVATE Boost::asio)
    target_link_libraries(${NAME_SERVER} PRIVATE jsoncpp)
    target_link_libraries(${NAME_SERVER} PRIVATE ${NAME_LIB_UTILS})
    target_link_libraries(${NAME_SERVER} PRIVATE ${NAME_LIB_CMD})
    target_link_libraries(${NAME_SERVER} PRIVATE ${NAME_LIB})
endif()
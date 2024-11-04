set(TEST_NAME "r-type_tests")

set(TEST_SOURCES
    MainTest.cpp
    ECS/Entity/EntityManager.cpp
    Utils/Protocol.cpp
)

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} PRIVATE doctest::doctest)
target_link_libraries(${TEST_NAME} PUBLIC ${RTYPE})
target_link_libraries(${TEST_NAME} PUBLIC "Utils")

add_test(NAME RTypeTests COMMAND ${TEST_NAME})

target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_compile_options(${TEST_NAME} PRIVATE
    -Wall
)

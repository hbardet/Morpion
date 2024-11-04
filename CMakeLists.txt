cmake_minimum_required(VERSION 3.19)

project(R-Type VERSION 1.0)
set(RTYPE "MorpionXOX")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

add_compile_options(-g)
add_link_options(-g)

if (WIN32)
    set(CMAKE_GENERATOR "Visual Studio 17 2022")
    set(CMAKE_GENERATOR_PLATFORM "x64")
    add_definitions(-D_WIN32_WINNT=0x0601)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FS")
    else()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    endif()
else()
    set(CMAKE_GENERATOR "Unix Makefiles")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

find_package(boost_asio CONFIG REQUIRED)
find_package(doctest REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)

if (NOT DEFINED RAYLIB_CPP_VERSION)
    set(RAYLIB_CPP_VERSION v5.0.2)
endif()

include(FetchContent)
FetchContent_Declare(
    raylib_cpp
    GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
    GIT_TAG ${RAYLIB_CPP_VERSION}
)
FetchContent_MakeAvailable(raylib_cpp)

add_subdirectory(src/ECS)
add_subdirectory(src/Utils)
add_subdirectory(src/Command)
add_subdirectory(src/Client)
add_subdirectory(src/Server)

enable_testing()
add_subdirectory(tests)

find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY}")
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*;-header-filter=.*;-warnings-as-errors=*")
else()
    message(WARNING "clang-tidy not found")
endif()

# Afficher le type de build
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

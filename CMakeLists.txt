cmake_minimum_required(VERSION 3.16)
project(left4dead)

# GoogleTest requires at least C++17

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -Werror -pedantic -Wno-reorder")
# debugging flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline ")
# threads
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# SDL
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lSDL2_image -lSDL2_ttf") # -lSDL2_ttf -lSDL2_gfx")

# Qt UI
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS REQUIRED Core)
find_package(Qt5 COMPONENTS REQUIRED Widgets)
find_package(yaml-cpp)

# SDL2

#find_package(SDL2 REQUIRED)

#set(SDL2_IMAGE_INCLUDE_DIRS /usr/include/SDL2)
#set(SDL2_IMAGE_LIBRARIES /usr/lib/libSDL2_image.so)
#include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# ASSETS
add_custom_target(assets_target ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
  COMMENT "Copiando assets"
)

set(ASSETS_DIR ${CMAKE_BINARY_DIR}/assets)

# COMMON
include_directories(${PROJECT_SOURCE_DIR}/Common)
include_directories(${PROJECT_SOURCE_DIR}/Common/Communication)
include_directories(${PROJECT_SOURCE_DIR}/Common/Configuration)
include_directories(${PROJECT_SOURCE_DIR}/Common/Defines)
include_directories(${PROJECT_SOURCE_DIR}/Common/Event)
include_directories(${PROJECT_SOURCE_DIR}/Common/Exception)
include_directories(${PROJECT_SOURCE_DIR}/Common/GameStructure)
include_directories(${PROJECT_SOURCE_DIR}/Common/Snapshot)
include_directories(${PROJECT_SOURCE_DIR}/Common/Thread)

add_subdirectory("Common")

# SERVER
include_directories(${PROJECT_SOURCE_DIR}/Server/src)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/Acceptor)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/CommunicationThreads)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/GameThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/GameWorld)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/Protocol)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/GameWorld/Collision)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/GameWorld/Infected)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/GameWorld/Player)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/GameWorld/Weapon)


add_subdirectory("Server/src")

# CLIENT
include_directories(${PROJECT_SOURCE_DIR}/Client/src)
include_directories(${PROJECT_SOURCE_DIR}/Client/src/ClientProtocol)
include_directories(${PROJECT_SOURCE_DIR}/Client/src/CommunicationThreads)
include_directories(${PROJECT_SOURCE_DIR}/Client/src/Game)
include_directories(${PROJECT_SOURCE_DIR}/Client/src/GameThread)
include_directories(${PROJECT_SOURCE_DIR}/Client/src/Launcher)
include_directories(${PROJECT_SOURCE_DIR}/Client/src/Sdl)
add_subdirectory("Client/src")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

#EJECUTABLES
add_executable(server "Server/main.cpp")
target_link_libraries(server server_classes common_classes yaml-cpp)

add_executable(client "Client/main.cpp")
target_link_libraries(client client_classes common_classes SDL2 SDL2_image SDL2_ttf yaml-cpp)

# add_executable(testprotocol "Testing/testprotocol.cpp" )
# target_link_libraries(testprotocol server_classes client_classes common_classes)

# target_link_libraries(
#   testprotocol
#   GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(testprotocol)

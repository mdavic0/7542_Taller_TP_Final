project(left4dead)

cmake_minimum_required(VERSION 3.16)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# Flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -Werror -pedantic -Wno-reorder")
# debugging flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline ")
# threads
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# COMMON
include_directories(${PROJECT_SOURCE_DIR}/Common)
add_subdirectory("Common")

# SERVER
include_directories(${PROJECT_SOURCE_DIR}/Server/src)
add_subdirectory("Server/src")

# CLIENT
include_directories(${PROJECT_SOURCE_DIR}/Client/src)
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


# EJECUTABLES
add_executable(server "Server/main.cpp")
target_link_libraries(server server_classes common_classes)

add_executable(client "Client/main.cpp")
target_link_libraries(client client_classes common_classes)

#add_executable(testprotocol "Testing/testprotocol.cpp" )
#target_link_libraries(testprotocol server_classes client_classes common_classes)

#target_link_libraries(
#  testprotocol
#  GTest::gtest_main
#)

#include(GoogleTest)
#gtest_discover_tests(testprotocol)
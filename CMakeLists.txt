project(Testing)

cmake_minimum_required(VERSION 3.16)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  testprotocol
  testprotocol.cpp
  server_protocol.cpp
  server_protocol.h
  client_protocol.cpp
  client_protocol.h
  common_event.h
  common_eventdto.cpp
  common_eventdto.h
  common_snapshot.cpp
  common_snapshot.h
  common_socket.cpp
  common_socket.h
)
target_link_libraries(
  testprotocol
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(testprotocol)
project(left4dead)

FILE(GLOB_RECURSE myFiles *.cpp *.h)

add_library(client_classes ${myFiles})

find_package(Qt5 REQUIRED COMPONENTS Widgets)

target_link_libraries(client_classes Qt5::Widgets client)

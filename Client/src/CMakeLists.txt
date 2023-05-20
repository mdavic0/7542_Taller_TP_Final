project(left4dead)

FILE(GLOB_RECURSE myFiles *.cpp *.h)

add_library(client_classes ${myFiles})

target_link_libraries(client_classes Qt5::Widgets Qt5::Core client)

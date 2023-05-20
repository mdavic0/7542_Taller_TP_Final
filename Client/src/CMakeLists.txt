project(left4dead)

FILE(GLOB_RECURSE myFiles *.cpp *.h)

add_library(client_classes ${myFiles})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(client_classes
                        Qt5::Widgets
                        Qt5::Core
                        ${SDL2_LIBRARIES}
                        ${SDL2_IMAGE_LIBRARIES}
                        client)

project(left4dead)

add_subdirectory(launcher)
add_subdirectory(sdl)

FILE(GLOB_RECURSE myFiles *.cpp *.h)

add_library(client_classes ${myFiles})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(client_classes
                        Qt5::Widgets
                        Qt5::Core
                        ${SDL2_LIBRARIES}
                        ${SDL2_IMAGE_LIBRARIES}
                        launcher sdlLibrary)
target_include_directories(client_classes PUBLIC launcher sdlLibrary)
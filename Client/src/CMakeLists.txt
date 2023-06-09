project(left4dead)

add_subdirectory(Launcher)
add_subdirectory(Sdl)

FILE(GLOB_RECURSE myFiles *.cpp *.h)

add_library(client_classes ${myFiles})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(client_classes
                        Qt5::Widgets
                        Qt5::Core
                        ${SDL2_LIBRARIES}
                        ${SDL2_IMAGE_LIBRARIES}
                        ${SDL2_TTF_LIBRARIES}
                        launcher sdlLibrary)
target_include_directories(client_classes PUBLIC launcher sdlLibrary)
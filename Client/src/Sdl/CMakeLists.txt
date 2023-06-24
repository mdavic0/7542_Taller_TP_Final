project(left4dead)   

FILE(GLOB_RECURSE myFiles *.cpp *.h)

add_library(sdlLibrary ${myFiles})

target_link_libraries(sdlLibrary SDL2 SDL2_image SDL2_ttf SDL2_mixer)


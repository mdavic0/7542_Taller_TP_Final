project(left4dead)   

FILE(GLOB_RECURSE myFiles *.cpp *.h)

add_library(launcher ${myFiles})

target_include_directories(launcher PUBLIC ../Sdl)

target_link_libraries(launcher Qt5::Widgets Qt5::Core)

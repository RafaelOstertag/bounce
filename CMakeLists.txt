cmake_minimum_required(VERSION 3.10)

# set the project name
project(Bounce VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -pedantic -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-g0 -O3 -Wall -pedantic -Werror -DNDEBUG")

include(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf)

add_executable(bounce src/bounce.cxx src/window.cxx src/renderer.cxx src/ball.cxx src/text.cxx src/sdl.cxx src/outlinerenderer.cxx)
target_compile_options(bounce PRIVATE ${SDL2_CFLAGS_OTHER})
target_include_directories(bounce PRIVATE "${PROJECT_BINARY_DIR}" PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(bounce ${SDL2_LIBRARIES} )

configure_file(config.h.in config.h)

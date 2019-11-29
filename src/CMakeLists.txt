
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf)

add_executable(bounce bounce.cxx window.cxx renderer.cxx ball.cxx text.cxx sdl.cxx outlinerenderer.cxx solidrenderer.cxx wall.cxx pointgeom.cxx)
target_compile_options(bounce PRIVATE ${SDL2_CFLAGS_OTHER})
target_include_directories(bounce PRIVATE "${PROJECT_BINARY_DIR}" PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(bounce ${SDL2_LIBRARIES} )

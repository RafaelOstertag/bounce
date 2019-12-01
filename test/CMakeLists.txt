enable_testing()

pkg_check_modules(CPPUNIT REQUIRED cppunit)

add_executable(pointgeom pointgeom.cxx ${PROJECT_SOURCE_DIR}/src/pointgeom.cxx)
target_compile_options(pointgeom PRIVATE ${CPPUNIT_CFLAGS_OTHER})
target_include_directories(pointgeom PRIVATE "${PROJECT_SOURCE_DIR}/src" PUBLIC ${CPPUNIT_INCLUDE_DIRS})
target_link_libraries(pointgeom ${CPPUNIT_LIBRARIES})

add_test(NAME pointgeom COMMAND pointgeom)

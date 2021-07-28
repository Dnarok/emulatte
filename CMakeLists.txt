cmake_minimum_required(VERSION 3.21.0 FATAL_ERROR)

project(emulatte)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(ExternalProject)
ExternalProject_Add(spdlog
    PREFIX spdlog
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/spdlog
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_INSTALL_PREFIX=${STAGING_DIR}
    -DSPDLOG_BUILD_SHARED=OFF
)

set(SOURCE_FILES source/main.cpp)
set(HEADER_FILES include/emulatte/fundamentals.hpp
                 include/emulatte/cpu.hpp)

add_executable(emulatte ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(emulatte spdlog)
target_include_directories(emulatte PUBLIC ${STAGING_DIR}/include/
                                    PUBLIC ${PROJECT_SOURCE_DIR}/include/emulatte/)
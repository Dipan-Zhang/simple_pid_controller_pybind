cmake_minimum_required(VERSION 3.16)

project(pid_controller 
    VERSION 0.1.0
    DESCRIPTION "simple controller for visualization"
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
        message(FATAL_ERROR "GCC version must be at least 9.0!")
    endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
        message(FATAL_ERROR "Clang version must be at least 9.0!")
    endif()
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

find_package(rg-dynamics REQUIRED)

add_subdirectory(src)

option(BUILD_PYTHON_INTERFACE "Build Python interface" OFF)
if(BUILD_PYTHON_INTERFACE)
	add_subdirectory(interfaces)
    message(INFO "Build with python API")
endif()

install(
    FILES
        ${PROJECT_SOURCE_DIR}/include/pid_controller.hpp
    DESTINATION 
        ${CMAKE_INSTALL_PREFIX}/include
)



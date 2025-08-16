cmake_minimum_required(VERSION 4.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cppmenu)

add_executable(cppmenu src/simple.cpp)
target_include_directories(cppmenu PUBLIC
	"${PROJECT_BINARY_DIR}")

find_package(PkgConfig REQUIRED)

# List of required packages
set(REQUIRED_PACKAGES
gtkmm-4.0)

pkg_check_modules(DEPS REQUIRED ${REQUIRED_PACKAGES})

include_directories(${DEPS_INCLUDE_DIRS})
target_link_libraries(cppmenu ${DEPS_LIBRARIES})

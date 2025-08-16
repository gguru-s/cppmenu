cmake_minimum_required(VERSION 4.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cppmenu)

add_executable(cppmenu src/simple.cpp)
target_include_directories(cppmenu PUBLIC
	"${PROJECT_BINARY_DIR}")

set(GTK_LAYER_SHELL_INCLUDE_DIR "/usr/include/gtk4-layer-shell/")
set(GTK_LAYER_SHELL_LIBRARY "/usr/lib/libgtk4-layer-shell.so")

find_package(PkgConfig REQUIRED)

# List of required packages
set(REQUIRED_PACKAGES
gtkmm-4.0)

pkg_check_modules(DEPS REQUIRED ${REQUIRED_PACKAGES})

include_directories(${DEPS_INCLUDE_DIRS}
${GTK_LAYER_SHELL_INCLUDE_DIR})
target_link_libraries(cppmenu ${DEPS_LIBRARIES}
${GTK_LAYER_SHELL_LIBRARY})

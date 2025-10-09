cmake_minimum_required(VERSION 4.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cppmenu)

file(GLOB_RECURSE SRCFILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(cppmenu ${SRCFILES})

find_package(PkgConfig REQUIRED)

set(REQUIRED_PACKAGES
gtk4-layer-shell-0
gtkmm-4.0)

pkg_check_modules(DEPS REQUIRED ${REQUIRED_PACKAGES})

target_include_directories(cppmenu PRIVATE
"./include/"
${DEPS_INCLUDE_DIRS}
)

target_link_libraries(cppmenu
	${DEPS_LIBRARIES}
)

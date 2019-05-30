cmake_minimum_required (VERSION 3.4)
project(TSDemux)

set (TSDemux_VERSION_MAJOR 0)
set (TSDemux_VERSION_MINOR 1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_SUPPRESS_REGENERATION true)
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "ts-demux")

file(GLOB_RECURSE HEADER_FILES "src/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(ts-demux
	${SOURCE_FILES}
	${HEADER_FILES})

target_include_directories(ts-demux PRIVATE
	src)

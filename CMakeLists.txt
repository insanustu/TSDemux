cmake_minimum_required (VERSION 3.4)
project(TSDemux)

set (TSDemux_VERSION_MAJOR 0)
set (TSDemux_VERSION_MINOR 1)
set (CMAKE_CXX_STANDARD 11)


add_executable(ts-demux
	src/main.cpp
	src/m2tsextractor.cpp
	src/M2TSProcessor.cpp
    src/ElementaryStreamData.cpp
	src/util.cpp)

target_include_directories(ts-demux PUBLIC
	src)

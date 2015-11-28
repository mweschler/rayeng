# CMakeLists files in this project can

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
set (SOURCES redeng_Win32.cpp)
set (HEADERS core.h)

cmake_minimum_required (VERSION 3.0)
project (RAYENG)
add_executable(RayEng WIN32 ${SOURCES} ${HEADERS})

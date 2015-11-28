# CMakeLists files in this project can
cmake_minimum_required (VERSION 3.0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
set (SOURCES redeng_Win32.cpp re_win32GDI.cpp raygame.cpp)
set (HEADERS core.h redeng_platform.h re_win32GDI.h raygame.h)

project (RAYENG)
add_executable(RayEng WIN32 ${SOURCES} ${HEADERS})
target_link_libraries(RayEng gdi32.lib)
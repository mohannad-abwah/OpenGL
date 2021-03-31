cmake_minimum_required(VERSION 3.19)
project(learnopengl)

set(CMAKE_CXX_STANDARD 20)

add_executable(learnopengl main.cpp "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/src/glad.c")

find_package(OpenGL REQUIRED)
target_link_libraries(learnopengl glfw3 OpenGL::GL)
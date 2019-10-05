cmake_minimum_required(VERSION 3.8)
#project(glad)

#set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)

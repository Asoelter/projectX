set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm

project(util)

add_library (util          handmade_util.h
             image_reader.h image_reader.cpp)

set_property(TARGET util PROPERTY CXX_STANDARD 17)

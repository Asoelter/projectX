set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm

add_library (util          handmade_util.h
             image_reader.h image_reader.cpp)

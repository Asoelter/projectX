set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm

add_library (util          handmade_util.h
             file_reader.h file_reader.cpp)

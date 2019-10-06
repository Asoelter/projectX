set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm
project(core)


add_library (core graphics/shader.h graphics/shader.cpp
                  graphics/window.h graphics/window.cpp
                  graphics/square.h graphics/square.cpp
                  audio/speaker.h   audio/speaker.cpp)

find_package(OpenAL REQUIRED)
if(OPENAL_FOUND)
    message("OPENAL FOUND")
    include_directories(${OPENAL_INCLUDE_DIR})
    target_link_libraries(core ${OPENAL_LIBRARY})
    message(${OPENAL_LIBRARY})
else()
    message("OPENAL NOT FOUND")
endif(OPENAL_FOUND)

include_directories(../)
include_directories(../vendor/glad)
include_directories(../vendor/glad/include)
include_directories(../vendor/glfw)
include_directories(../vendor/glfw/include)

target_link_libraries(core glad)
target_link_libraries(core glfw)

target_include_directories(core PUBLIC ../vendor/glad)
target_include_directories(core PUBLIC ../vendor/glad/include)
target_include_directories(core PUBLIC ../vendor/glfw)

set_property(TARGET core PROPERTY CXX_STANDARD 17)

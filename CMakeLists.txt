cmake_minimum_required(VERSION 2.8)
project(SDLTest)

# Use C++11, enable all warnings and compile in debug mode
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# Add any definitions here
#set(SDL2_INCLUDE_DIRS "C:/Users/Kevin/ClionProjects/sdl2/include/SDL2")
#set(SDL2_LIBRARIES "-LC:/Users/Kevin/ClionProjects/sdl2/lib -lmingw32 -lSDL2main -lSDL2")

# Find packages
find_package(SDL2 REQUIRED)

# Find include and library paths here

# Global include directories

# sdl-example target
# Find all source files in the below directory automatically
file(GLOB_RECURSE SOURCE_FILES)

add_executable(SDLTest main.cpp ${SOURCE_FILES})
target_include_directories(SDLTest PUBLIC . ${SDL2_INCLUDE_DIRS})
target_link_libraries(SDLTest ${SDL2_LIBRARIES})

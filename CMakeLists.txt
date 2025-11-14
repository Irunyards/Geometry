cmake_minimum_required(VERSION 3.10)
project(GeometryPackage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics)

# Add the geometry library
add_library(geometry STATIC geometry.cpp)
target_include_directories(geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} /opt/homebrew/opt/sfml@2/include)

# Add the executable
add_executable(GeometryApp main.cpp)

# Link the executable to SFML and our geometry library
target_link_libraries(GeometryApp geometry sfml-graphics sfml-window sfml-system)

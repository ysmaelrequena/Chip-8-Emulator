cmake_minimum_required(VERSION 3.16) # Arch ships modern CMake
project(8chip LANGUAGES C)

# Make all warnings visible and strict (good practice in C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Add our source files
file(GLOB SRC_FILES src/*.c)

# Create the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Add include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Find SDL3 package
find_package(SDL3 REQUIRED)

# Link SDL3 to our emulator
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

cmake_minimum_required(VERSION 3.16)
project(Kepler LANGUAGES CXX)

# Enforce C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include source directory
include_directories(${CMAKE_SOURCE_DIR}/src)

# === Define the Kepler Library ===
file(GLOB_RECURSE KEPLER_SRC
    "src/kepler/**/*.cpp"
)

add_library(kepler STATIC ${KEPLER_SRC})
target_include_directories(kepler PUBLIC src)

# Optional: enable warnings and strictness
target_compile_options(kepler PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)

# === Example Executable (galah builder) ===
add_executable(galah_builder src/kepler/examples/galah_builder.cpp)
target_link_libraries(galah_builder PRIVATE kepler)

# === Optional Testing ===
enable_testing()

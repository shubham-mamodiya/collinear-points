cmake_minimum_required(VERSION 3.20)
# --- AI generated --- 
project(CollinearPoints LANGUAGES CXX)

# ---- Create executable ----
add_executable(collinear-points)

# ---- Source files ----
target_sources(collinear-points
    PRIVATE
        src/main.cpp
        src/collinear.cpp
)

# ---- Include directories ----
target_include_directories(collinear-points
    PRIVATE
        src
)

# ---- Use modern C++ ----
target_compile_features(collinear-points PRIVATE cxx_std_20)

# ---- Warnings (always on) ----
target_compile_options(collinear-points PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# ---- Debug-only settings (sanitizers) ----
target_compile_options(collinear-points PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

target_link_options(collinear-points PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

# ---- Optional: cleaner output (puts binary in build/) ----
set_target_properties(collinear-points PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

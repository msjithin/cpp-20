# 1. Set the Minimum Required Version (3.10 is often enough for modern C++)
cmake_minimum_required(VERSION 3.10)

# 2. Define the Project
project(Concepts_prj LANGUAGES CXX)

# 3. Set C++ Standard to C++20
# CMAKE_CXX_STANDARD is the most common way to set the language version.
set(CMAKE_CXX_STANDARD 20)

# 4. Enforce the standard (i.e., disable compiler extensions)
# Set to OFF to ensure strict adherence to the C++20 standard, 
# similar to how you implicitly want to use 'g++' in your Makefile.
set(CMAKE_CXX_EXTENSIONS OFF) 

# --- Setting Compiler Flags ---

# 5. Set global or target-specific compiler flags
# This uses 'target_compile_options' for your executable/library
# to add the warning and concept depth flags.

# Assuming your main executable is named 'main' and uses 'main.cpp'
add_executable(main main.cpp)

# Add your specific compiler flags to the target
target_compile_options(main PRIVATE
    -ltbb 
    -DPARALLEL
    -Wall
    -Wextra
    -fconcepts-diagnostics-depth=2
)
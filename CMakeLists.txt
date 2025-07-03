# Use 3.19 or later for CMakePresets.json support.
cmake_minimum_required(VERSION 3.19.0)

# CXX is C++. When I tried to use the latter,
# I would get errors about missing CMake modules.
project(cppsort VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) # Or 14, 17, 20, etc.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Disable compiler-specific extensions (optional)

add_executable(cppsort bubble.cpp common.cpp heap.cpp insertion.cpp main.cpp managed_dynamic_array.cpp merge.cpp quick.cpp selection.cpp stopwatch.cpp)
# gcc on Linux needs to be linked to the math
# library to prevent issues building stopwatch
# target_link_libraries(cppsort PRIVATE m)

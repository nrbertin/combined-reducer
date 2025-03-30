cmake_minimum_required(VERSION 3.14)

if(Kokkos_ENABLE_CUDA STREQUAL "On")
    set(CMAKE_CXX_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/kokkos/bin/nvcc_wrapper)
endif()

project(CombinedReducer LANGUAGES CXX)
add_subdirectory(kokkos)
add_executable(combined_reducer combined_reducer.cpp)
target_link_libraries(combined_reducer PRIVATE Kokkos::kokkos)


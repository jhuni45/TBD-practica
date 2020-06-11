# collect source files

cmake_minimum_required(VERSION 2.8)
find_package(CUDA)
find_package(OpenCV REQUIRED)
file( GLOB  hdr *.hpp *.h )
file( GLOB  cu  *.cu)
SET (global_op_files main.cpp)

CUDA_ADD_EXECUTABLE(global_op ${global_op_files} ${hdr} ${cu})
target_link_libraries(global_op ${OpenCV_LIBS})
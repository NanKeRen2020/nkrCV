# cmakelists: std_sanqi_xj_server

cmake_minimum_required (VERSION 3.8)

project (nkr_demo VERSION 1.0.0)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(OpenCV_DIR /home/seeking/Downloads/opencv-3.4.2/install/share/OpenCV)

find_package (OpenCV REQUIRED)
include_directories (${OpenCV_INCLUDE_DIRS})

if(UNIX)
    include_directories ("/usr/local/include/opencv" "/usr/local/include/opencv2")
    link_directories("/usr/local/lib")
    link_directories("/usr/local/cuda/lib64")
    # to install opencv go with the bash here: https://github.com/milq/milq/blob/master/scripts/bash/install-opencv.sh
endif()

SET(PLATFORM_COMPILE_FLAGS "-march=native")
SET(COMMON_COMPILE_FLAGS "-fopenmp ")
SET(CMAKE_CXX_FLAGS "${PLATFORM_COMPILE_FLAGS} ${COMMON_COMPILE_FLAGS} $ENV{CXXFLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(UNIX)
    set(BOOST_LIBRARYDIR "/usr/local/lib")
    find_package(Boost REQUIRED COMPONENTS system filesystem thread)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    set(Boost_USE_STATIC_LIBS ON)
    find_package(Boost 1.68.0 REQUIRED COMPONENTS system filesystem thread)
    include_directories ("$ENV{BOOST_ROOT}")
    link_directories ("$ENV{BOOST_ROOT}/lib64-msvc-14.1")
endif()

include_directories (${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIR} "./utils")


# icp for refine
option(USE_CUDA "use cuda or not" OFF)
if(USE_CUDA)
set(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda-10.2)
add_definitions(-DCUDA_ON)
endif()


add_executable (test_match_location test_match_location.cpp )
target_link_libraries (test_match_location  ${CMAKE_CURRENT_SOURCE_DIR}/libs/libnkrcv.a  ${OpenCV_LIBS}  -ldl -lstdc++fs -lboost_serialization -lboost_system -lboost_filesystem)




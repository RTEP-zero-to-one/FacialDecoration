cmake_minimum_required(VERSION 3.21)
project(FacialDecorationTracing)

set(CMAKE_CXX_STANDARD 14)

# execute configuration
add_executable(UnitTest
        UnitTest/test_function.cpp
        ConsoleApplication1/ConsoleApplication1/global_variable.h
        ConsoleApplication1/ConsoleApplication1/img_process.cpp
        ConsoleApplication1/ConsoleApplication1/img_process.h)
add_executable(FacialDecoration
        ConsoleApplication1/ConsoleApplication1/main.cpp
        ConsoleApplication1/ConsoleApplication1/face_detect.h
        ConsoleApplication1/ConsoleApplication1/face_detect.cpp
        ConsoleApplication1/ConsoleApplication1/global_variable.h
        ConsoleApplication1/ConsoleApplication1/cascade.cpp
        ConsoleApplication1/ConsoleApplication1/cascade.h)

# opencv configuration
set(OpenCV_DIR C:\\opencv\\mbuild\\install\\x64\\mingw\\lib)  # opencv lib in Windows
#set(OpenCV_DIR C:\\opencv\\opencv\\build\\x64\\vc14\\lib)  # opencv lib in Windows
#set(OpenCV_DIR /opt/homebrew/Cellar/opencv/4.5.4_3/lib)  # opencv lib in Ubuntu
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(FacialDecoration ${OpenCV_LIBS})
target_link_libraries(UnitTest ${OpenCV_LIBS})

# gTest configuration
#add_subdirectory(./googletest-release-1.11.0)
#set(GTEST_LIBS
#        gtest
#        pthread)
target_link_libraries(UnitTest gtest pthread)

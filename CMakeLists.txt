cmake_minimum_required(VERSION 3.21)
project(FacialDecorationTracing)

set(CMAKE_CXX_STANDARD 14)

include_directories(test_demos)

add_executable(FacialDecorationTracing
        test_demos/video_stream_demo.cpp
        test_demos/video_stream_demo.h)
add_executable(ConsoleApplication1
        ConsoleApplication1/ConsoleApplication1/ConsoleApplication1.cpp
        ConsoleApplication1/ConsoleApplication1/face_detect.h
        ConsoleApplication1/ConsoleApplication1/face_detect.cpp
        ConsoleApplication1/ConsoleApplication1/global_variable.h)

#set(OpenCV_DIR C:\\opencv\\mbuild\\install\\x64\\mingw\\lib)  # opencv lib in Windows
set(OpenCV_DIR /opt/homebrew/Cellar/opencv/4.5.4_3/lib)  # opencv lib in Mac
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(FacialDecorationTracing ${OpenCV_LIBS})
target_link_libraries(ConsoleApplication1 ${OpenCV_LIBS})
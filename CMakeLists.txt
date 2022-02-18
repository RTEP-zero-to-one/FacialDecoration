cmake_minimum_required(VERSION 3.21)
project(FacialDecorationTracing)

set(CMAKE_CXX_STANDARD 14)

include_directories(test_demos)

add_executable(FacialDecorationTracing
        test_demos/video_stream_demo.cpp
        test_demos/video_stream_demo.h)
add_executable(ConsoleApplication1
        ConsoleApplication1/ConsoleApplication1/main.cpp
        ConsoleApplication1/ConsoleApplication1/face_detect.h
        ConsoleApplication1/ConsoleApplication1/face_detect.cpp
        ConsoleApplication1/ConsoleApplication1/global_variable.h)

add_executable(UnitTest
        test_demos/test_function.cpp)


set(googleTestDir ./googletest-release-1.11.0)
add_subdirectory(${googleTestDir})
include_directories(${googleTestDir}/googletest/include)
include_directories(${googleTestDir}/googlemock/include)

set(SOURCE_FILE
        ConsoleApplication1/ConsoleApplication1/img_process.cpp
        )
add_executable(GTest ${SOURCE_FILE})

# Link with GoogleTest
target_link_libraries(GTest gtest gtest_main)
#Link with GoogleMock
target_link_libraries(GTest gmock gmock_main)


#set(OpenCV_DIR C:\\opencv\\mbuild\\install\\x64\\mingw\\lib)  # opencv lib in Windows
set(OpenCV_DIR /opt/homebrew/Cellar/opencv/4.5.4_3/lib)  # opencv lib in Mac
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(FacialDecorationTracing ${OpenCV_LIBS})
target_link_libraries(ConsoleApplication1 ${OpenCV_LIBS})
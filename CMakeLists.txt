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
        ConsoleApplication1/ConsoleApplication1/global_variable.h)
add_executable(QtTest
        QtApplication/main.cpp)

# opencv configuration
set(OpenCV_DIR C:\\opencv\\mbuild\\install\\x64\\mingw\\lib)  # opencv lib in Windows
#set(OpenCV_DIR /opt/homebrew/Cellar/opencv/4.5.4_3/lib)  # opencv lib in Ubuntu
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(FacialDecoration ${OpenCV_LIBS})
target_link_libraries(UnitTest ${OpenCV_LIBS})

# gTest configuration
add_subdirectory(./googletest-release-1.11.0)
set(GTEST_LIBS
        gtest
        pthread)
target_link_libraries(UnitTest ${GTEST_LIBS})

# Qt configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib/cmake)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
target_link_libraries(QtTest Qt5::Core Qt5::Gui Qt5::Widgets)
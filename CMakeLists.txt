cmake_minimum_required(VERSION 3.21)
project(FacialDecorationTracing)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# execute configuration
add_executable(UnitTest
        UnitTest/test_function.cpp
        ImageProcess/global_variable.h
        ImageProcess/filter_process.cpp
        ImageProcess/filter_process.h)
add_executable(FacialDecoration
        QtApplication/main.cpp
        QtApplication/mainWindow.cpp
        QtApplication/mainWindow.h
        ImageProcess/face_detect.h
        ImageProcess/face_detect.cpp
        ImageProcess/global_variable.h
        ImageProcess/cascade.cpp
        ImageProcess/cascade.h
        ImageProcess/filter_process.cpp
        ImageProcess/filter_process.h)

# opencv configuration
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OpenCV_DIR C:\\opencv\\mbuild\\install\\x64\\mingw\\lib)  # opencv lib in Windows
endif ()
#set(OpenCV_DIR /opt/homebrew/Cellar/opencv/4.5.4_3/lib)  # opencv lib in Ubuntu
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(FacialDecoration ${OpenCV_LIBS})
target_link_libraries(UnitTest ${OpenCV_LIBS})

# gTest configuration
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_subdirectory(./googletest-release-1.11.0)
    set(GTEST_LIBS
            gtest
            pthread)
    target_link_libraries(UnitTest ${GTEST_LIBS})
else ()
    target_link_libraries(UnitTest gtest pthread)
endif ()

# Qt configuration
set(CMAKE_PREFIX_PATH C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib/cmake)
target_link_libraries(FacialDecoration Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(FacialDecoration ${OpenCV_LIBS})
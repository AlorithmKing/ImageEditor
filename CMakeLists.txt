cmake_minimum_required(VERSION 3.24)
project(ImageEditor)

set(CMAKE_CXX_STANDARD 20)


FIND_PACKAGE(OpenCV REQUIRED)


add_executable(testFormat testFormat.cpp ImgFormatConv.h ImgFormatConv.cpp)

add_executable(testResize ImgOperation.cpp ImgOperation.h  testResize.cpp ImgFormatConv.h ImgFormatConv.cpp)

TARGET_LINK_LIBRARIES(testFormat ${OpenCV_LIBS})

TARGET_LINK_LIBRARIES(testResize ${OpenCV_LIBS})

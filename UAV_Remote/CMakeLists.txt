cmake_minimum_required(VERSION 3.17)
project(UAV_Remote)

set(CMAKE_CXX_STANDARD 14)

add_executable(UAV_Remote main.cpp AutoPilot.cpp AutoPilot.h Networking.cpp Networking.h ImageProcessing.cpp ImageProcessing.h GrabFrame.cpp GrabFrame.h ControlSys.cpp ControlSys.h)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(UAV_Remote ${OpenCV_LIBS})
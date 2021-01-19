cmake_minimum_required(VERSION 3.5)

project(uav LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        GrabFrame.cpp
        GrabFrame.h
        AutoPilot.cpp
        AutoPilot.h
        ControlSys.cpp
        ControlSys.h
        ImageProcessing.cpp
        ImageProcessing.h
        Networking.cpp
        Networking.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(uav
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(uav SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(uav
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include_directories(${OpenCV_INCLUDE_DIRS})

#target_link_libraries(uav ${OpenCV_LIBS})

target_link_libraries(uav PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})

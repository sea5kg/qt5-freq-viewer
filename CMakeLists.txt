cmake_minimum_required(VERSION 3.5)

project(qt5-freq-viewer VERSION 0.1 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${qt5-freq-viewer_SOURCE_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        "./src/main.cpp"
        "./src/qt5freqviewer.cpp"
        "./src/qt5freqviewer.h"
        "./ui/qt5freqviewer.ui"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt5-freq-viewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(qt5-freq-viewer
        ${PROJECT_SOURCES}
    )
endif()

include_directories(
    "./src"
)

target_link_libraries(qt5-freq-viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(qt5-freq-viewer PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt5-freq-viewer)
endif()

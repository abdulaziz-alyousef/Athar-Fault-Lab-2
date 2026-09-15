cmake_minimum_required(VERSION 3.21)

project(
    AtharFaultLab2
    VERSION 2.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(
    QT
    NAMES Qt6 Qt5
    REQUIRED
    COMPONENTS
        Widgets
        Sql
)

find_package(
    Qt${QT_VERSION_MAJOR}
    REQUIRED
    COMPONENTS
        Widgets
        Sql
)

if(WIN32)
    enable_language(RC)
endif()

set(ATHAR_SOURCES
    src/main.cpp

    src/simulation/Fault.cpp
    src/simulation/Fault.h

    src/simulation/Service.cpp
    src/simulation/Service.h

    src/simulation/SimulationEngine.cpp
    src/simulation/SimulationEngine.h

    src/ui/MainWindow.cpp
    src/ui/MainWindow.h

    src/ui/SplashScreen.cpp
    src/ui/SplashScreen.h

    src/ui/Dashboard.cpp
    src/ui/Dashboard.h

    src/ui/FaultPanel.cpp
    src/ui/FaultPanel.h

    src/ui/MetricsPanel.cpp
    src/ui/MetricsPanel.h

    src/ui/NetworkView.cpp
    src/ui/NetworkView.h

    src/ui/HistoryPanel.cpp
    src/ui/HistoryPanel.h

    src/ui/ReportsPanel.cpp
    src/ui/ReportsPanel.h

    src/ui/UiLanguage.h

    src/storage/HistoryManager.cpp
    src/storage/HistoryManager.h
)

if(WIN32)
    list(
        APPEND
        ATHAR_SOURCES
        resources/athar.rc
    )
endif()

add_executable(
    AtharFaultLab2
    WIN32
    ${ATHAR_SOURCES}
)

target_link_libraries(
    AtharFaultLab2
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
)

if(WIN32)
    target_link_libraries(
        AtharFaultLab2
        PRIVATE
            dwmapi
    )
endif()

set_target_properties(
    AtharFaultLab2
    PROPERTIES
        WIN32_EXECUTABLE TRUE
        OUTPUT_NAME "Athar Fault Lab 2"
)
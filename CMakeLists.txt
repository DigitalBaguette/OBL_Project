cmake_minimum_required(VERSION 3.16)
project(OBL_Project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Sql
    Network
    Charts
    Test
)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(LOGIC_SOURCES
    src/core/NetworkProposal.cpp
    src/core/NetworkProposal.h
    src/core/CompanyProfile.cpp
    src/core/CompanyProfile.h
    src/core/NetworkAnalyzer.cpp
    src/core/NetworkAnalyzer.h

    src/llm/OllamaClient.cpp
    src/llm/OllamaClient.h
    src/llm/PromptBuilder.cpp
    src/llm/PromptBuilder.h

    src/storage/DatabaseManager.cpp
    src/storage/DatabaseManager.h
    src/storage/JsonSerializer.cpp
    src/storage/JsonSerializer.h
)

set(GUI_SOURCES
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/MainWindow.ui
    src/gui/CompanyInputDialog.cpp
    src/gui/CompanyInputDialog.h
    src/gui/CompanyInputDialog.ui


    src/gui/HistoryWidget.cpp
    src/gui/HistoryWidget.h
    src/gui/StatsView.cpp
    src/gui/StatsView.h
)

qt_add_executable(OBL_Project
    MANUAL_FINALIZATION
    src/main.cpp
    ${LOGIC_SOURCES}
    ${GUI_SOURCES}
    src/gui/NetworkResultWidget.h
    src/gui/NetworkResultWidget.cpp
)

target_link_libraries(OBL_Project PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::Charts
)

enable_testing()

add_executable(TestAnalyzer
    tests/TestAnalyzer.cpp
    tests/TestAnalyzer.h
    ${LOGIC_SOURCES}
)

target_link_libraries(TestAnalyzer PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::Test
)

add_test(NAME AnalyzerTest COMMAND TestAnalyzer)

set_target_properties(OBL_Project PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

qt_finalize_executable(OBL_Project)
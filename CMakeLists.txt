cmake_minimum_required(VERSION 3.16)
project(OBL_Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Pakiety Qt
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Sql
    Network
)

# 2. Inkluzje
include_directories(${CMAKE_SOURCE_DIR}/include)

# 3. Definicja źródeł (Tylko raz wymieniamy każdy plik!)
set(PROJECT_SOURCES
    src/main.cpp

    # GUI
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/MainWindow.ui
    src/gui/CompanyInputDialog.cpp
    src/gui/CompanyInputDialog.h
    src/gui/CompanyInputDialog.ui
    src/gui/NetworkResultWidget.cpp
    src/gui/NetworkResultWidget.h
    src/gui/NetworkResultWidget.ui
    src/gui/HistoryWidget.cpp
    src/gui/HistoryWidget.h
    src/gui/HistoryWidget.ui

    # Core
    src/core/NetworkProposal.cpp
    src/core/NetworkProposal.h
    src/core/CompanyProfile.cpp
    src/core/CompanyProfile.h
    src/core/NetworkAnalyzer.cpp
    src/core/NetworkAnalyzer.h

    # LLM
    src/llm/OllamaClient.cpp
    src/llm/OllamaClient.h
    src/llm/PromptBuilder.cpp
    src/llm/PromptBuilder.h

    # Storage
    src/storage/DatabaseManager.cpp
    src/storage/DatabaseManager.h
    src/storage/JsonSerializer.cpp
    src/storage/JsonSerializer.h
)

# 4. Tworzenie pliku wykonywalnego (Korzystamy z PROJECT_SOURCES)
qt_add_executable(OBL_Project
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# 5. Linkowanie bibliotek Qt
target_link_libraries(OBL_Project PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
)

# 6. Konfiguracja właściwości
set_target_properties(OBL_Project PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# 7. Finalizacja
qt_finalize_executable(OBL_Project)
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
    Test  # Wymagane do testów jednostkowych
)

# 2. Inkluzje
include_directories(${CMAKE_SOURCE_DIR}/src)

# 3. Definicja źródeł aplikacji (bez main.cpp dla łatwiejszego testowania)
set(APP_SOURCES
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

# 4. Tworzenie głównego pliku wykonywalnego
qt_add_executable(OBL_Project
    MANUAL_FINALIZATION
    src/main.cpp
    ${APP_SOURCES}
)

# 5. Linkowanie bibliotek Qt dla głównego projektu
target_link_libraries(OBL_Project PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::Test
)

# 6. KONFIGURACJA TESTÓW JEDNOSTKOWYCH (Ocena 5.0)
# Definiujemy osobny plik wykonywalny dla testów
enable_testing()

add_executable(TestAnalyzer
    tests/TestAnalyzer.cpp
    ${APP_SOURCES} # Test potrzebuje dostępu do logiki NetworkAnalyzer i NetworkProposal
)

target_link_libraries(TestAnalyzer PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::Test
    Qt6::Sql
)

add_test(NAME AnalyzerTest COMMAND TestAnalyzer)

# 7. Konfiguracja właściwości
set_target_properties(OBL_Project PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# 8. Finalizacja
qt_finalize_executable(OBL_Project)
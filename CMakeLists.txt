cmake_minimum_required(VERSION 3.16)
project(OBL_Project VERSION 1.0 LANGUAGES CXX)

# Standardowe ustawienia Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Pakiety Qt (Usunięto Charts dla lepszej kompatybilności)
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Sql
    Network
    Test
)

# 2. Katalogi nagłówkowe
include_directories(${CMAKE_SOURCE_DIR}/src)

# 3. Definicja źródeł LOGIKI (Współdzielone między aplikacją a testami)
# @note Rozdzielenie logiki od GUI ułatwia testowanie jednostkowe (Wymóg 5.0)
set(LOGIC_SOURCES
    # Core - modele danych i logika biznesowa
    src/core/NetworkProposal.cpp
    src/core/NetworkProposal.h
    src/core/CompanyProfile.cpp
    src/core/CompanyProfile.h
    src/core/NetworkAnalyzer.cpp
    src/core/NetworkAnalyzer.h

    # LLM - komunikacja z modelem Ollama
    src/llm/OllamaClient.cpp
    src/llm/OllamaClient.h
    src/llm/PromptBuilder.cpp
    src/llm/PromptBuilder.h

    # Storage - warstwa trwałości danych (SQLite + JSON)
    src/storage/DatabaseManager.cpp
    src/storage/DatabaseManager.h
    src/storage/JsonSerializer.cpp
    src/storage/JsonSerializer.h
)

# 4. Definicja źródeł GUI (Usunięto StatsView)
set(GUI_SOURCES
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
)

# 5. Główny cel binarny
qt_add_executable(OBL_Project
    MANUAL_FINALIZATION
    src/main.cpp
    ${LOGIC_SOURCES}
    ${GUI_SOURCES}
)

# Linkowanie bibliotek (Usunięto Qt6::Charts)
target_link_libraries(OBL_Project PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
)

# 6. Automatyczne testy jednostkowe
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

# 7. Właściwości systemowe
set_target_properties(OBL_Project PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

qt_finalize_executable(OBL_Project)
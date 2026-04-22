cmake_minimum_required(VERSION 3.16)
project(OBL_Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Pakiety Qt - wymagane Widgets i Network do komunikacji z Ollama [cite: 93]
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# 2. Inkluzje (jeśli masz dodatkowe biblioteki w folderze include)
include_directories(${CMAKE_SOURCE_DIR}/include)

# 3. Lista plików źródłowych z użyciem ścieżek absolutnych [cite: 93, 94]
set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

    # GUI [cite: 6]
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/MainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/MainWindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/CompanyInputDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/CompanyInputDialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/CompanyInputDialog.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/NetworkResultWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/NetworkResultWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/NetworkResultWidget.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/HistoryWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/HistoryWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/HistoryWidget.ui

    # Core (Logika biznesowa) [cite: 4]
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NetworkProposal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NetworkProposal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/CompanyProfile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/CompanyProfile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NetworkAnalyzer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NetworkAnalyzer.h

    # LLM (Ollama / Qwen 2.5) [cite: 4]
    ${CMAKE_CURRENT_SOURCE_DIR}/src/llm/OllamaClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/llm/OllamaClient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/llm/PromptBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/llm/PromptBuilder.h

    # Storage (JSON Database) [cite: 5]
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storage/DatabaseManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storage/DatabaseManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storage/JsonSerializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storage/JsonSerializer.h
)

# 4. Tworzenie pliku wykonywalnego
qt_add_executable(OBL_Project
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    src/gui/MainWindow.cpp
    src/gui/mainwindow.h src/gui/mainwindow.cpp
    src/gui/MainWindow.h
    src/gui/MainWindow.cpp
    src/llm/OllamaClient.h
    src/llm/OllamaClient.cpp
    src/gui/CompanyInputDialog.ui
    src/gui/CompanyInputDialog.h
    src/gui/CompanyInputDialog.cpp

    src/gui/HistoryWidget.cpp
    src/gui/HistoryWidget.h
    src/gui/HistoryWidget.ui
    src/core/NetworkProposal.cpp
    src/core/NetworkProposal.h
    src/core/CompanyProfile.cpp
    src/core/CompanyProfile.h
    src/core/NetworkAnalyzer.cpp
    src/core/NetworkAnalyzer.h
    src/llm/PromptBuilder.cpp
    src/llm/PromptBuilder.h
    src/storage/DatabaseManager.cpp
    src/storage/DatabaseManager.h
    src/storage/JsonSerializer.cpp
    src/storage/JsonSerializer.h


)

# 5. Linkowanie bibliotek Qt 
target_link_libraries(OBL_Project PRIVATE
    Qt6::Widgets
    Qt6::Network
)

# 6. Konfiguracja pod Windows/macOS 
set_target_properties(OBL_Project PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 7. Testy i Dokumentacja
enable_testing()
# add_subdirectory(tests) # Odkomentuj, gdy stworzysz folder tests z CMakeLists.txt

# 8. Instalacja [cite: 95]
include(GNUInstallDirs)
install(TARGETS OBL_Project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(OBL_Project)
# Network Analysis Tool (OBL Project)

System automatycznej analizy projektów sieciowych wykorzystujący lokalne modele LLM.

## Funkcje
- Integracja z Ollama (Llama 3.2)
- Asynchroniczny zapis historii do bazy SQLite (JSON)
- Wielowątkowa architektura (Qt Concurrent/QThread)
- Testy jednostkowe w QtTest
- Historia zapisanych propozycji z podglądem szczegółów
- Statystyki projektów (wykres liczby pracowników)

## Wymagania
- Qt6 (moduły: Widgets, Sql, Network, Charts, Test)
- CMake ≥ 3.16
- Kompilator C++17
- Zainstalowana [Ollama](https://ollama.com/) z modelem `llama3.2` (`ollama pull llama3.2`)

## Jak uruchomić? (wersja finalna)
1. Pobierz wersję finalną (https://github.com/DigitalBaguette/OBL_Project/releases)
2. Upewnij się, że masz zainstalowaną [Ollamę](https://ollama.com/) i uruchomiony model `llama3.2`
3. Uruchom `OBL_Project.exe`

## Jak zbudować ze źródeł?
```bash
git clone https://github.com/DigitalBaguette/OBL_Project.git
cd OBL_Project
cmake -B build -S .
cmake --build build
```
Plik wykonywalny pojawi się w katalogu `build/` (lub `build/Debug`, `build/Release` — zależnie od generatora).

## Jak uruchomić testy jednostkowe?
Projekt zawiera testy w QtTest (target `TestAnalyzer`, plik `tests/TestAnalyzer.cpp`).

Z linii poleceń:
```bash
cmake --build build --target TestAnalyzer
ctest --test-dir build -R AnalyzerTest --output-on-failure
```

W Qt Creator: przełącz aktywny target na `TestAnalyzer` (Projects → Build & Run) i uruchom przyciskiem Run.

## Obsługa błędów
Projekt obsługuje błędy zgodnie z konwencją frameworka Qt (kody powrotu, sygnały błędów typu `errorOccurred`/`operationFinished`), zamiast mechanizmu C++ exceptions — jest to zgodne z wielowątkową architekturą aplikacji, w której błędy muszą bezpiecznie przechodzić między wątkiem GUI a wątkiem bazy danych.

## Dokumentacja
Pełna dokumentacja techniczna (Doxygen) dostępna jest tutaj: https://digitalbaguette.github.io/OBL_Project/
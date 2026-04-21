# 🤖 File Manager (Qt C++ & AI)

Aplikacja okienkowa napisana w C++ (Qt 6), która wykorzystuje lokalne modele sztucznej inteligencji (LLM) do automatyzacji operacji na plikach. Program tłumaczy polecenia użytkownika w języku naturalnym na skrypty w języku Python i bezpiecznie je wykonuje.

## 🚀 Funkcjonalności
* **Asynchroniczne zapytania REST API:** Komunikacja z serwerem Ollama w tle (bez blokowania interfejsu użytkownika).
* **Bezpieczne wykonywanie kodu:** Zastosowanie `QProcess` do odpalania wygenerowanych skryptów Python z pełnym przechwytywaniem błędów (Standard Output / Error).
* **Responsywne GUI:** Interfejs oparty o Layouty i płynny pasek postępu.
* **Architektura pod testy:** Logika wydzielona do funkcji statycznych.
* **Automatyczne testy:** Skonfigurowany moduł testów jednostkowych (`QtTest`) w osobnym targecie CMake.

## 🛠 Wymagania systemowe
Aby poprawnie skompilować i uruchomić projekt, potrzebujesz:
1. **Qt Creator** (z zestawem narzędzi MinGW 64-bit oraz Qt 6+).
2. **CMake** (ustawiony jako główny system budowania).
3. **Python 3** (dodany do zmiennej środowiskowej PATH).
4. **Ollama** z pobranym modelem językowym (domyślnie w kodzie ustawiony jest model `llama3`).

## ⚙️ Jak uruchomić?
1. Uruchom serwer Ollama w tle (`ollama run llama3`).
2. Sklonuj to repozytorium.
3. Otwórz plik `CMakeLists.txt` w środowisku Qt Creator.
4. Wybierz cel (Target) `FileAssistant` i kliknij *Zbuduj*, a następnie *Uruchom*.

## 🧪 Uruchamianie testów
Projekt zawiera osobny cel budowania dla testów jednostkowych. Aby je uruchomić, zmień w lewym dolnym rogu Qt Creatora cel budowania z `FileAssistant` na `UnitTests` i kliknij *Uruchom*. Wyniki pojawią się w logach aplikacji.
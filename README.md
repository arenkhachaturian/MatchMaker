# MatchMakingApp

## Overview

MatchMakingApp is a Qt-based application designed to manage users and games, providing matchmaking functionality for players. It features a robust engine, intuitive UI, and a modular architecture to ensure scalability and maintainability.

Key features include:
- A **user dashboard** with filtering and sorting options.
- Management of **games** and **users**, including adding and removing entries.
- **Matchmaking engine** to pair users based on specific criteria.
- **Testable architecture** with unit tests for critical components.
- Cross-platform compatibility leveraging **CMake** and **Qt**.

---

## Project Structure

### **1. Engine**
Contains the core logic for users, games, and matchmaking:
- **User Management:** Classes like `User`, `UserPoolManager`, and `UserRegistry`.
- **Game Management:** Classes like `Game`, `GameExecutor`, and `GameRegistry`.
- **Matchmaking:** Implements algorithms to pair users effectively using `MatchmakingEngine`.

### **2. Models**
Defines data models for application components:
- `UserTableModel`: Manages user data in a table format.
- `DashboardModel` and `DashboardSerializer`: Handle serialization and data manipulation for the dashboard.

### **3. Viewers**
Implements the graphical user interface:
- `UserTableWidget`: Displays user information with filtering and sorting.
- `DashboardWidget`: Provides an overview of users and games.
- Dialogs for adding/removing users: `AddUserDialog` and `RemoveUserDialog`.

### **4. IO**
Handles file operations for persistent storage:
- `JsonIOHandler`: Reads and writes user and game data to/from JSON files.
- Environment variable replacements (e.g., `{GAME_DIR}`) for portable paths.

### **5. Tests**
Unit tests for core modules, ensuring reliability and correctness:
- Includes test cases for users, games, JSON handling, matchmaking, and registries.

---

## Platform Support

- **Windows:** Fully supported with all features and tests available.
- **Linux:** Currently in progress, with future updates planned to ensure compatibility.

---

## Configuration

The project uses CMake for build configuration and testing.

### **Key Variables**
- `DB_DIR`: Directory for storing user and game data (`app_data/`).
- `GAME_EXEC_DIR`: Directory containing game executables (`games/`).
- `USER_DATA_FILE`: Path to the user data file (`app_data/user_data.json`).
- `GAME_DATA_FILE`: Path to the game data file (`app_data/game_data.json`).
- `TEST_DIR`: Directory for test resources (enabled in Debug mode).
- `TEST_GAMES_DIR`: Directory containing test game executables (`tests/games/`).

These variables are dynamically injected into configuration headers (`config.h` and `test_config.h`).

---

## Dependencies

### **Required Libraries**
- **Qt**: Core functionality is built using Qt Widgets and Qt Test.
- **C++17**: Modern C++ features for cleaner, more efficient code.

### **Build Requirements**
- **CMake 3.16+**
- **Qt6 (preferred) or Qt5**: Widgets and Test modules are required.

---

## Build Instructions

### **1. Clone the Repository**
```bash
git https://github.com/arenkhachaturian/MatchMaker.git
cd MatchMakingApp

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make

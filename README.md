# Simple SQLite User Manager in C

This is a simple command-line tool built in C using `sqlite3` for managing user data.

## Features

- Add user (name, height, info)
- List all users
- Search user by exact name

## Technologies

- C
- SQLite3
- vcpkg (for dependency management on Windows)

---

## 📦 Installing SQLite3 using `vcpkg` on Windows

1. **Clone vcpkg** (if you haven't already):

```bash
git clone https://github.com/microsoft/vcpkg
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install sqlite3:x64-windows
.\vcpkg integrate install
```

## Compilation

- Open the project in Visual Studio and build.
- Or, from the command line:

```bash
cl sqlite_input.c /link sqlite3.lib
```

## Usage

1. Run the program: `.\sqlite_input`
2. Choose an option:
   - 1: Add a new user (enter name, height, info).
   - 2: List all users with their details.
   - 3: Search for a user by name to see their details.
   - 4: Exit the program.

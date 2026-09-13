# Smart Student Placement Management System

A modular C project for managing student placements, built phase by phase
using standard C only (no C++, no external libraries, no database).

## Status: Phase 0 + Phase 1 Complete
- Project skeleton and folder structure
- Build system (Makefile)
- Shared constants (`include/constants.h`)
- Generic binary file handling (`filehandler.c/.h`)
- Input validation helpers (`validation.c/.h`)
- Small utility helpers (`utils.c/.h`)
- Minimal `main.c` proving all modules compile and link correctly

## Folder Structure
```
placement-management-system/
├── src/        Implementation (.c) files
├── include/    Header (.h) files
├── data/       Binary data files (persistent storage)
├── reports/    Generated text reports
├── backup/     Backup copies of data/
├── tests/      Test files
├── README.md
└── Makefile
```

## Requirements
- MinGW GCC installed and added to your system PATH
- `mingw32-make` (comes with most MinGW installs) OR run gcc commands manually

## Build & Run (Windows, MinGW)
```
mingw32-make
placement_system.exe
```

If you don't have `make` installed, compile manually:
```
gcc -Wall -Wextra -std=c11 -Iinclude -c src/filehandler.c -o obj/filehandler.o
gcc -Wall -Wextra -std=c11 -Iinclude -c src/main.c -o obj/main.o
gcc -Wall -Wextra -std=c11 -Iinclude -c src/utils.c -o obj/utils.o
gcc -Wall -Wextra -std=c11 -Iinclude -c src/validation.c -o obj/validation.o
gcc obj/*.o -o placement_system.exe
placement_system.exe
```

## Clean Build Artifacts
```
mingw32-make clean
```

# Compiler settings
CXX = g++  # The C++ compiler to use (g++)
CXXFLAGS = -I"C:/PDCurses-master" -L"C:/PDCurses-master/wincon" -lpdcurses -std=c++11 -Wall -Wextra
# CXXFLAGS includes:
# -I: Specifies the directory for PDCurses header files (e.g., curses.h).
# -L: Specifies the directory for the compiled PDCurses library.
# -lpdcurses: Links the PDCurses library for terminal handling.
# -std=c++11: Enables C++11 features.
# -Wall, -Wextra: Enables warnings for debugging.

# Source files needed to compile the project
SRCS = 2048.cpp modele.cpp menu.cpp ai.cpp
# SRCS is a variable that lists all the C++ source files required to build the game.

# Name of the final executable
EXEC = 2048
# EXEC specifies the name of the output executable file.

# Default target: builds the game executable
all: $(EXEC)
# The "all" target is the default when you run "make".
# It depends on the $(EXEC) target (the game executable).
# Rule to build the game executable
$(EXEC):
	$(CXX) $(SRCS) -o $(EXEC) $(CXXFLAGS)
# This rule builds the executable $(EXEC) (i.e., 2048) using:
# - $(CXX): The compiler (g++).
# - $(SRCS): All source files (2048.cpp, modele.cpp, etc.).
# - -o $(EXEC): Specifies the name of the output file (2048).
# - $(CXXFLAGS): Includes compiler flags for PDCurses and warnings.

# Rule to clean up generated files
clean:
	rm -f $(EXEC)
# The "clean" target removes the built executable to allow a clean rebuild.
# - rm -f: Deletes the file $(EXEC) (2048) without error if the file doesn’t exist.

# Declaring phony targets
.PHONY: all clean
# "all" and "clean" are declared as phony targets, meaning they are commands
# and not associated with any real files. This avoids conflicts if files named
# "all" or "clean" exist in the directory.

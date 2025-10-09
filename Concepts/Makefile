# --- Variables ---
# The compiler to use for C++ source files
CXX = g++

# The standard compiler flags:
# -std=c++20: Enables the C++20 standard
# -Wall -Wextra: Enables common warnings (good practice)
# -fconcepts-diagnostics-depth=1: Sets the verbosity for concept failures
CXXFLAGS = -std=c++20 -Wall -Wextra -fconcepts-diagnostics-depth=2

# The name of the final executable
TARGET = basics

# The source file(s)
SRC = basics.cpp

# The object file(s) - derived from the source files
OBJ = $(SRC:.cpp=.o)

# --- Targets ---

# Default target: builds the executable from object files
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Generic rule to compile a .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target: removes generated files
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJ)
# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Define the target executable
TARGET = myapp

# Define source and object files
SRCDIR = src
OBJDIR = obj
INCDIR = inc
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Include directories
INC = -I$(INCDIR)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

# Create directories if they don't exist
$(shell mkdir -p $(OBJDIR))

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean

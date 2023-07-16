CC := g++
CFLAGS := -std=c++17 -Wall -Wextra
SRCDIR := src
OBJDIR := obj
BINDIR := bin
TARGET := myprogram

# List of source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Default target
all: $(BINDIR)/$(TARGET)

# Rule to build the target executable
$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile each source file into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated object files and the executable
clean:
	@rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
# Compiler
CXX := g++

# FLTK compiler flags
FLTK_CXXFLAGS := $(shell fltk-config --cxxflags)

# FLTK linker flags
FLTK_LDFLAGS := $(shell fltk-config --ldflags)

# Source files
SOURCES := main.cpp

# Object files
OBJECTS := $(SOURCES:.cpp=.o)

# Executable
EXECUTABLE := wmlogout

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(FLTK_LDFLAGS) -o $@
	strip $@
	rm -f $(OBJECTS)

%.o: %.cxx
	$(CXX) $(FLTK_CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

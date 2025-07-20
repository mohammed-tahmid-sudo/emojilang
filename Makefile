# Simple Makefile for emojilang C++ version

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = $(BUILDDIR)/emojilang

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $(OBJECTS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

help:
	@echo "Available targets:"
	@echo "  all     - Build the emojilang interpreter"
	@echo "  clean   - Remove build files"
	@echo "  install - Install to /usr/local/bin/"
	@echo "  help    - Show this help message"

# Run tests
test: $(TARGET)
	@echo "Running test files..."
	@for file in tests/*.emo; do \
		echo "Testing $$file..."; \
		$(TARGET) $$file; \
	done

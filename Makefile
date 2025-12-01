CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
TARGET = banking_system
SRCDIR = .
OBJDIR = build
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET) bank_data.txt

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

install:
	@echo "Banking System compiled successfully!"
	@echo "Run 'make run' to start the application"
	@echo "Run 'make clean' to clean build files"

help:
	@echo "Available targets:"
	@echo "  all     - Build the banking system (default)"
	@echo "  clean   - Remove build files and data"
	@echo "  run     - Build and run the application"
	@echo "  debug   - Build with debug symbols"
	@echo "  help    - Show this help message"
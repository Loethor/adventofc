# Compiler and base flags
CC = gcc
CFLAGS_COMMON = -O3 -pedantic -std=c99 -Wall -Wextra -I./common

# Set YEAR and DAY as prerequisites for defining SRC_DIR and CFLAGS
YEAR ?= 
DAY ?= 

# Derived variables
SRC_DIR = $(YEAR)/day$(DAY)/src
SRC_FILE = $(SRC_DIR)/day$(DAY).c
OUTPUT_EXE = day$(DAY)_solution.exe
CFLAGS = $(CFLAGS_COMMON) -I$(SRC_DIR)

# Default target: show usage
all:
	@echo "Usage: make run YEAR=YYYY DAY=DD"
	@echo "       make test YEAR=YYYY DAY=DD"

# Check if YEAR and DAY are set
check-args:
	@if [ -z "$(YEAR)" ] || [ -z "$(DAY)" ]; then \
		echo "Error: Please specify YEAR and DAY (e.g., make run YEAR=2024 DAY=1)"; \
		exit 1; \
	fi

# Validate source file existence
check-src:
	@if [ ! -f "$(SRC_FILE)" ]; then \
		echo "Error: Solution source file $(SRC_FILE) not found."; \
		exit 1; \
	fi

# Run the solution for a specific year and day
run: check-args check-src
	$(CC) $(CFLAGS) -o $(OUTPUT_EXE) $(SRC_FILE) common/utils.c
	@echo "Running solution for Year $(YEAR), Day $(DAY):"
	./$(OUTPUT_EXE)

# Clean all executables
clean:
	rm -f day*_solution

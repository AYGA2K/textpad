BUILD_DIR     := build
TARGET        := textpad
CMAKE_PRESET  := conan-ninja-release
CONAN_FLAGS   := -s build_type=Release -s compiler.cppstd=gnu20

.PHONY: run all deps configure build clean help

EXE := $(BUILD_DIR)/$(TARGET)

run: build
	./$(EXE)

all:
	conan install . --output-folder=$(BUILD_DIR) --build=missing $(CONAN_FLAGS)
	cmake --preset $(CMAKE_PRESET)
	cmake --build --preset $(CMAKE_PRESET)
	./$(EXE)

deps:
	conan install . --output-folder=$(BUILD_DIR) --build=missing $(CONAN_FLAGS) 

config: deps
	cmake --preset $(CMAKE_PRESET)

build:
	cmake --build --preset $(CMAKE_PRESET)

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "make / make run   - build + run ./$(EXE) (default)"
	@echo "make all          - conan install, configure, build, run (first-time / after clean)"
	@echo "make deps         - conan install only"
	@echo "make config       - deps + cmake --preset $(CMAKE_PRESET)"
	@echo "make build        - compile only"
	@echo "make clean        - remove $(BUILD_DIR)/"

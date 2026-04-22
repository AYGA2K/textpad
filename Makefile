BUILD_DIR := build
BINARY    := $(BUILD_DIR)/textpad

.PHONY: setup build run clean

all: build run

setup:
	cmake -S . -B $(BUILD_DIR) -G "Ninja"

build:
	cmake --build $(BUILD_DIR) --parallel

run: build
	$(BINARY)

clean:
	rm -rf $(BUILD_DIR)

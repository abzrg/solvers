BUILD_DIR := build

all:
	cmake --build $(BUILD_DIR)

test:
	ctest --test-dir $(BUILD_DIR)

clean:
	cmake --build $(BUILD_DIR) --target $@

.PHONY: all test clean

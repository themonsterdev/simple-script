.PHONY: all

# Default target
all: macos windows

macos:
	@echo "Building for macOS..."
	cmake --preset mac-os-debug

windows:
	@echo "Building for Windows..."
	cmake --preset windows-debug

build-macos:
	@echo "Building for macOS..."
	cmake --build --preset mac-os-debug

build-windows:
	@echo "Building for Windows..."
	cmake --build --preset windows-debug

all: cmake

run:
	cd build && ./Engine

cmake: build
	cd build && cmake .. -GNinja
	cd build && ninja

build:
	mkdir -p build

clean:
	rm -rf build

.PHONY: cmake clean all
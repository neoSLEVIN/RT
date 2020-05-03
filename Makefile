all: build run

build:
	@cmake --build ./cmake-build-debug --target RT -- -j 4

run:
	@./cmake-build-debug/RT.exe

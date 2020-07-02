OS := $(shell uname)

ifeq ($(OS),Darwin)
  EXECUTE = RT
else
  EXECUTE = RT.exe
endif

all: build run

build:
	@cmake --build ./cmake-build-debug --target RT -- -j 4

run:
	@./cmake-build-debug/$(EXECUTE)

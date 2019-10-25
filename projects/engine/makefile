COMPILER=g++
CFLAGS=-std=c++11 -I./src -I./src/include -g -lGL -lglfw -lX11 -lpthread -ldl
FILES=./src/ ./src/game.cpp ./src/glad.c ./src/fileio/open.cpp ./src/io/input.cpp ./src/rendersystem/camera.cpp ./src/rendersystem/glerrors.cpp ./src/rendersystem/opengltoucher.cpp ./src/rendersystem/textures/texturesystem.cpp ./src/rendersystem/shaders/shaderprogram.cpp ./src/rendersystem/shaders/shadersystem.cpp ./src/rendersystem/camera.cpp

default:
	$(COMPILER) -o engine.so $(FILES) $(CFLAGS)

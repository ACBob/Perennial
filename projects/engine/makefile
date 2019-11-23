COMPILER=g++
CFLAGS=-std=c++11 -I./src -I./src/include -g -lGL -lglfw -lX11 -lpthread -ldl -fPIC -shared
FILES=src/p_main.cpp src/rendersystem.cpp src/glad.c src/fileoperations.cpp src/shader.cpp
default:
	$(COMPILER) -o engine.so $(FILES) $(CFLAGS)

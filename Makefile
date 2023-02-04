COMPILER := g++
STD 	 := c++20
FLAGS 	 := -ggdb -Wall -Weffc++ -Wextra -Werror
INCLUDE  := -Iinclude/ -Iimgui/ -Iimgui/backends
LIB 	 := -Llib/
LIBS 	 := -lglfw3dll -lopengl32

SRC := comp/*.o src/*.cpp $(wildcard src/gui/*.cpp) src/OpenGL/**/*.cpp
# src/imgui/*.cpp


test: compile run clean
build: compile run

compile:
	@-mkdir out
	-$(COMPILER) -g --std=$(STD) $(INCLUDE) $(LIB) $(SRC) $(LIBS) -o out/main

comp_libs:
	@-mkdir comp
	-$(COMPILER) -c --std=$(STD) $(INCLUDE) $(LIB) src/glad.c src/imgui/**/*.cpp src/imgui/*.cpp $(LIBS)
	-$(COMPILER) -c --std=$(STD) $(INCLUDE) $(LIB) imgui/*.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp $(LIBS)
	mv *.o comp/

run:
	@echo ""
	./out/main $(args)

clean:
	@echo ""
	rm -f out/*.o out/*.exe

clean_all:
	@echo ""
	rm -rd out
	rm -rd comp

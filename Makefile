# OBJS_MAIN=main.cpp Snake.cpp Game.cpp Gallery.cpp SDL_utils.cpp
# OBJS_TEST_GAME=GameTest.cpp Snake.cpp Game.cpp Gallery.cpp SDL_utils.cpp
# OBJ_MAIN=main.exe
# OBJ_TEST_GAME=gameTest.exe
# COMPILER_FLAGS=-std=c++11
# LINKER_FLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image
# INCLUDE_DIR=-IC:\Users\khami\Downloads\setup\SDL2-2.0.22\x86_64-w64-mingw32\include\SDL2 -IC:\Users\khami\Downloads\setup\SDL2_image-2.0.5\x86_64-w64-mingw32\include\SDL2 -IC:\Users\khami\OneDrive\Documents\CppUnit\include
# LIB_DIR=-LC:\Users\khami\Downloads\setup\SDL2-2.0.22\x86_64-w64-mingw32\lib -LC:\Users\khami\Downloads\setup\SDL2_image-2.0.5\x86_64-w64-mingw32\lib -LC:\Users\khami\OneDrive\Documents\CppUnit\lib



# all:
# 	g++ -std=c++17 -c main.cpp $(INCLUDE_DIR)
# 	g++ -std=c++17 -c Snake.cpp $(INCLUDE_DIR)
# 	g++ -std=c++17 -c Game.cpp $(INCLUDE_DIR)
# 	g++ -std=c++17 -c Gallery.cpp $(INCLUDE_DIR)
# 	g++ -std=c++17 -c SDL_utils.cpp $(INCLUDE_DIR)
	

# 	g++ -std=c++17 Snake.o  Game.o Gallery.o SDL_utils.o GameTest.o -o main $(LIBFINCLUDE_DIRLAGS)
# 	g++ -std=c++17 -c GameTest.cpp $(INCLUDE_DIR)
# 	g++ -std=c++17 Snake.o  Game.o Gallery.o SDL_utils.o GameTest.o  -lcppunit -o $(OBJ_TEST_GAME) $(INCLUDE_DIR)

# run:
# 	g++ $(COMPILER_FLAGS) $(INCLUDE_DIR) $(LIB_DIR) $(OBJS_MAIN) $(LINKER_FLAGS) -o $(OBJ_MAIN)
# 	./$(OBJ_MAIN)
# test:
# 	g++ $(COMPILER_FLAGS) $(INCLUDE_DIR) $(LIB_DIR) $(OBJS_TEST_GAME) $(LINKER_FLAGS) -o $(OBJ_TEST_GAME)
# 	./$(OBJ_TEST_GAME)

# # @REM sudo apt-get install libsdl2-dev libsdl2-image-dev
# # @REM gcc -std=c99 -o main -Wall -Wextra -pedantic main.c -lSDL2 -lSDL2_image



LIBFLAGS = -lSDL2 -lSDL2_image
all:
	g++ -std=c++11 -c SDL_utils.cpp $(LIBFLAGS)
	g++ -std=c++11 -c Gallery.cpp $(LIBFLAGS)
	g++ -std=c++11 -c Game.cpp $(LIBFLAGS)
	g++ -std=c++11 -c Snake.cpp $(LIBFLAGS)
	g++ -std=c++11 -c main.cpp $(LIBFLAGS)

	g++ -std=c++11 SDL_utils.o  Gallery.o Game.o  Snake.o  main.o -o main $(LIBFLAGS)
	g++ -std=c++11 -c GameTest.cpp $(LIBFLAGS)
	g++ -std=c++11 SDL_utils.o  Gallery.o Game.o  Snake.o GameTest.o  -lcppunit -o GameTest $(LIBFLAGS)
run:
	chmod +x main
	./main

test:
	chmod +x GameTest
	./GameTest

clean:
	rm -rf *.o main GameTest
push:
	git add *.cpp *.h Makefile && git commit -m "test" && git push
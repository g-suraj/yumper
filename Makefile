#OBJS specifies which files to compile as part of the project
OBJS = Main.cpp WindowInit.cpp Texture.cpp Timer.cpp Gravity.cpp Ball.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -g
#
#  #LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image 
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = exe

#This is the target that compiles our executable
all: exe
exe: $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm -rf ./*.out
	rm exe

#OBJS specifies which files to compile as part of the project
OBJS = State.cpp FSM.cpp
HEADERS = State.hpp FSM.hpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -std=c++14 -Wall -Wextra

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = state

#This is the target that compiles our executable
all : $(OBJS) $(HEADERS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

clean : $(OBJ_NAME)
	rm $(OBJ_NAME)

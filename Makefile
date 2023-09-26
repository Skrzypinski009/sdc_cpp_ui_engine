CFLAGS := -lSDL2 -lSDL2_ttf -std=c++17
CC := g++

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include

INC := $(wildcard $(INC_DIR)/*.h)

_OBJ := $(subst .cpp,.o,$(wildcard $(SRC_DIR)/*.cpp))
OBJ := $(subst $(SRC_DIR),$(OBJ_DIR),$(_OBJ))

all: myapp

myapp: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o app

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm app *.o 

run: myapp
	./app

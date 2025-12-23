CC = g++

CFLAGS = -Wall -Wextra -std=c++11 -I include -g

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include


TARGET = $(BIN_DIR)/tp3.out

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

run: all
	./$(TARGET)
CC   = g++
OPTS = -O0 -std=c++17
DEBUG = -g

SRC_DIR = ./src
INCLUDE_DIR = ./include
BUILD_DIR = ./build

SRCS = $(SRC_DIR)/*.cpp

INCLUDE = $(addprefix -I,$(INCLUDE_DIR)) -I/usr/include/lua5.1/
CFLAGS = $(OPTS) $(INCLUDE) $(DEBUG)
LIBS = -L/usr/lib/x86_64-linux-gnu/ -lsfml-graphics -lsfml-window -lsfml-system -llua5.1

TARGET = procedural-dungeons

all: $(TARGET)


$(TARGET):
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

clean:
	rm -rf $(OBJS) $(BUILD_DIR)/*

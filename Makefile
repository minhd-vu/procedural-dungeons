CC   = g++
OPTS = -O0 -std=c++17 -target x86_64-apple-darwin
DEBUG = -g

SRC_DIR = ./src
INCLUDE_DIR = ./include
BUILD_DIR = ./build

SRCS = $(SRC_DIR)/*.cpp

INCLUDE = $(addprefix -I,$(INCLUDE_DIR))
CFLAGS = $(OPTS) $(INCLUDE) $(DEBUG)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = $(BUILD_DIR)/procedural-dungeons

all: $(TARGET)


$(TARGET):
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

clean:
	rm -rf $(OBJS) $(BUILD_DIR)/*

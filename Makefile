##############################################
# Makefile for Whittier College C++ projects
#
# Jeff Lutgen, 2022
##############################################

SRCS = pqueue-test.cpp pqueue-vector.cpp pqueue-linkedlist.cpp pqueue-doublylinkedlist.cpp ansi_escapes.cpp
HDRS = pqueue-vector.h pqueue-linkedlist.h pqueue-doublylinkedlist.h ansi_escapes.h
USE_TIGR = false

##############################################

TARGET = assign6

CFLAGS = -Wall
CXXFLAGS = -Wall -Wno-sign-compare -Wno-deprecated-declarations -std=c++17

ifeq ($(OS),Windows_NT)
	CC = gcc
	CXX = g++
	CFLAGS += -Wno-unknown-pragmas -Wno-unused-but-set-variable
else
	CC = clang
	CXX = clang++
endif


WCLIB = wclib
UTIL_SRC = $(WCLIB)/util.cpp
TIGR_SRC = $(WCLIB)/tigr.c

ifeq ($(USE_TIGR),true)
	TIGR_O = tigr.o
	ifeq ($(OS),Windows_NT)
		LDFLAGS = -s -lopengl32 -lgdi32
	else
		UNAME_S := $(shell uname -s)
		ifeq ($(UNAME_S),Darwin)
			LDFLAGS = -framework OpenGL -framework Cocoa
		else ifeq ($(UNAME_S),Linux)
			LDFLAGS = -s -lGLU -lGL -lX11
		endif
	endif
endif

OBJS = $(TIGR_O) util.o $(patsubst %.cpp, %.o, $(SRCS))

all: $(TARGET)

debug: CFLAGS += -g -O0
debug: CXXFLAGS += -g -O0
debug: $(TARGET)

util.o: $(UTIL_SRC)
	$(CXX) $^ -c $(CXXFLAGS)

$(TIGR_O): $(TIGR_SRC)
	$(CC) $^ -c $(CFLAGS)

%.o: %.cpp $(HDRS)
	$(CXX) $< -c -I$(WCLIB) $(CXXFLAGS)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ -I$(WCLIB) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) *.o $(TARGET) $(TARGET).exe
	$(RM) -r *.dSYM

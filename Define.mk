
HOME=/home/sosohu/workspace/DiMaria
CC=gcc
CFLAGS=-O3 -fPIC -Wformat -g
CXXFLAGS=-O3 -fPIC -Wformat --std=c++0x -DDEBUG -g
AR=ar
ARFLAGS=-r

#LIBGL=-lglut -lGLU -lGL -lm
LIBGL=
LIBS=$(LIBGL)

INC=$(HOME)/include
SRC=$(HOME)/src
LIB_PATH=$(HOME)/lib
TEST=$(HOME)/test



HOME=/home/sosohu/huqinghai/work/DiMaria
CC=gcc
CFLAGS=-O3 -fPIC
CXXFLAGS=-O3 -fPIC --std=c++0x -DDEBUG
AR=ar
ARFLAGS=-r

LIBGL=-lglut -lGLU -lGL -lm
LIBS=$(LIBGL)

INC=$(HOME)/include
SRC=$(HOME)/src
LIB_PATH=$(HOME)/lib
TEST=$(HOME)/test


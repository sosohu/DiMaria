
include $(HOME)/Define.mk

IINC=-I$(INC) -I$(INC)/core -I$(INC)/graph -I$(INC)/unix -I$(INC)/io

all:
	$(CXX) $(IINC) -o main main.cc -L$(LIB_PATH) -lmy $(LIBS) $(CXXFLAGS)

clean:
	rm -rf main

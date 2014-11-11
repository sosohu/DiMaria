include $(HOME)/Define.mk

IINC=-I$(INC)/core -I$(INC)/graph -I$(INC)/unix -I$(INC)/io

OBJS= $(patsubst %.c,%.o,$(wildcard *.c))
OBJS+= $(patsubst %.cc,%.o,$(wildcard *.cc))

all:$(OBJS) $(LIB_PATH)/libmy.a $(LIB_PATH)/libmy.so

%.o:%.c
	$(CXX) $(IINC) -c $^ $(CXXFLAGS) 
%.o:%.cc
	$(CXX) $(IINC) -c $^ $(CXXFLAGS) 

$(LIB_PATH)/libmy.so:$(OBJS)
	$(CXX) $(IINC) -fPIC -shared $^ -o $@ $(CXXFLAGS)

$(LIB_PATH)/libmy.a:$(OBJS)
	$(AR) $(ARFLAGS) $@ $^ 

clean:
	rm -rf $(OBJS)

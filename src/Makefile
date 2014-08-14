include $(HOME)/Define.mk

OBJS= $(patsubst %.c,%.o,$(wildcard *.c))

all:$(OBJS) $(LIB_PATH)/libmy.a $(LIB_PATH)/libmy.so

%.o:%.c
	$(CC) -I$(INC) -c $^ $(CFLAGS) 

$(LIB_PATH)/libmy.so:$(OBJS)
	$(CC) -I$(INC) -shared $^ -o $@ $(CFLAGS)

$(LIB_PATH)/libmy.a:$(OBJS)
	$(AR) $(ARFLAGS) $@ $^ 

clean:
	rm -rf $(OBJS)

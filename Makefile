CC = gcc
objs += src/alarm.c src/config.c src/fixed_queue.c src/list.c src/reactor.c src/semaphore.c src/thread.c src/main.c

CFLAGS += -I./include
LDLIBS += -lpthread -std=c99  -std=gnu99 -lrt
all:
	$(CC) $(objs) -o out/test $(CFLAGS) $(LDLIBS)

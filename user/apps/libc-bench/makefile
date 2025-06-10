ifeq ($(ARCH), x86_64)
	CROSS_COMPILE=x86_64-linux-musl-
else ifeq ($(ARCH), riscv64)
	CROSS_COMPILE=riscv64-linux-musl-
endif

SRCS = $(sort $(wildcard *.c))
OBJS = $(SRCS:.c=.o)

CC=$(CROSS_COMPILE)gcc

CFLAGS = -Os
LDFLAGS = -static
LIBS = -lpthread -lrt -lpthread

.PHONY: all clean test install


all: libc-bench

clean:
	rm -f $(OBJS) libc-bench

test: all
	./libc-bench

install: all
	mv libc-bench $(DADK_CURRENT_BUILD_DIR)/libc-bench

libc-bench: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
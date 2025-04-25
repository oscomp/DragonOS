ifeq ($(ARCH), x86_64)
	CROSS_COMPILE=x86_64-linux-musl-
else ifeq ($(ARCH), riscv64)
	CROSS_COMPILE=riscv64-linux-musl-
endif

CC=$(CROSS_COMPILE)gcc
SRC=$(wildcard *.c)  # 查找所有 .c 文件
BIN=$(SRC:.c=)       # 生成对应的可执行文件名

.PHONY: all install clean

all: $(BIN)

%: %.c
	$(CC) -static -o $@ $<

install: all
	mkdir -p $(DADK_CURRENT_BUILD_DIR)
	mv $(BIN) $(DADK_CURRENT_BUILD_DIR)/

clean:
	rm -f $(BIN) *.o

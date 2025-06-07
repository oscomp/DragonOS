ifeq ($(ARCH), x86_64)
	CROSS_COMPILE=x86_64-linux-musl-
else ifeq ($(ARCH), riscv64)
	CROSS_COMPILE=riscv64-linux-musl-
endif

CC=$(CROSS_COMPILE)gcc
SRC=$(wildcard *.c)                 # 查找所有 .c 文件
BIN=$(SRC:.c=)                      # 生成对应的可执行文件名
LUA_TESTS := $(wildcard lua/*.lua)  # 查找所有 Lua 测试脚本
LUA_TEST_RUNNER := $(wildcard lua/*.sh)  # Lua 测试运行脚本名称 (包含 lua_testcode.sh)

.PHONY: all install clean

all: $(BIN)

%: %.c
	$(CC) -static -o $@ $<

install: all
	mkdir -p $(DADK_CURRENT_BUILD_DIR)
	mv $(BIN) $(DADK_CURRENT_BUILD_DIR)/
	mkdir -p $(DADK_CURRENT_BUILD_DIR)/lua
	cp $(LUA_TESTS) $(LUA_TEST_RUNNER) $(DADK_CURRENT_BUILD_DIR)/lua/

clean:
	rm -f $(BIN) *.o

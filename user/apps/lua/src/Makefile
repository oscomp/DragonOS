ifeq ($(ARCH), x86_64)
    CROSS_COMPILE=x86_64-linux-musl-
else ifeq ($(ARCH), riscv64)
    CROSS_COMPILE=riscv64-linux-musl-
endif

CC = $(CROSS_COMPILE)gcc -std=gnu99
AR = $(CROSS_COMPILE)ar rcu
RANLIB = $(CROSS_COMPILE)ranlib

PLAT = linux
CFLAGS = -O2 -Wall -Wextra -DLUA_COMPAT_5_3 -DLUA_USE_LINUX -static $(MYCFLAGS)
LDFLAGS = -static $(MYLDFLAGS)
LIBS = -lm $(MYLIBS)

RM = rm -f

SYSCFLAGS =
SYSLDFLAGS =
SYSLIBS =

MYCFLAGS =
MYLDFLAGS =
MYLIBS =
MYOBJS =

CMCFLAGS = 

LUA_A = liblua.a
CORE_O = lapi.o lcode.o lctype.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o
LIB_O = lauxlib.o lbaselib.o lcorolib.o ldblib.o liolib.o lmathlib.o loadlib.o loslib.o lstrlib.o ltablib.o lutf8lib.o linit.o
BASE_O = $(CORE_O) $(LIB_O) $(MYOBJS)

LUA_T = lua
LUA_O = lua.o

LUAC_T = luac
LUAC_O = luac.o

ALL_O = $(BASE_O) $(LUA_O) $(LUAC_O)
ALL_T = $(LUA_A) $(LUA_T) $(LUAC_T)
ALL_A = $(LUA_A)

default: $(PLAT)

all: $(ALL_T)

o: $(ALL_O)

a: $(ALL_A)

$(LUA_A): $(BASE_O)
	$(AR) $@ $(BASE_O)
	$(RANLIB) $@

$(LUA_T): $(LUA_O) $(LUA_A)
	$(CC) -o $@ $(LDFLAGS) $(LUA_O) $(LUA_A) $(LIBS)

$(LUAC_T): $(LUAC_O) $(LUA_A)
	$(CC) -o $@ $(LDFLAGS) $(LUAC_O) $(LUA_A) $(LIBS)

test:
	./$(LUA_T) -v

clean:
	$(RM) $(ALL_T) $(ALL_O)

depend:
	@$(CC) $(CFLAGS) -MM l*.c

echo:
	@echo "PLAT= $(PLAT)"
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(SYSLDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

TO_BIN= lua luac

.PHONY: install uninstall

install:
	mkdir -p $(INSTALL_BIN) $(INSTALL_INC) $(INSTALL_LIB) $(INSTALL_MAN)
	cp $(TO_BIN) $(INSTALL_BIN)

uninstall:
	cd $(INSTALL_BIN) && $(RM) $(TO_BIN)

.PHONY: linux

linux: $(ALL)

llex.o:
	$(CC) $(CFLAGS) $(CMCFLAGS) -c llex.c

lparser.o:
	$(CC) $(CFLAGS) $(CMCFLAGS) -c lparser.c

lcode.o:
	$(CC) $(CFLAGS) $(CMCFLAGS) -c lcode.c

INSTALL_BIN= /bin

INSTALL= install -p
INSTALL_EXEC= $(INSTALL) -m 0755
MKDIR= mkdir -p
RM= rm -f

TO_BIN= lua luac

.PHONY: all clean install uninstall

all: build

build:
	@cd src && $(MAKE) all

install: build
	$(MKDIR) $(INSTALL_BIN)
	cd src && mv $(TO_BIN) $(DADK_CURRENT_BUILD_DIR)

uninstall:
	cd $(INSTALL_BIN) && $(RM) $(TO_BIN)

clean:
	cd src && $(MAKE) clean
	$(RM) src/*.o
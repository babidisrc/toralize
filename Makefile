BINDIR ?= /usr/bin
LIBDIR ?= /usr/lib
SCRIPT_NAME = toralize
SO_NAME = toralize.so
SRC = src/toralize.c

all:
	@echo "Use 'make build' to build the shared object file and 'sudo make install' to set up toralize for your system."

build:
	@echo "Building $(SO_NAME)..."
	gcc ${SRC} -o ${SO_NAME} -fPIC -shared -ldl -D_GNU_SOURCE
	@echo "Build complete."

install:
	@echo "Installing $(SCRIPT_NAME)..."
	install -Dm755 install.sh $(BINDIR)/$(SCRIPT_NAME)
	install -Dm644 toralize.so ${LIBDIR}/${SO_NAME}
	@echo "Installation complete."

uninstall:
	@echo "Removing $(SCRIPT_NAME)..."
	rm -f $(BINDIR)/$(SCRIPT_NAME)
	rm -f ${LIBDIR}/${SO_NAME}
	@echo "Uninstallation complete."

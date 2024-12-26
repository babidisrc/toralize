PREFIX ?= /usr/bin
SCRIPT_NAME = toralize

all:
	@echo "Use 'sudo make install' to set up toralize for your system."

install:
	@echo "Installing $(SCRIPT_NAME)..."
	install -Dm755 install.sh $(PREFIX)/$(SCRIPT_NAME)
	install -Dm644 bin/toralize.so /usr/lib/toralize.so
	@echo "Installation complete."

uninstall:
	@echo "Removing $(SCRIPT_NAME)..."
	rm -f $(PREFIX)/$(SCRIPT_NAME)
	rm -f /usr/lib/toralize.so
	@echo "Uninstallation complete."

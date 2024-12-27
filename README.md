# Toralize

**Toralize** is a lightweight utility that facilitates proxy connections via SOCKS4. Focusing on simplicity and functionality, it allows you to traverse a proxy using a shared object (`.so`) library.


## Requirements
- Linux environment.
- `gcc` or compatible compiler.
- SOCKS4-compatible proxy (default is 127.0.0.1:9050 for Tor).


## Installation

Follow these steps to install Toralize on your system:

1. Clone the repository:

```bash
git clone https://github.com/babidisrc/toralize.git
cd toralize
```

2. Create the `install.sh` script in the main folder:

```bash
#!/bin/bash

SO_PATH="/path/to/toralize/libtoralize.so"
case "$(uname)" in
    Linux*)     OS="Linux";;
    Darwin*)    OS="Mac";;
    CYGWIN*|MINGW*) OS="Windows";;
    *)          OS="Unknown";;
esac

if [ ! -f "$SO_PATH" ]; then
    echo "ERROR: Shared object file not found at $SO_PATH"
    exit 1
fi

if [ "$OS" = "Mac" ]; then
    export DYLD_INSERT_LIBRARIES="$SO_PATH"
elif [ "$OS" = "Linux" ]; then
    export LD_PRELOAD="$SO_PATH"
else
    echo "ERROR: Unsupported operating system: $OS"
    exit 1
fi

if ! "$@"; then
    echo "ERROR: Failed to execute command: $@"
    unset LD_PRELOAD DYLD_INSERT_LIBRARIES
    exit 1
fi

unset LD_PRELOAD DYLD_INSERT_LIBRARIES
```

3. Build the shared object file:

```bash
mkdir build
cd build
sudo cmake ..
sudo make
```

4. Install the library (requires root permissions):

```bash
sudo make install
```

## Usage

To use Toralize, simply prepend the toralize command to your desired application. For example:

```bash
toralize curl http://example.com
toralize firefox
```

## Acknowledgments

This project was inspired by tutorials created by Dr. Jonas Birch (2024) and Beej's Guide to Network Programming.

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

2. Build the shared object file:

```bash
make build
```

3. Create the `install.sh` script in the main folder:

```bash
#!/bin/bash
export LD_PRELOAD="path/to/toralize/toralize.so"
"$@"
unset LD_PRELOAD
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

## Uninstallation

If you need to remove Toralize from your system, run:

```bash
sudo make uninstall
```

## Acknowledgments

This project was inspired by tutorials created by Dr. Jonas Birch (2024) and Beej's Guide to Network Programming.

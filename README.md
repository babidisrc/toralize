# Toralize

**Toralize** is a lightweight utility that facilitates proxy connections via SOCKS4. Focusing on simplicity and functionality, it allows you to traverse a proxy using a shared object (`.so`) library.

### Requirements
- Linux environment.
- `gcc` or compatible compiler.
- SOCKS4-compatible proxy (default is 127.0.0.1:9050 for Tor).

## Installation
Follow these steps to install Toralize on your system:

1. Clone the repository:

```bash
git clone https://github.com/yourusername/toralize.git
cd toralize
```
3. Install the library (requires root permissions):

```bash
./toralize.sh
sudo make install
```
## Usage

To use Toralize, simply prepend the toralize command to your desired application. For example:

```bash
toralize curl http://example.com
toralize curl http://120.14.0.5
```

#!/bin/bash

SO_PATH="/usr/local/lib/libtoralize.so"
case "$(uname)" in
    Linux*)     OS="Linux";;
    Darwin*)    OS="Mac";;
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


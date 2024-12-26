#!/bin/bash

SO_PATH="$(dirname "$(realpath "$0")")/toralize.so"

if [ -f "$SO_PATH" ]; then
    export LD_PRELOAD="$SO_PATH"
fi

"$@"
unset LD_PRELOAD

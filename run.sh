#!/bin/sh

if [ ! -f build/build.ninja ]; then
    meson setup build
fi

# Only run the newly-compiled binary if the compilation succeeded
meson compile -C build && build/visort

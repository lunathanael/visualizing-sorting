#!/bin/sh

# The reason we can't just check for the existence of the directory is that
# there are times when the build directory exists and contains meson files, but
# there were errors generating the build system. Checking for compile commands
# ensures that a valid build configuration exists.
if [ ! -f build/compile_commands.json ]; then
    meson setup build
fi

meson compile -C build \
    && build/visort $@

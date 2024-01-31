#!/bin/sh

# Only run the newly-compiled binary if the compilation succeeded
meson compile -C build && build/visort

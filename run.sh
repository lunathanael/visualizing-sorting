#!/bin/sh

meson setup build \
    && meson compile -C build \
    && build/visort

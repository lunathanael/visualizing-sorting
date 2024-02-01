#!/usr/bin/env python3

import subprocess

SOURCES = ["src/main.cpp"]
HEADERS = ["include/vis/backend/bogo_sorter.hpp",
           "include/vis/backend/bubble_sorter.hpp",
           "include/vis/backend/quick_sorter.hpp",
           "include/vis/backend/sorter.hpp",
           "include/vis/frontend/sorter.hpp"]


def format_files(files: list[str]) -> None:
    subprocess.run(["clang-format", "-i", *files])


def main() -> int:
    format_files(SOURCES)
    format_files(HEADERS)
    return 0


if __name__ == "__main__":
    code = main()
    exit(code)

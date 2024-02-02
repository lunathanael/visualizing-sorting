#                                    _           _ _     _
#  _ __ ___   ___  ___  ___  _ __   | |__  _   _(_) | __| |
# | '_ ` _ \ / _ \/ __|/ _ \| '_ \  | '_ \| | | | | |/ _` |
# | | | | | |  __/\__ \ (_) | | | |_| |_) | |_| | | | (_| |
# |_| |_| |_|\___||___/\___/|_| |_(_)_.__/ \__,_|_|_|\__,_|

project('visualizing-sorting', 'cpp')

sources = files(
  'src/main.cpp',
  'src/frontend/config.cpp',
  )

headers = files(
  'include/vis/backend/bogo_sorter.hpp',
  'include/vis/backend/bubble_sorter.hpp',
  'include/vis/backend/quick_sorter.hpp',
  'include/vis/backend/sorter.hpp',
  'include/vis/frontend/config.hpp',
  'include/vis/frontend/sorter.hpp',
  )

incdirs = include_directories('include')

executable('visort', sources,
  dependencies: dependency('sfml-all'),
  include_directories: incdirs,
  )

custom_target('format',
  build_by_default: true,
  command: ['clang-format', '-i', '@INPUT@'],
  input: [sources, headers],
  output: 'stdout',
  )

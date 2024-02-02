#                                    _           _ _     _
#  _ __ ___   ___  ___  ___  _ __   | |__  _   _(_) | __| |
# | '_ ` _ \ / _ \/ __|/ _ \| '_ \  | '_ \| | | | | |/ _` |
# | | | | | |  __/\__ \ (_) | | | |_| |_) | |_| | | | (_| |
# |_| |_| |_|\___||___/\___/|_| |_(_)_.__/ \__,_|_|_|\__,_|

project('visualizing-sorting', 'cpp')

sources = files('src/main.cpp', 'src/frontend/config.cpp')
incdirs = include_directories('include')

executable('visort', sources,
  dependencies: dependency('sfml-all'),
  include_directories: incdirs)

custom_target('format',
  input: sources,
  output: 'stdout',
  command: ['clang-format', '-i', '@INPUT@'],
  build_by_default: true)

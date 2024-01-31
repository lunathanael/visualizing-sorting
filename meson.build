#                                    _           _ _     _
#  _ __ ___   ___  ___  ___  _ __   | |__  _   _(_) | __| |
# | '_ ` _ \ / _ \/ __|/ _ \| '_ \  | '_ \| | | | | |/ _` |
# | | | | | |  __/\__ \ (_) | | | |_| |_) | |_| | | | (_| |
# |_| |_| |_|\___||___/\___/|_| |_(_)_.__/ \__,_|_|_|\__,_|

project('visualizing-sorting', 'cpp')

visort_sources = [
  'src/main.cpp',
  ]

visort_incdirs = include_directories('include')

executable('visort', visort_sources,
  dependencies : dependency('sfml-all'),
  include_directories : visort_incdirs)

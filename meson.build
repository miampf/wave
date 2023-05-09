project('wave', 'cpp', default_options : ['cpp_std=c++20'])

vendor = include_directories('vendor')

subdir('wave/lib')

executable('wave-bin', 'wave/main.cpp', link_with : lib, include_directories : vendor)

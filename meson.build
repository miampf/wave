project('wave', 'cpp', default_options : ['c_std=c11', 'cpp_std=c++20'])

include_dir = include_directories(['vendor', 'wave/lib'])

wave_applib = library('wave_applib', sources : ['wave/lib/app/app.cpp', 'wave/lib/app/app.hpp'])

executable('wave', 'wave/main.cpp', include_directories : include_dir, link_with : wave_applib)


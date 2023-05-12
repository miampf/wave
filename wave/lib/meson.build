inc_lib = include_directories('.')

rtaudio = dependency('rtaudio', required : true)
spdlog = dependency('spdlog', required : true)

lib = library('wavelib', [
  'app/app.cpp',
  'app/app.hpp',
  'audio/audio.cpp',
  'audio/audio.hpp'
  ], include_directories : inc_lib, dependencies : [rtaudio, spdlog])

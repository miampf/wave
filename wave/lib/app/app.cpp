#include <spdlog/spdlog.h>
#include <iostream>

#include "../audio/audio.hpp"
#include "app.hpp"

namespace Wave {
  App::App() {}

  int App::init() {
    spdlog::info("Initializing App");

    AudioInterface audio;

    int err = audio.init();
    if (err != AudioErrors::AudioInitSuccess) {
      spdlog::error("Failed to initialize audio");
      return AppErrors::AppInitFailure;
    }

    return AppErrors::AppInitSuccess;
  }
}


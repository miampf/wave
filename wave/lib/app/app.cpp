#include <spdlog/spdlog.h>
#include "../audio/audio.hpp"

#include "app.hpp"

namespace Wave {
  App::App() {}

  void App::init() {
    spdlog::info("Initializing App");

    AudioInterface audio;

    audio.init();
  }
}


#include <rtaudio/RtAudio.h>
#include <spdlog/spdlog.h>

#include "audio.hpp"

namespace Wave {
  AudioInterface::AudioInterface() {}

  int AudioInterface::init() {
    spdlog::info("Initializing audio system");

    RtAudio audio;

    spdlog::info("Querying devices");

    std::vector<unsigned int> device_ids = audio.getDeviceIds();

    for (unsigned int i = 0; i < device_ids.size(); i++) {
      RtAudio::DeviceInfo info = audio.getDeviceInfo(device_ids[i]);

      spdlog::info("Found device #{}: {}", i, info.name);
    }

    return AudioErrors::InitSuccess;
  }
}

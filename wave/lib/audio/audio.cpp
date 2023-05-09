#include <rtaudio/RtAudio.h>
#include <spdlog/spdlog.h>

#include "audio.hpp"

namespace Wave {
  AudioInterface::AudioInterface() {}

  int AudioInterface::init() {
    spdlog::info("Initializing audio system");

    RtAudio audio;

    spdlog::info("Querying devices");

    // Determine the number of devices available
    unsigned int devices = audio.getDeviceCount();
    // Scan through devices for various capabilities
    RtAudio::DeviceInfo info;
    for ( unsigned int i=0; i<devices; i++ ) {
      info = audio.getDeviceInfo( i );
      
      spdlog::info("Found Device %s", info.name);
    }

    return AudioErrors::InitSuccess;
  }
}

#pragma once

#include <RtAudio.h>
#include <vector>

namespace Wave {
  enum AudioErrors {
    AudioInitSuccess,

    AudioInitFailure
  };

  class AudioInterface {
    private:
      RtAudio* audio;
      std::vector<unsigned int> device_ids;
      
    public:
      AudioInterface();
      ~AudioInterface();

      int init();
  };
}

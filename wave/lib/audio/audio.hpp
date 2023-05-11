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

   public:
      AudioInterface();
      ~AudioInterface();

      int init();
  };
}  // namespace Wave

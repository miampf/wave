#pragma once

namespace Wave {
  enum AudioErrors {
    InitSuccess,

    InitFailure
  };

  class AudioInterface {
    public:
      AudioInterface();

      int init();
  };
}

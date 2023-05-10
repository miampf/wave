#pragma once

namespace Wave {
  enum AppErrors {
    AppInitSuccess,

    AppInitFailure
  };

  class App {
   public:
      App();

      int init();
  };
}


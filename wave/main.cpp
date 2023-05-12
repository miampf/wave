#include "lib/app/app.hpp"

int main(int argc, char **argv) {
  Wave::App a;
  int err = a.init();

  if (err != Wave::AppErrors::AppInitSuccess) {
    return -1;
  }

  return 0;
}

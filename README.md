# Wave

A simple synthesizer for game audio. This is mainly developed for educational purposes and to get better at C/C++, so the code might be a bit spaghettied.

## Compiling from source

To compile from source, you need [meson](https://mesonbuild.com/) and the [ninja build system](https://ninja-build.org/) installed.
Furthermore, you need to install [spdlog](https://github.com/gabime/spdlog), [rtaudio](https://github.com/thestk/rtaudio) and [imgui](https://github.com/ocornut/imgui). You can do that in an arch-based linux distribution by running:

```bash
yay -S spdlog rtaudio imgui
```

Once you got that, run

```bash
meson setup build
```

to prepare your build files and

```bash
ninja -C build/
```

to compile everything. If that succeeds, you should have your binary as `build/wave`.

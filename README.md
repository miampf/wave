# Wave

A simple synthesizer for game audio. This is mainly developed for educational purposes and to get better at C/C++, so the code might be a bit spaghettied.

## Compiling from source

To compile from source, you need [meson](https://mesonbuild.com/) and the [ninja build system](https://ninja-build.org/) installed. Once you got that, run

```bash
meson setup build
```

to prepare your build files and

```bash
ninja -C build/
```

to compile everything. If that succeeds, you should have your binary as `build/wave`.

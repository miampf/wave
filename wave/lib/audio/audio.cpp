#include <rtaudio/RtAudio.h>
#include <spdlog/spdlog.h>
#include <math.h>

#include "audio.hpp"

int sinus_wave(
    void *out_buffer,
    void *in_buffer,
    unsigned int n_buffer_frames,
    double stream_time,
    RtAudioStreamStatus status,
    void *user_data) {
  if (status) {
    spdlog::error("Stream underflow detected");
  }

  double freq = 440;

  double* buffer = (double*)out_buffer;
  float* data = (float*) user_data;
  float timec = data[0];
  int sample_rate = 44100;

  for (int i = 0; i < n_buffer_frames; i++) {
    double sine = sin(2 * M_PI * freq * (timec / sample_rate));
    buffer[i] = sine;
    timec++;
  }

  return 0;
}


namespace Wave {
  AudioInterface::AudioInterface() {}
  AudioInterface::~AudioInterface() {
    int err = this->audio->stopStream();
    if (err != RTAUDIO_NO_ERROR) {
      spdlog::error("Error while stopping audio stream: {}", this->audio->getErrorText());
    }

    if (this->audio->isStreamOpen()) this->audio->closeStream();
  }

  int AudioInterface::init() {
    spdlog::info("Initializing audio system");

    this->audio = new RtAudio();

    spdlog::info("Querying devices");

    if (this->audio->getDeviceCount() < 1) {
      spdlog::error("No audio devices found");
      return AudioErrors::AudioInitFailure;
    }

    this->device_ids = this->audio->getDeviceIds();

    for (unsigned int i = 0; i < this->device_ids.size(); i++) {
      RtAudio::DeviceInfo info = this->audio->getDeviceInfo(this->device_ids[i]);

      spdlog::info("Found device #{}: {}", i, info.name);
    }

    unsigned int default_device_id = this->audio->getDefaultOutputDevice();
    spdlog::info("Using device \"{}\"", this->audio->getDeviceInfo(default_device_id).name);

    RtAudio::StreamParameters parameters;
    parameters.deviceId = default_device_id;
    parameters.nChannels = 2;
    parameters.firstChannel = 0;
    unsigned int sample_rate = 44100;
    unsigned int buffer_frames = 128;
    float timec = 0;

    float user_data[1] = {timec};

    spdlog::info("Opening stream to device");

    int err = this->audio->openStream(
        &parameters,
        nullptr,
        RTAUDIO_FLOAT64,
        sample_rate,
        &buffer_frames,
        &sinus_wave,
        (void *)&user_data);
    this->audio->startStream();

    if (err != RTAUDIO_NO_ERROR) {
      spdlog::error("Error while opening stream: {}", this->audio->getErrorText());
      return AudioErrors::AudioInitFailure;
    }

    return AudioErrors::AudioInitSuccess;
  }
}

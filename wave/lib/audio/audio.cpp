#include <rtaudio/RtAudio.h>
#include <spdlog/spdlog.h>
#include <math.h>

#include "audio.hpp"

int N = 0;

typedef struct {
  unsigned int sample_rate;
  unsigned int n_channels;
} CallbackData;

int sinus_wave(
    void* out_buffer,
    void* in_buffer,
    unsigned int n_buffer_frames,
    double stream_time,
    RtAudioStreamStatus status,
    void* user_data) {
  if (status) {
    spdlog::error("Stream underflow detected");
  }
  CallbackData* data = static_cast<CallbackData*>(user_data);
  double freq = 440;

  double* buffer = static_cast<double*>(out_buffer);
  unsigned int sample_rate = data->sample_rate;

  for (unsigned int i = 0; i < n_buffer_frames; i++) {
    for (unsigned int j = 0; j < data->n_channels; j++) {
      double sine = sin(N * 2 * M_PI * freq / sample_rate);
      *buffer++ = sine;
    }
    N++;
  }

  return 0;
}


namespace Wave {
  AudioInterface::AudioInterface() {}
  AudioInterface::~AudioInterface() {
    try {
      this->audio->stopStream();
    } catch (RtAudioError &e) {
      spdlog::error("Error while stopping audio stream");
      e.printMessage();
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
    
    unsigned int device_count = this->audio->getDeviceCount();

    for (unsigned int i = 0; i < device_count; i++) {
      RtAudio::DeviceInfo info = this->audio->getDeviceInfo(i);

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

    CallbackData data = CallbackData{sample_rate, parameters.nChannels};

    spdlog::info("Opening stream to device");

    void* data_ptr = static_cast<void*>(&data);

    try {
      this->audio->openStream(
          &parameters,
          nullptr,
          RTAUDIO_FLOAT64,
          sample_rate,
          &buffer_frames,
          &sinus_wave,
          data_ptr);
      this->audio->startStream();
    } catch (RtAudioError &e) {
      spdlog::error("Error while opening stream");
      e.printMessage();
      return AudioErrors::AudioInitFailure;
    }

    char in;
    std::cin.get(in);

    return AudioErrors::AudioInitSuccess;
  }
}

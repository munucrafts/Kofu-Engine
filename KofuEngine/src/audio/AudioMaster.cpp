#include "AudioMaster.h"

AudioMaster& AudioMaster::GetAudioMaster()
{
    static AudioMaster as;
    return as;
}

void AudioMaster::InitAudioMaster()
{
    alcDevice = alcOpenDevice(nullptr);
    alcContext = alcCreateContext(alcDevice, nullptr);

    alcMakeContextCurrent(alcContext);
    alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
}

void AudioMaster::ShutdownAudioMaster()
{
    alcMakeContextCurrent(nullptr);

    if (alcContext) alcDestroyContext(alcContext);
    if (alcDevice) alcCloseDevice(alcDevice);

    alcContext = nullptr;
    alcDevice = nullptr;
}

AudioMaster::AudioMaster()
{
    alcDevice = nullptr;
    alcContext = nullptr;
}

AudioMaster::~AudioMaster()
{
    ShutdownAudioMaster();
}

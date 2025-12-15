#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <AL/al.h>
#include <AL/alc.h>

class AudioMaster
{
public:
    static AudioMaster& GetAudioMaster();
    void InitAudioMaster();
    void ShutdownAudioMaster();

private:
    ALCdevice* alcDevice;
    ALCcontext* alcContext;

private:
    AudioMaster();
    ~AudioMaster();
};


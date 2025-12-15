#pragma once
#include <string>
#include <glm/glm.hpp>
#include <AL/al.h>
#include <AL/alc.h>

class AudioSource
{
private:
    ALuint sourceId = 0;
    ALuint buffer = 0;

public:
    AudioSource() = default;
    ~AudioSource();
    void InitAudioSource();
    void DeleteAudioSource();
    void PlayAudioSource() const;
    void LoadAudioFile(const std::string& audioPath, const glm::vec3& origin);
    void SetAudioPitch(const float pitch) const;
    void SetAudioVolume(const float volume) const;
    void SetAudioAttenuation(const float rollOffFactor, const float referenceDistance, const float maxDistance) const;
    void SetAudioOrigin(const glm::vec3& origin) const;
    void SetAudioVelocity(const glm::vec3& velocity) const;
    void PauseAudio() const;
    void ResumeAudio() const;
};


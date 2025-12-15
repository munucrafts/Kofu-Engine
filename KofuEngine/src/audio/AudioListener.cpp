#include "AudioListener.h"

AudioListener& AudioListener::GetListener()
{
    static AudioListener audioListener;
    return audioListener;
}

void AudioListener::SetListenerLocation(const glm::vec3& location) const
{
    alListener3f(AL_POSITION, location.x, location.y, location.z);
}

void AudioListener::SetListenerVelocity(const glm::vec3& velocity) const
{
    alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

void AudioListener::SetListenerOrientation(const glm::vec3& forward, const glm::vec3& up) const
{
    float orientation[6] = { forward.x, forward.y, forward.z, up.x, up.y, up.z };
    alListenerfv(AL_ORIENTATION, orientation);
}
#pragma once
#include <glm/glm.hpp>
#include <AL/al.h>
#include <AL/alc.h>

class AudioListener
{
public:
    static AudioListener& GetListener();
    void SetListenerLocation(const glm::vec3& location) const;
    void SetListenerVelocity(const glm::vec3& velocity) const;
    void SetListenerOrientation(const glm::vec3& forward, const glm::vec3& up) const;

private:
    AudioListener() = default;
    ~AudioListener() = default;
};


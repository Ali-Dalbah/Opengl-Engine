#ifndef SOUND_OBJECT_H
#define SOUND_OBJECT_H
#include <glm/glm.hpp>
#include <AL/al.h>
class SoundObject{
public:
    SoundObject();
    ~SoundObject();
    void play(const unsigned int );
    void setGain(float);
    void setPitch(float);
    void setLoop(bool);
private:
    float pitch;
    float gain;
    glm::vec3 position;
    glm::vec3 velocity;
    bool loop;
    unsigned int buffer;
    unsigned int source;
};

#endif
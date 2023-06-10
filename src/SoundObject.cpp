#include "../include/SoundObject.h"

SoundObject::SoundObject(): position(0.f), velocity(0.f) {
    this->pitch = 1.f;
    this->gain = 1.f;
    this->loop = false;
    this->buffer = 0;
    alGenSources(1, &source);
    alSource3f(source, AL_POSITION, position.x, position.y, position.z);
    alSource3f(source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    alSourcef(source, AL_PITCH, pitch);
    alSourcef(source, AL_GAIN, gain);
    alSourcei(source, AL_LOOPING, loop);
    alSourcei(source, AL_BUFFER, buffer);
}

SoundObject::~SoundObject() {
    if (source)
        alDeleteSources(1, &source);
}

void SoundObject::play(const unsigned int buffer) {
    if (buffer != this->buffer) {
        this->buffer = buffer;
        alSourcei(source, AL_BUFFER, (int)buffer);
    }
    alSourcePlay(source);
}

void SoundObject::setGain(float gain) {
    this->gain = gain;
    if(source) alSourcef(source, AL_GAIN, gain);
}

void SoundObject::setPitch(float pitch) {
    this->pitch = pitch;
    if (source) alSourcef(source, AL_PITCH, pitch);
}

void SoundObject::setLoop(bool loop) {
    this->loop = loop;
    if (source) alSourcei(source, AL_LOOPING, loop);
}
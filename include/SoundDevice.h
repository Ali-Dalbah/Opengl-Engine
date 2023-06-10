#ifndef SOUND_DEVICE_H 
#define SOUND_DEVICE_H

#include <AL/alc.h>
#include <AL/al.h>
#include <iostream>

class SoundDevice {
public:
    static SoundDevice* get();
private:
    SoundDevice();
    ~SoundDevice();
    ALCdevice* device;
    ALCcontext* context;
};

#endif
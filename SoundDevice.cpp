#include "../include/SoundDevice.h"

SoundDevice* SoundDevice::get() {
    static SoundDevice* device =  new SoundDevice();
    return device;
}

SoundDevice::SoundDevice() {
    device = alcOpenDevice(nullptr);
    if (!device)
        throw("Failed to Create Sound Device");
    context = alcCreateContext(device, nullptr);
    if (!context)
        throw("Failed to Create Sound Context");
    if (!alcMakeContextCurrent(context))
        throw("Failed to Make Context Current");
    const char* name = nullptr;
    if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"));
        name= alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    if (!name || alcGetError(device) != ALC_NO_ERROR)
        name = alcGetString(device, ALC_DEVICE_SPECIFIER);
}

SoundDevice::~SoundDevice() {
    if (!alcMakeContextCurrent(nullptr))
        std::cout<<"Failed to Make Context Null"<<std::endl;
    alcDestroyContext(context);
    if(context)
        std::cout<<"Failed to destroy Context"<<std::endl;
    if (!alcCloseDevice(device))
        std::cout<<"Failed to close Device"<<std::endl;
}
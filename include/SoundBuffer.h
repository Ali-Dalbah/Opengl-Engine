#ifndef SOUND_BUFFER_H
#define SOUND_BUFFER_H
#include <vector>
#include <sndfile.h>
#include <AL/alext.h>
#include <AL/al.h>
#include <iostream>
#include <limits.h>
class SoundBuffer{
public:
    static SoundBuffer* get();
    unsigned int addSound(const char*);
    bool removeSound(const unsigned int&);
private:
    SoundBuffer();
    ~SoundBuffer();
    std::vector<unsigned int> buffers;
};

#endif
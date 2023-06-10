#include "../include/SoundBuffer.h"

SoundBuffer* SoundBuffer::get() {
    static SoundBuffer* buffer = new SoundBuffer();
    return buffer;
}

unsigned int SoundBuffer::addSound(const char* fileName) {
    SF_INFO  fileInfo;
    SNDFILE* file = sf_open(fileName, SFM_READ, &fileInfo);
    if (!file) {
        std::cout<<"ERROR: Couldn't Open Sound File "<<fileName<<"\n"<<sf_strerror(file)<<std::endl;
        return 0;
    }
    if (fileInfo.frames < 1 || fileInfo.frames > INT_MAX/sizeof(short) / fileInfo.channels) {
        std::cout<<"ERROR: Sound File Bad Sample Count "<<fileName<<" "<<fileInfo.frames<<std::endl;
        sf_close(file);
        return 0;
    }
    ALenum format = AL_NONE;
    switch (fileInfo.channels) {
    case 1:
        format = AL_FORMAT_MONO16;
        break;
    case 2:
        format = AL_FORMAT_STEREO16;
        break;
    case 3:
        if (sf_command(file, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT2D_16;
        break;
    case 4:
        if (sf_command(file, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT3D_16;
    default:
        break;
    }
    if (!format) {
        std::cout<<"ERROR: Sound File Format not Supported "<<fileName<<std::endl;
        sf_close(file);
        return 0;
    }
    short* memory = (short*)(malloc(fileInfo.frames * fileInfo.channels * sizeof(short)));
    long int frameCount = sf_readf_short(file, memory, fileInfo.frames);
    if (frameCount < 1) {
        free(memory);
        sf_close(file);
        std::cout<<"Failed to Read Samples in "<<fileName<<std::endl;
        return 0;
    }
    int bytesCount = (int)(frameCount * fileInfo.channels) * (int)(sizeof(short));
    unsigned int buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, memory, bytesCount, fileInfo.samplerate);
    free(memory);
    sf_close(file);
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        std::cout<<"ERROR: Openal "<<alGetString(err)<<std::endl;
        if (buffer && alIsBuffer(buffer)) alDeleteBuffers(1, &buffer);
        return 0;
    }
    buffers.push_back(buffer);
    return buffer;
}

bool SoundBuffer::removeSound(const unsigned int& buffer) {
    std::vector<unsigned int>::iterator it = buffers.begin();
    while (it != buffers.end()) {
        if (*it == buffer) {
            alDeleteBuffers(1, &*it);
            it = buffers.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

SoundBuffer::SoundBuffer() {
    buffers.clear();
}

SoundBuffer::~SoundBuffer() {
    alDeleteBuffers(buffers.size(), buffers.data());
    buffers.clear();
}
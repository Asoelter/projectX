#ifndef SPEAKER_H
#define SPEAKER_H

#ifdef __linux__
#include <AL/al.h>
#include <AL/alc.h>
#endif 
#ifdef __APPLE_CC__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
//TODO(asoelter): find audio library for windows
#endif

#include <vector>

namespace core::audio
{

class Speaker
{
public:
    Speaker();
    ~Speaker();
    void play(const std::vector<short>& buffer);
    void play(const short* buffer, int count);
    bool playing() const;

    static std::vector<short> tone(int hz);

private:
    static constexpr int bufferCount_ = 2;

#ifndef WIN32
    ALCdevice* device_;
    ALCcontext* context_;
    ALuint buffers_[bufferCount_]; //think openGL vbo 
    ALuint source_;
#endif 
};

}

#endif //SPEAKER_H

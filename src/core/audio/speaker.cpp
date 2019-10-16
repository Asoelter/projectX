#include "speaker.h"

#ifdef WIN32
# define _USE_MATH_DEFINES
# define M_PI 3.14159
#endif 
#include <cmath>

#include "../../util/handmade_util.h"
#ifndef WIN32
#	include <AL/al.h>
#	include <AL/alc.h>
#endif

namespace core::audio
{
Speaker::Speaker()
{
#ifndef WIN32
    device_ = alcOpenDevice(0);

    handmade_assert(device_)

    context_ = alcCreateContext(device_, 0);

    alcMakeContextCurrent(context_);

    handmade_assert(context_);

    alGenBuffers(bufferCount_, buffers_);
    alGenSources(1, &source_);
#endif 
}

Speaker::~Speaker()
{
#ifndef WIN32
    alcCloseDevice(device_);
#endif
}

void Speaker::play(const std::vector<short>& buffer)
{
    play(buffer.data(), buffer.size());
}

void Speaker::play(const short* buffer, int count)
{
#ifndef WIN32
    alBufferData(buffers_[0], AL_FORMAT_MONO16, buffer, count, 44000);
    alSourcei(source_, AL_BUFFER, buffers_[0]);

    //alSourcei(source_, AL_LOOPING, 1); //loops buffer
    alSourcePlay(source_);
#endif
}

bool Speaker::playing() const
{
#ifndef WIN32
    ALint sourceState;
    alGetSourcei(source_, AL_SOURCE_STATE, &sourceState);
    return sourceState == AL_PLAYING;
#else
	return false;
#endif
}

std::vector<short> Speaker::tone(int hz)
{
    const int samplesPerSecond = 48000;
    const auto audioBufferSize = samplesPerSecond * 2;
    const int wavePeriod = samplesPerSecond / hz;

    const short toneVolume = 6000;
    int sampleIndex = 0;

    std::vector<short> result;
    result.reserve(samplesPerSecond);

    for(int i = 0; i < audioBufferSize; ++i)
    {
        const float t = 2.0f * M_PI * static_cast<float>(sampleIndex++) / static_cast<float>(wavePeriod);
        const auto sineValue = sinf(t);
        const short sampleValue = sineValue * toneVolume;
        result.push_back(sampleValue);
    }

    result.shrink_to_fit();

    return result;
}

}


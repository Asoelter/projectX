#include "speaker.h"

#include <cmath>

#include "../../util/handmade_util.h"
#include <AL/al.h>
#include <AL/alc.h>

namespace core::audio
{
Speaker::Speaker()
{
    device_ = alcOpenDevice(0);

    handmade_assert(device_)

    context_ = alcCreateContext(device_, 0);

    alcMakeContextCurrent(context_);

    handmade_assert(context_);

    alGenBuffers(bufferCount_, buffers_);
    alGenSources(1, &source_);
}

Speaker::~Speaker()
{
    alcCloseDevice(device_);
}

void Speaker::play(const std::vector<short>& buffer)
{
    play(buffer.data(), buffer.size());
}

void Speaker::play(const short* buffer, int count)
{
    alBufferData(buffers_[0], AL_FORMAT_MONO16, buffer, count, 44000);
    alSourcei(source_, AL_BUFFER, buffers_[0]);

    //alSourcei(source_, AL_LOOPING, 1); //loops buffer
    alSourcePlay(source_);
}

bool Speaker::playing() const
{
    ALint sourceState;
    alGetSourcei(source_, AL_SOURCE_STATE, &sourceState);
    return sourceState == AL_PLAYING;
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

//Original audio stuff
//NOTE(adam): openAL does not need data inputted in a two channel format
/*constexpr int numChannels = 1;
constexpr int samplesPerSecond = 48000;
constexpr auto audioBufferSize = numChannels * samplesPerSecond;
short audioBuffer[audioBufferSize];

constexpr int toneHz = 256;
constexpr short toneVolume = 6000;
int sampleIndex = 0;
constexpr int wavePeriod = samplesPerSecond / toneHz;
constexpr int halfWavePeriod = wavePeriod / 2;
constexpr int bytesPerSample = sizeof(short) * 2;

static auto count = 0;

if(count++ == 0)
{
    for(int i = 0; i < audioBufferSize; ++i)
    {
        const short sampleValue = ((sampleIndex++ / halfWavePeriod) % 2) ? toneVolume : -toneVolume;
        audioBuffer[i] = sampleValue;
    }

    int discards = 0;
    int lastValue = audioBuffer[audioBufferSize - 1];

    for(int i = audioBufferSize - 1; audioBuffer[i] == lastValue; --i)
    {
        ++discards;
    }

    alBufferData(audioBuffers[0], AL_FORMAT_MONO16, audioBuffer, audioBufferSize - discards, 44000);
    alSourcei(audioSource, AL_BUFFER, audioBuffers[0]);
}

ALint sourceState;
alGetSourcei(audioSource, AL_SOURCE_STATE, &sourceState);

if (sourceState != AL_PLAYING)
{
    alSourcePlay(audioSource);
}*/


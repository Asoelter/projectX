#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <cmath>

#include "util/handmade_util.h"
#include "util/handmade_defs.h"
#include "util/handmade_gl.h"

#include "core/shader.h"
#include "core/window.h"

//opengl globals
GLFWwindow* glWindow;
GLuint vao[2];
GLuint vbo[2];

//window globals
global constexpr int width  = 720;
global constexpr int height = 480;
global bool running         = true;

//audio globals
ALCdevice* audioDevice;
ALCcontext* audioContext;
global constexpr int numAudioBuffers = 2;
global constexpr int audioBufferSize = 24000;
global short audioBuffer[audioBufferSize]; //actual audio buffer
ALuint audioBuffers[numAudioBuffers]; //think openGL vbo 
ALuint audioSource;

enum key
{
    ESCAPE = 9
};

void init_audio();

int main(int argc, char** argv)
{
    HANDMADE_UNUSED(argc); 
    HANDMADE_UNUSED(argv);

    core::graphics::Window customWindow(width, height, "Custom window");
    init_audio();
    core::graphics::Shader shader("src/res/shaders/grad.vs", "src/res/shaders/grad.fs");

    float topLeft[] = {
         1.0f,  1.0f,
        -1.0f,  1.0f,
        -1.0f, -1.0f
    };

    float bottomRight[] = {
        -1.0f, -1.0f,
         1.0f,  -1.0f,
         1.0f, 1.0f,
    };

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), topLeft, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), bottomRight, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    while(running && customWindow.open())
    {
        //graphics stuff
        if(customWindow.isPressed(core::graphics::Key::Escape))
        {
            running = false;
        }

        customWindow.setBackgroundColor(0.0f, 0.6f, 0.8f);
        customWindow.update();

        glBindVertexArray(vao[0]);
        shader.bind();
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(vao[1]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        customWindow.swap();

        //audio stuff
        //NOTE(adam): openAL does not need data inputted in a two channel format
        constexpr int numChannels = 1;
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
        }

    } //while(running)

    alcCloseDevice(audioDevice);

    return 0;
} //main

void init_audio()
{
    audioDevice = alcOpenDevice(NULL);

    handmade_assert(audioDevice)

    audioContext = alcCreateContext(audioDevice, NULL);

    alcMakeContextCurrent(audioContext);

    handmade_assert(audioContext);

    alGenBuffers(numAudioBuffers, audioBuffers);
    alGenSources(1, &audioSource);
}

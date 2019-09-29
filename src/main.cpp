#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/extensions/dbe.h>
#include <X11/extensions/Xdbe.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <cmath>

#define HANDMADE_INTERNAL
#include "util/handmade_util.h"
#include "util/handmade_defs.h"

//window globals
global constexpr int width                    = 720;
global constexpr int height                   = 480;
global bool running                 = true;

//visual globals
global Display* display             = nullptr;
global Visual* visual               = nullptr;
global XdbeBackBuffer backBuffer    = {0};
global int screen                   = 0;
global Window window                = {0};
global GC gc                        = {0};
global XImage* image;
global char* pixmap;

//audio globals
ALCdevice* audioDevice;
ALCcontext* audioContext;
stat statBuf;
global constexpr int numAudioBuffers = 2;
global constexpr int audioBufferSize = 24000;
global short audioBuffer[audioBufferSize]; //actual audio buffer
ALuint audioBuffers[numAudioBuffers]; //think openGL vbo 
ALuint audioSource;

global constexpr auto BLACKNESS = 0x000000;
global constexpr auto WHITENESS = 0xFFFFFF;

enum key
{
    ESCAPE = 9
};

void init_graphics();
void init_audio();
void renderWeirdGradient(int offset);

int main(int argc, char** argv)
{
    HANDMADE_UNUSED(argc); 
    HANDMADE_UNUSED(argv);

    pixmap = new char[width * height];
    init_graphics();
    init_audio();

    XEvent event;
    int yOffset = 0;

    auto wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);

    XSetWMProtocols(display, window, &wmDeleteMessage, 1);
    bool running = true;

    handmade_assert(display);

    int offset = 0;

    while(running)
    {
        event = {0};
        XCheckMaskEvent(display, ExposureMask | ButtonPressMask | KeyPressMask | StructureNotifyMask, &event);

        XdbeBeginIdiom(display);

        switch(event.type)
        {
            case KeyPress: 
            {
                offset += 10;

                if(event.xkey.keycode == key::ESCAPE)
                {
                    running = false;
                }
            }break;

            case ClientMessage:
            {
                if(event.xclient.data.l[0] == static_cast<long>(wmDeleteMessage))
                {
                    running = false; 
                }
            }break;

            case ConfigureNotify:
            {
                if(width == event.xconfigure.width && height == event.xconfigure.height)
                {
                    break; //Only use this to handle window resizes
                }

                //handle resize events here
            }break;

            default:
            {

            }break;
        } //switch

        //graphics stuff
        renderWeirdGradient(offset);

        XdbeSwapInfo swapInfo;
        swapInfo.swap_window = window;
        swapInfo.swap_action = XdbeUndefined;

        handmade_assert(XdbeSwapBuffers(display, &swapInfo, 1));
        XdbeEndIdiom(display);

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

            std::cout << "First value: " << audioBuffer[0] << std::endl;
            std::cout << "Last value: " << audioBuffer[audioBufferSize - discards - 1] << std::endl;
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

void init_graphics() 
{
    //XCreateImage(display, visual, depth, format, offset, data, width, height, bitmap_pad,
                        //bytes_per_line)
    display = XOpenDisplay((char *)0);
    screen  = DefaultScreen(display);

    int major = 0;
    int minor = 0;

    if(!XdbeQueryExtension(display, &major, &minor)) //init double buffering
    {
        printf("Xdbe (%d.%d) supported, using double buffering\n", major, minor);
        int numScreens = 1;
        Drawable screens[] = { DefaultRootWindow(display) };
        XdbeScreenVisualInfo *info = XdbeGetVisualInfo(display, screens, &numScreens);
        if (!info || numScreens < 1 || info->count < 1) 
        {
            fprintf(stderr, "No visuals support Xdbe\n");
            return;
        }

        // Choosing the first one, seems that they have all perflevel of 0,
        // and the depth varies.
        XVisualInfo xvisinfo_templ;
        xvisinfo_templ.visualid = info->visinfo[0].visual; // We know there's at least one
        // As far as I know, screens are densely packed, so we can assume that if at least 1 exists, it's screen 0.
        xvisinfo_templ.screen = 0;
        xvisinfo_templ.depth = info->visinfo[0].depth;

        int matches;
        XVisualInfo *xvisinfo_match =
            XGetVisualInfo(display, VisualIDMask|VisualScreenMask|VisualDepthMask, &xvisinfo_templ, &matches);

        if (!xvisinfo_match || matches < 1) {
            fprintf(stderr, "Couldn't match a Visual with double buffering\n");
            return;
        }

        visual = xvisinfo_match->visual;
    } 

    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, width, height, 5, None, None);
    backBuffer = XdbeAllocateBackBufferName(display, window, XdbeBackground);

    XSetStandardProperties(display, window, "Handmade","Handmade",None,NULL,0,NULL);

    XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask | StructureNotifyMask);

    gc = XCreateGC(display, window, 0,0);

    XMapRaised(display, window);

    image = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen), ZPixmap, 0, pixmap, width, height, 8, 0);
}

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

void renderWeirdGradient(int offset)
{
    const auto stride = width / 10;

    const auto xLimit = width + stride + offset;
    const auto yLimit = height + stride;



    for(int startPointY = 0; startPointY < yLimit; startPointY += stride)
    {
        auto prevStartX = 0;
        auto carriageReturned = false;

        for(int startPointX = offset + stride; startPointX < offset || !carriageReturned; startPointX += stride)
        {
            auto horizontalWalker = startPointX;
            auto verticalWalker = startPointY;

            auto color = 0x00AFFF;
            while(horizontalWalker > prevStartX && verticalWalker < startPointY + stride)
            {
                XSetForeground(display, gc, color);
                XDrawLine(display, backBuffer, gc, horizontalWalker, startPointY, startPointX, verticalWalker);
                --horizontalWalker;
                ++verticalWalker;
                --color;
            }

            XSetForeground(display, gc, WHITENESS);

            auto cornerX = horizontalWalker;
            auto cornerY = verticalWalker;

            auto hWalker2 = startPointX;
            auto vWalker2 = startPointY;

            while(hWalker2 > prevStartX && vWalker2 < startPointY + stride)
            {
                XSetForeground(display, gc, color);
                XDrawLine(display, backBuffer, gc, hWalker2, cornerY, cornerX, vWalker2);
                --hWalker2;
                ++vWalker2;
                color -= 2;
            }

            prevStartX = startPointX;

            if(startPointX >= width)
            {
                startPointX = 0;
                carriageReturned = true;
            }
        }
    }

    std::cout << "Before" << std::endl;
    XPutImage(display, backBuffer, gc, image, 0, 0, 0, 0, width, height);
    std::cout << "After" << std::endl;
}


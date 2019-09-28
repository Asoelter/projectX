#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/extensions/dbe.h>
#include <X11/extensions/Xdbe.h>

#define ALSA_PCM_NEW_HW_PARAMS_API

#include <AL/al.h>
#include <AL/alc.h>
#include <alsa/asoundlib.h>

#include <iostream>
#include <cmath>

#define HANDMADE_INTERNAL
#include "util/handmade_util.h"
#include "util/handmade_defs.h"

//visual globals
global Display* display             = nullptr;
global Visual* visual               = nullptr;
global XdbeBackBuffer backBuffer    = {0};
global int screen                   = 0;
global Window window                = {0};
global GC gc                        = {0};

//window globals
global int width                    = 720;
global int height                   = 480;
global bool running                 = true;

//audio globals
global snd_pcm_hw_params_t *params  = nullptr;
global snd_pcm_uframes_t frames     = 32;
global snd_pcm_t *audioHandle            = nullptr;
global int rc                       = 0;
global int dir                      = 0;
global unsigned int rate             = 0;

static constexpr auto BLACKNESS = 0x000000;
static constexpr auto WHITENESS = 0xFFFFFF;

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

    init_graphics();
    init_audio();

    XEvent event;
    int yOffset = 0;

    auto wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);

    XSetWMProtocols(display, window, &wmDeleteMessage, 1);
    bool running = true;

    handmade_assert(display);

    int offset = 0;

    handmade_assert(frames);
    const auto size = frames * 4;
    short buffer[size];
    short secondaryBuffer[size];

    auto sign = 1;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < frames * 2; j += frames * 2)
        {
            buffer[i + j] = 126 * 10000 * sin(i);
            buffer[i + j + 1] = 126 * 10000 * sin(i);
        }

        if(i % 2 == 0)
        {
            sign *= -1;
        }
    }

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

        renderWeirdGradient(offset);

        XdbeSwapInfo swapInfo;
        swapInfo.swap_window = window;
        swapInfo.swap_action = XdbeUndefined;

        handmade_assert(XdbeSwapBuffers(display, &swapInfo, 1));
        XdbeEndIdiom(display);

        snd_pcm_prepare(audioHandle);
        static short value = 5;
        value += 10;
        if(snd_pcm_writei(audioHandle, &value, frames) < 0)
        {
            snd_pcm_prepare(audioHandle);
            std::cout << "Buffer underrun" << std::endl;
        }


    } //while(running)

    snd_pcm_drain(audioHandle);
    snd_pcm_close(audioHandle);

    return 0;
} //main

void init_graphics() 
{

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
}

void init_audio()
{
    rc = snd_pcm_open(&audioHandle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    handmade_assert(rc >= 0)

    //Allocate a hardware parameters object. 
    snd_pcm_hw_params_alloca(&params);

    //Fill it in with default values. 
    snd_pcm_hw_params_any(audioHandle, params);

    //Interleaved mode 
    snd_pcm_hw_params_set_access(audioHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

    //Signed 16-bit little-endian format 
    snd_pcm_hw_params_set_format(audioHandle, params, SND_PCM_FORMAT_S16_LE);

    //Two channels (stereo) 
    snd_pcm_hw_params_set_channels(audioHandle, params, 2);

    //44100 bits/second sampling rate (CD quality) 
    rate = 48000;
    snd_pcm_hw_params_set_rate_near(audioHandle, params, &rate, &dir);

    //Set period size to 32 frames. 
    frames = 32;
    snd_pcm_hw_params_set_period_size_near(audioHandle, params, &frames, &dir);

    const int periods = 2;
    const int periodsize = 8192;
    snd_pcm_hw_params_set_buffer_size(audioHandle, params, (periodsize * periods)>>2);

    //Write the parameters to the driver 
    rc = snd_pcm_hw_params(audioHandle, params);
    handmade_assert(rc >= 0);

    //Use a buffer large enough to hold one period 
    snd_pcm_hw_params_get_period_size(params, &frames, &dir);

    snd_pcm_prepare(audioHandle);
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
}


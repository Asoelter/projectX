#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/extensions/dbe.h>
#include <X11/extensions/Xdbe.h>

#include <portaudio.h>

#include <iostream>

#define HANDMADE_UNUSED(arg) (void)arg

#define HANDMADE_INTERNAL

#ifdef HANDMADE_INTERNAL
#   define handmade_assert(arg)                     \
        if(!(arg))                                  \
            {                                       \
                std::cout << "Failed assertion: \"" \
                          << #arg << "\" on line "  \
                          << __LINE__ << " in file "\
                          << __FILE__ << '\n';      \
                abort();                            \
            }                                       \
        else{}
#else
#   define assert(arg) 
#endif 

#define LinMain main

#define persistant  static
#define global      static

global Display* display = nullptr;
global Visual* visual   = nullptr;
global XdbeBackBuffer backBuffer;
global int screen = 0;
global Window window;
global GC gc;

global int width    = 720;
global int height   = 480;
global bool running = true;

static constexpr auto BLACKNESS = 0x000000;
static constexpr auto WHITENESS = 0xFFFFFF;

enum key
{
    ESCAPE = 9
};

void init_graphics();
void renderWeirdGradient(int offset);

int LinMain(int argc, char** argv)
{
    HANDMADE_UNUSED(argc); 
    HANDMADE_UNUSED(argv);

    init_graphics();

    XEvent event;
    int yOffset = 0;

    auto wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);

    XSetWMProtocols(display, window, &wmDeleteMessage, 1);
    bool running = true;

    handmade_assert(display);

    int offset = 0;

    while(running)
    {
        XNextEvent(display, &event);

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
    } //while(running)

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

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
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


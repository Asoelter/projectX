#ifndef DRAWABLE_H
#define DRAWABLE_H

template<typename T>
struct IsDrawable
{
    static bool value() {return false;}
};

template<typename T>
constexpr inline bool IsDrawableV = false;

//TODO(asoelter): check for required overloaded
//template functions (eg., draw) once the required 
//functions are identified

#define REGISTER_DRAWABLE(type)                     \
    template<>                                      \
    struct IsDrawable<type>                         \
    {                                               \
        static bool value() {return true;}          \
    };                                              \
                                                    \
    template<>                                      \
    constexpr inline bool IsDrawableV<type> = true; \

#endif //DRAWABLE_H

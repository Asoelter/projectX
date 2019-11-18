#ifndef COLOR_H
#define COLOR_H

namespace core::graphics
{

struct Color
{
    constexpr Color(float _r, float _g, float _b, float _a)
        : r(_r)
        , g(_g)
        , b(_b)
        , a(_a)
    {

    }

    constexpr Color(const Color& other)
        : r(other.r)
        , g(other.g)
        , b(other.b)
        , a(other.a)
    {
        
    }

    union
    {
        struct
        {
            float r;
            float g;
            float b;
            float a;
        };
        float data[4];
    };


    constexpr static Color greyScale(float value);
};

constexpr Color white()
{
    return {1.0f, 1.0f, 1.0f, 1.0f};
}

constexpr Color black()
{
    return {0.0f, 0.0f, 0.0f, 1.0f};
}

constexpr Color red()
{
    return {1.0f, 0.0f, 0.0f, 1.0f};
}

constexpr Color green()
{
    return {0.0f, 1.0f, 0.0f, 1.0f};
}

constexpr Color yellow()
{
    return {1.0f, 1.0f, 0.0f, 1.0f};
}

constexpr Color orange()
{
    return {1.0f, 0.5f, 0.0f, 1.0f};
}

constexpr Color blue()
{
    return {0.0f, 0.0f, 1.0f, 1.0f};
}

constexpr Color greyScale(float value)
{
    return {value, value, value, 1.0f};
}

constexpr Color grey()
{
    return greyScale(0.5);
}

}


#endif //COLOR_H


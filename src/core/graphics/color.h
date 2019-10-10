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

constexpr Color red()
{
    return {1.0f, 0.0f, 0.0f, 1.0f};
}

constexpr Color green()
{
    return {0.0f, 1.0f, 0.0f, 1.0f};
}

constexpr Color blue()
{
    return {0.0f, 0.0f, 1.0f, 1.0f};
}

constexpr Color greyScale(float value)
{
    return {value, value, value, 1.0f};
}

}


#endif //COLOR_H


#include <iostream>

//----------------------handmade_unused-------------------
#define HANDMADE_UNUSED(arg) (void)arg

//----------------------handmade_assert-------------------
#ifdef HANDMADE_INTERNAL
#   define handmade_assert(arg)                     \
        if(!(arg))                                  \
        {                                           \
            std::cout << "Failed assertion: \""     \
                      << #arg << "\" \non line: "   \
                      << __LINE__ << " \nin file: " \
                      << __FILE__ << '\n'           \
                      << "Continue? (y/n)\n";       \
                                                    \
            char response;                          \
            std::cin >> response;                   \
                                                    \
            if(response == 'n')                     \
            {                                       \
                abort();                            \
            }                                       \
        }                                           \
        else{}
#else
#   define handmade_assert(arg) 
#endif //HANDMADE_INTERNAL

//----------------------handmade_print-------------------
#ifdef HANDMADE_INTERNAL
#   define handmade_print(msg) \
        std::cout << __LINE__ << ": " << msg << '\n'; 
#else
#   define handmade_print(msg)
#endif //HANDMADE_INTERNAL

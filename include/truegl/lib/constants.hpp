#ifndef CONSTANTS
#define CONSTANTS

#include <iostream>
#include <truegl/lib/graphics.hpp>

namespace TGL {
/* Keycode definitions for ReadKey Method */
class KeyCode {
private:
public:
    /* Standard KeyCodes; You can use only these keycodes for your game */
    static constexpr auto KEY_W = ASCII_w;
    static constexpr auto KEY_A = ASCII_a;
    static constexpr auto KEY_S = ASCII_s;
    static constexpr auto KEY_D = ASCII_d;
    static constexpr auto KEY_ESCAPE = ASCII_ESC;
    static constexpr auto KEY_SPACE = ASCII_SP;

    /* Functions */
    static auto is_valid_key_code(int k) -> bool
    {
        return k == KeyCode::KEY_A || k == KeyCode::KEY_D || k == KeyCode::KEY_ESCAPE || k == KeyCode::KEY_S || k == KeyCode::KEY_SPACE || k == KeyCode::KEY_W ? true : false;
    }
};
} // namespace TGL
#endif

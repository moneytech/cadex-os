/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * A simple game for Cadex OS
 * @author HyperCreeck
 * @note This game uses TrueGL GameKit Library
 */
#include <iostream>        // standard I/O funtions reside here
#include <truegl/gkit.hpp> // This is required for using TrueGL GameKit

using namespace std;       // std namespace
using namespace TGL;       // TrueGL namespace
using namespace TGL::GKit; // Required for TrueGL; We dont want to put TGL::GKit
                           // on every TrueGL class and function

int key;
int x, y, w, h;

int main(int argc, const char **argv) {
    Console::WriteLine(
        "Box: A simple but mind blowing game"); // just an intro :)
    render_window(WN_STDWINDOW);
    w = 10;
    h = 10;
    while (1) {
        read_object(STDIN, &key, 1);
        if (key == KeyCode::KEY_W || key == ASCII_W) {
            y--;
            drawRect(x, y, w, h);
        } else if (key == KeyCode::KEY_ESCAPE) {
            break;
        }
    }
    return 0; // Don't forget to return 0!
}

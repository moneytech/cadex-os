/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * A simple game for Cadex OS
 * @author HyperCreeck
 * @note This game uses TrueGL GameKit Library
*/
#include <iostream> // standard I/O funtions reside here
#include <truegl/gkit.hpp> // This is required for using TrueGL GameKit

using namespace std; // std namespace
using namespace TGL; // TrueGL namespace
using namespace TGL::GKit; // Required for TrueGL; We dont want to put TGL::GKit on every TrueGL class and function

int a;

int main(int argc, const char** argv) {
    Console::WriteLine("Box: A simple but mind blowing game"); // just an intro :)
    renderWindow(WN_STDWINDOW);
    while(1){
        read(0, a, 1);
        if(a == KeyCode::KEY_W){
            drawRect(10, 10, 100, 100);
        } else
        {
            break;
        }
        
    }
    return 0; // Don't forget to return 0!
}
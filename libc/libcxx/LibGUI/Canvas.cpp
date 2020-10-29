#include <LibGUI/Canvas.hpp>
#include <stdio.h>

// Constructor
LibGUI::Canvas::Canvas(int x, int y, int width, int height) {
    // Invoke on_create()
    this->on_create ();
}

// Draws a pixel on the specified position
void LibGUI::Canvas::draw_pixel (int x, int y){
    // The best way of drawing a pixel
    drawRect (x,y,1,1);
}

// Draws a rectangle on the specified positions with the specified dimensions
void LibGUI::Canvas::draw_rect(int x, int y, int w, int h){
    // Just use drawRect()!
    drawRect (x,y,w,h);
}

// Draws a line on the specified positions with the specified dimensions
void LibGUI::Canvas::draw_line(int x, int y, int w, int h){
    // Just use drawLine()!
    drawLine(x,y,w,h);
}

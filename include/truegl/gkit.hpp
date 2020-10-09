/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * TrueGL GameKit
 *
 * GameKit provides libraries for making Games for Cadex OS using C++
*/

#ifndef _TRUEGL_GKIT
#define _TRUEGL_GKIT

#include <iostream>
#include <truegl/lib/constants.hpp>

namespace TGL::GKit {
class SpriteBase {
private:
public:
    /* Properties */
    int x = 0;
    int y = 0;
    union {
        int r;
        int g;
        int b;
    } Color;

    /* Event-handler functions */
    virtual void OnReady() = 0;
    virtual void OnDestroy() = 0;
    virtual void OnCreate() = 0;
    virtual void OnDraw() = 0;
    virtual void OnClearSprite() = 0;
    virtual void OnMove() = 0;
    virtual void OnResize() = 0;
};

class GSprite : public SpriteBase {
private:
public:
    /* Properties */
    int x;
    int y;
    int width;
    int height;

    union {
        int r;
        int g;
        int b;
    } Color;

    ~GSprite();

    /* Functions */
    void SetSpriteType() { }
    void DrawSprite() { }
    void MoveSprite() { }
    void SetLocation(int xpos, int ypos)
    {
        x = xpos;
        y = ypos;
    }
    void SetWidth(int w)
    {
        width = w;
    }
    void SetHeight(int h)
    {
        height = h;
    }
    int GetWidth()
    {
        return width;
    }
    int GetHeight()
    {
        return height;
    }
    int GetXPos()
    {
        return x;
    }
    int GetYPos()
    {
        return y;
    }
    /* Event-handler functions */
    virtual void OnReady() { }
    virtual void OnDestroy() { }
    virtual void OnCreate() { }
    virtual void OnDraw() { }
    virtual void OnClearSprite() { }
    virtual void OnMove() { }
    virtual void OnResize() { }
};
} // namespace TGL::GKit
#endif // !_TRUEGL_GKIT

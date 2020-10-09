/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * TrueGL Graphics Library eXtended
 *
 * This file includes all necessary headers for making a standard TrueGL GLX application
*/

#ifndef _TGL_GLX_
#define _TGL_GLX_

#include <truegl/lib/button.hpp>
#include <truegl/lib/graphics.hpp>

#define TGL_GLX_VER 1
#define TGL_SUPPORTS_XEND false
#define TGL_IS_BETA false

namespace TGL
{
    extern GraphicsManager Graphics;
    extern GraphicsContext AppContext;

    typedef struct
    {
        GraphicsContext glx_context;
        bool is_glx_beta = true;
        bool window_initialised = false;
        union window_props
        {
            int width;
            int height;
            int xpos;
            int ypos;
            int window_level;
            bool root_window = true;
        } *window_props;
    } glx_config_t;

    extern glx_config_t *current_glx_config;

/**
 * @param context 
*/
    auto glx_get_config = [](GraphicsContext context) {
        if(current_glx_config->window_props->root_window){
			// If the current glx window config's root_window property is 1 then return the current glx config
            return current_glx_config;
        } else
        {
			// Just return if the current glx window config's root_window value is 0
            return;
        }
    };
} // namespace TGL

#endif

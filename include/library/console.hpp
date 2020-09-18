/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * This file contains the class definitions of the Console class
*/
#ifndef _CONSOLE_HH
#define _CONSOLE_HH

#include <stdio.h>
#include <stdlib.h>
#include <algorithm.h>
#include <color>
#include <library/malloc.h>
#include <library/math.h>
#include <library/scanf.h>

namespace std
{

    /**
     * The base console class
     * @author HyperCreeck (@asiawin)
    */
    class Console
    {
    public:
        /**
         * Create a console on WN_STDWINDOW
        */
        Console()
        {
        }

        /**
         * Creates a console on specified window
         * @param window The window to initialize the console
        */
        Console(int window)
        {
        }

        /**
         * Delete the console object
        */
        ~Console()
        {
        }

        /**
         * Writes the specified string to the console
         * @param str The string to write to the console
        */
        static void Write(char *str)
        {
            printf("%s", str);
        }

        /**
         * Writes a line to console
         * @param str String to write to console
        */
        static void WriteLine(char *str)
        {
            printf("%s\n", str);
        }

        /**
         * Read a line from the STDIN
         * @param str The string to store the input to
        */
        void ReadLine(char *str)
        {
            scanf(str, sizeof(str));
        }

        /**
         * Sets the foreground color of the console
         * @param color The color to use
        */
        auto SetForegroundColor(Colors::Color *color) -> void
        {
            setTextColor(color->r, color->g, color->b, color->a);
        }

        /**
         * Prints a character to the console
         * @param value The value to print to the console
        */
        auto PutChar(char value) -> void
        {
            printf_putchar(value);
        }

        /**
         * Prints an integer value to the console
         * @param value The value to print to the console
        */
        auto PutInt(int value) -> void
        {
            printf("%d", value);
        }

        /**
         * Prints a hexadecimal value to the console
         * @param vaule The value to print to the console
        */
        auto PutHex(uint32_t value) -> void
        {
            printf("%x", value);
        }
    };
} // namespace std

#endif
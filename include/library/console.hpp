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
#include <library/malloc.h>
#include <library/math.h>
#include <library/scanf.h>

#include <color>
#include <string>

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
            renderWindow(WN_STDWINDOW);
        }

        /**
         * Creates a console on specified window
         * @param window The window to initialize the console
        */
        Console(int window)
        {
            renderWindow(window);
        }

        /**
         * Deletes the console object
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
         * Writes the specified string to the console
         * @param str The string to write to the console
        */
        static auto Write(String *str) -> void
        {
            char *tmp = str->getValue();
            printf("%s", tmp);
        }

        /**
         * Writes a line to the console
         * @param str The string to write to the console
        */
        static auto WriteLine(String *str) -> void
        {
            char *tmp = str->getValue();
            printf("%s", tmp);
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
        static void ReadLine(char *str)
        {
            scanf(str, sizeof(str));
        }

        /**
         * Sets the foreground color of the console
         * @param color The color to use
        */
        static auto SetForegroundColor(Colors::Color *color) -> void
        {
            setTextColor(color->r, color->g, color->b, color->a);
        }

        /**
         * Prints a character to the console
         * @param value The value to print to the console
        */
        static auto PutChar(char value) -> void
        {
            printf_putchar(value);
        }

        /**
         * Prints an integer value to the console
         * @param value The value to print to the console
        */
        static auto PutInt(int value) -> void
        {
            printf("%d", value);
        }

        /**
         * Prints a hexadecimal value to the console
         * @param value The value to print to the console
        */
        static auto PutHex(uint32_t value) -> void
        {
            printf("%x", value);
        }

        /**
         * Reads data from the keyboard with the specified length
         * @param output The variable to store the read data
         * @param length The length of data (i.e keystrokes) to be read from the keyboard
        */
        static auto Read(void *output, int length) -> void
        {
            read_object(STDIN, output, length);
        }
    };
} // namespace std

#endif
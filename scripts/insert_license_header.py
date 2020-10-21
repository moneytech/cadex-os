#!/usr/bin/env python3

# License header inserter script
# Inserts license header on the top of the file specified

import os, sys


def line_prepender(filename, line):
    with open(filename, "r+") as f:
        content = f.read()
        f.seek(0, 0)
        f.write(line.rstrip("\r\n") + "\n" + content)


def append_end_note(line, string, file):
    x = open(file, "a")
    x.write("\n\n/* EOF */")


# append_end_note(10, 10, sys.argv[1])
if sys.argv.__len__ > 0:
    line_prepender(
        sys.argv[1],
        "/**\n * Copyright (C) 2019-2020 The CadexOS Project\n * This software is distributed under the GNU General Public License.\n * See the file LICENSE for details.\n*/\n\n",
    )

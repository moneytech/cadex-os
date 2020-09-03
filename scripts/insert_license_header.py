#!/usr/bin/env python3

import os, sys

def append_end_note(line, string, file):
    x =  open(file, "a")
    x.write("\n\n/* EOF */")
    
append_end_note(10, 10, sys.argv[1])
#!/usr/bin/env python3

# Python file for creating standard filesystem folders inside basefs folder
import os, sys

def proc():
    mkdir("../basefs/proc", mode=0o777, *, dir_fd=None)
    
proc()
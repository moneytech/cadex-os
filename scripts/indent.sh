#!/bin/sh

# Standard indenting options for Cadex OS.
# Run "indent.sh filename" to properly indent a file.

indent -bap -br -brs -cdw -ce -cli0 -nfca -nhnl -nprs -nsaf -nsai -nsaw -nsob -npcs -npro -nss -l256 -nbfda -ut -i8 -npsl $@

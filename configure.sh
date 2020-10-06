#!/bin/bash

# Configuration script for Cadex OS

# Check if all dependencies are installed
echo -n "-- Checking if cross compiler works... "
if [ ! -d cross ]; then
	echo "-- Cross compiler not in 'cross' directory. Building cross compiler into 'cross'"
	./scripts/build-toolchain.sh
fi
echo "yes."
#!/bin/bash

# We'll use bash

GCC="gcc-8.2.0"
BINUTILS="binutils-2.31.1"
GDB="gdb-8.2"

CURRDIR=$(pwd)
PREFIX=$CURRDIR/cross
WORKDIR=$(mktemp -d)

# Tell the user about our config
echo "-- Cross compiler build script for Cadex OS (i386)"
echo "-- Installing cross-compiler to $PREFIX"
echo "-- Building in directory $WORKDIR"

cd "$WORKDIR"

# get and extract sources

if [ ! -d $BINUTILS ]; then
	echo "-- Downloading GNU Binutils sources..."
	curl -O https://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.gz
	tar -zxf $BINUTILS.tar.gz
fi

if [ ! -d $GCC ]; then
	echo "-- Downloading GCC sources..."
	curl -O https://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.gz
	tar -zxf $GCC.tar.gz
fi

if [ ! -d $GDB ]; then
	echo "-- Downloading GDB sources..."
	curl -O http://ftp.gnu.org/gnu/gdb/$GDB.tar.gz
	tar -zxf $GDB.tar.gz
fi

# build and install libtools
echo "-- Building libtools..."
cd $BINUTILS
./configure --prefix="$PREFIX" --target=i686-elf --disable-nls --disable-werror --with-sysroot
make && make install
cd ..

# download gcc prerequisites
echo "-- Downloading GCC prerequisites..."
cd $GCC
./contrib/download_prerequisites
cd ..

# build and install gcc
echo "-- Building GCC..."
mkdir $GCC-elf-objs
cd $GCC-elf-objs
../$GCC/configure --prefix="$PREFIX" --target=i686-elf --disable-nls --enable-languages=c --without-headers
make all-gcc && make all-target-libgcc && make install-gcc && make install-target-libgcc
cd ..

# build and install GDB
echo "-- Building GDB..."
cd $GDB
./configure --prefix="$PREFIX" --target=i686-elf
make && make install
cd ..

cd "$CURRDIR"
rm -rf "$WORKDIR"

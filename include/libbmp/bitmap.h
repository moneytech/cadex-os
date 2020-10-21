/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#ifndef BITMAP_H
#define BITMAP_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BITMAP_MAGIC 0x4D42
#define BITMAP_COMPRESSION_BI_RGB 0 /* Uncompressed */
#define BITMAP_BYTES_PER_24BPP 3 /* makes the code more readable */

typedef struct tagBITMAPFILEHEADER {
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
} __attribute__((packed)) bmp_fileheader_t;

typedef struct tagBITMAPINFOHEADER {
    unsigned short magic;
    unsigned int biSize;
    long biWidth;
    long biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} bmp_infoheader_t;

typedef struct bitmap {
    unsigned short magic;
    unsigned int width;
    unsigned int height;
    char *image_bytes;
    char *buf;
    unsigned int total_size;
    uint32_t bpp;
} bitmap_t;

typedef struct palette {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} palette_t;

typedef struct DIB_Header {
    uint32_t headerSize;
    uint32_t width;
    uint32_t height;
    uint16_t colorPlanes;
    uint16_t bpp;
    uint32_t compressionType;
} DIB_Header;

typedef struct BMP_Header {
    uint16_t magic;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t pixelsOffset;
    DIB_Header dibHeader;
} BMP_Header;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a bitmap and returns it
 * @param filename Full file path of the file (Must be absolute)
 */
bitmap_t *bitmap_create(char *filename);

/**
 * Displays the specified bitmap object
 * @param bmp The pointer to the bitmap object
 */
void bitmap_display(bitmap_t *bmp);

/**
 * Copys the bitmap data to framebuffer
 * @param bmp The pointer to the bitmap object
 */
void bitmap_to_framebuffer(bitmap_t *bmp);

int readBMP(char *filename, int posx, int posy);
bool Bitmap24Load(char *filename, uint32_t *width, uint32_t *height);
#ifdef __cplusplus
}
#endif
#endif

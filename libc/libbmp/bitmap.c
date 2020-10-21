#include <libbmp/bitmap.h>

bitmap_t *bitmap_create(char *filename) {
    bitmap_t *ret = malloc(sizeof(bitmap_t));
    // qemu_printf("Opening %s\n", filename);
    int file = open(filename, 0);
    if (!file) {
        dbg_printf("bitmap_create(): Fail to open %s\n", filename);
        return NULL;
    }

    /* This store bmp files upto 20KB */
    uint32_t size = 19782;
    void *buf = malloc(size);
    dbg_printf("bitmap_create(): Reading content of %s\n", filename);
    read_object(file, buf, size);

    // Parse the bitmap
    bmp_fileheader_t *h = buf;
    unsigned int offset = h->bfOffBits;
    // qemu_printf("bitmap size: %u\n", h->bfSize);
    // qemu_printf("bitmap offset: %u\n", offset);

    bmp_infoheader_t *info = buf + sizeof(bmp_fileheader_t);

    ret->width = info->biWidth;
    ret->height = info->biHeight;
    ret->image_bytes = (void *)((unsigned int)buf + offset);
    ret->buf = buf;
    ret->total_size = size;
    ret->bpp = info->biBitCount;
    printf("bitmap_create(): bitmap is %u x %u\n", ret->width, ret->height);
    // qemu_printf("file is here: %p\n", buf);
    // qemu_printf("image is here %p\n", ret->image_bytes);
    syscall_object_close(file);
    return ret;
}

void bitmap_display(bitmap_t *bmp) {
    if (!bmp)
        return;
    printf("bitmap_display(): Displaying bitmap. Dimens: W=%u,H=%u,SIZE=%u",
           bmp->width, bmp->height, bmp->total_size);
    uint8_t *image = bmp->image_bytes;
    int j = 0;
    // Do copy
    for (int i = 0; i < bmp->height; i++) {
        // Copy the ith row of image to height - 1 - i row of screen, each row
        // is of length width * 3
        char *image_row = image + i * bmp->width * 3;
        j = 0;
        for (int k = 0; k < bmp->width; k++) {
            uint32_t b = image_row[j++];
            uint32_t g = image_row[j++];
            uint32_t r = image_row[j++];
            uint32_t rgb = ((r << 16) | (g << 8) | (b)) & 0x00ffffff;
            rgb = rgb | 0xff000000;
            setTextColor(r, g, b, 0);
            drawRect(k, i, 1, 1);
            resetColor();
        }
    }
}

/**
 * Copy bitmap content to frame buffer
 * */
void bitmap_to_framebuffer(bitmap_t *bmp) {
    if (!bmp)
        return;
    uint8_t *image = bmp->image_bytes;
    int j = 0;
    // Do copy
    for (int i = 0; i < bmp->height; i++) {
        // Copy the ith row of image to height - 1 - i row of frame buffer, each
        // row is of length width * 3
        char *image_row = image + i * bmp->width * 3;
        // uint32_t * framebuffer_row = (void*)frame_buffer + (bmp->height - 1 -
        // i) * bmp->width * 4;

        j = 0;
        for (int k = 0; k < bmp->width; k++) {
            uint32_t b = image_row[j++] & 0xff;
            uint32_t g = image_row[j++] & 0xff;
            uint32_t r = image_row[j++] & 0xff;
            uint32_t rgb = ((r << 16) | (g << 8) | (b)) & 0x00ffffff;

            rgb = rgb | 0xff000000;
            setTextColor((r << 16), (g << 8), (b), 0);
            drawRect(k, i, 1, 1);
            resetColor();
        }
    }
}

int readBMP(char *filename, int posx, int posy) {
    int i;
    int f = open(filename, 0);

    if (f == KERROR_NOT_FOUND)
        return 0;
    else if (!f)
        return 0;

    printf("readBMP(): Reading file %s...\n", filename);
    unsigned char info[54];
    read(f, info, 54); // read the 54-byte header

    bmp_fileheader_t *header = (bmp_fileheader_t *)info;

    if (header->bfType != BITMAP_MAGIC) {
        printf("readBMP(): %s is not a valid 24-bit bitmap file\n", filename);
        return 0;
    }
    // extract image height and width from header
    int width = *(int *)&info[18];
    int height = *(int *)&info[22];

    printf("readBMP(): Image info: FILE=%s, W=%d,H=%d\n", filename, width,
           height);
    int row_padded = (width * 3 + 3) & (~3);
    unsigned char *data = malloc((unsigned char)3 * width * height);

	if(!data){
        printf("readBMP(): Out of memory!");
        return 0;
	}
    unsigned char tmp;

    data += (height - 1) * (width) * BITMAP_BYTES_PER_24BPP;

    for (int i = 0; i < height; i++) {
        read(f, data, row_padded);
        for (int j = 0; j < width * 3; j += 3) {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j + 2];
            data[j + 2] = tmp;

            setTextColor((int)data[j], (int)data[j + 1], (int)data[j + 2], 0);
            drawRect(posx + j, posy + i, 3, 1);
            resetColor();
        }
        data -= (width * BITMAP_BYTES_PER_24BPP * 2);
    }

    syscall_object_close(f);
    free(data);
    return true;
}

// returns true on success
// *ppBuffer will have the address of an allocated buffer containing the image
// on success, NULL otherwise. Caller must free *ppBuffer.
bool Bitmap24Load(char *filename, uint32_t *width,
                  uint32_t *height) {

    // Get the size of the image file
    uint32_t fileSize = 20000;

    // Allocate a buffer for the bitmap file
    uint8_t *rawFileBuffer = malloc(fileSize);
    if (!rawFileBuffer) {
        printf("Not enough memory to open bitmap file\n");
        return 0;
    }

    int f = open(filename, 0);

    if (!f)
        return 0;
    else if (f == KERROR_NOT_FOUND)
        return 0;

    read(f, rawFileBuffer, fileSize);
    BMP_Header *bmpHeader = (BMP_Header *)rawFileBuffer;

    // Check for the magic number
    if (bmpHeader->magic != BITMAP_MAGIC) {
        printf("%s is not a 24-bit bitmap file as far as I can "
                "tell.\nI don't know how to load it.\n",
                filename);
        free(rawFileBuffer);
        return false;
    }

    // Find where the pixel data begins
    uint32_t pixelDataOffset = bmpHeader->pixelsOffset;

    // Ensure the image is a 24-bit bitmap
    if (bmpHeader->dibHeader.bpp != 24) {
        printf("I'm sorry but this image isn't a 24-bit bitmap; "
                "I don't know how to display it.\n");
        printf("Image appears to be %d-bit", bmpHeader->dibHeader.bpp);
        free(rawFileBuffer);
        return false;
    }

    // Ensure the file is in RGB format
    if (bmpHeader->dibHeader.compressionType != BITMAP_COMPRESSION_BI_RGB) {
        printf("I'm sorry but this image is compressed; I don't "
                "know how to display it.\n");
        free(rawFileBuffer);
        return false;
    }

    // Get the image dimensions
    *width = bmpHeader->dibHeader.width;
    *height = bmpHeader->dibHeader.height;

    printf("Image dimensions: W=%d,H=%d", *width, *height);

    uint8_t *pixelData = (uint8_t *)((uint32_t)bmpHeader + pixelDataOffset);

    // For stupid reasons, bitmaps are stored "upside-down," so we'll need to
    // flip them vertically start at the bottom row of the pixelData
    pixelData += (*height - 1) * (*width) * BITMAP_BYTES_PER_24BPP;

    // for every line
    for (unsigned int y = 0; y < *height; ++y) {
        // for every pixel of the current line
        for (unsigned int x = 0; x < *width; ++x) {
            // copy the color elements from the pixel data to the current pixel
            setTextColor(*(pixelData++), *(pixelData++), *(pixelData++), 0);
            drawRect(x, y, 1, 1);
			resetColor();
        }

        // back pixelData up to the previous row (we backup an "extra" row
        // because we advanced to the end of the current row in the for loop)
        pixelData -= (*width * BITMAP_BYTES_PER_24BPP * 2);
    }
    // free(rawFileBuffer);
    return true;
}

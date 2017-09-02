#pragma once

#include "../util/graphics/gl.h"

/*
7z file must contain only one image file.
Returns an array of 8-bit pixel components (unsigned chars) where the first pixel is the bottom left.
Depending on the image format, either 3 (RGB) or 4 (RGBA) components make up one whole pixel.
*/
unsigned char* extractImageFrom7zFile(char* file, int* width, int* height, GLenum* format);

void freeImageData(unsigned char* imageData);

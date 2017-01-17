#pragma once

#include "../gl/gl.h"

unsigned char* extractImageFrom7zFile(char* file, int* width, int* height, GLenum* format);

void freeImageData(unsigned char* imageData);

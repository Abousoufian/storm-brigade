#ifndef __CODE_C__
#define __CODE_C__

#include <stdio.h>
#include <stdlib.h>

void helpMenu();
int convertToNumb(int *array);
void getLSB(unsigned char *inputPixels, unsigned char *redPixels, int imageSize);
void writeBMPfile(char *bmpHeaderInfo, unsigned char *inputPixels, int imageSize);
void convertToBinary(char inputChar, int *array);
void readBMPfile(char *bmpHeaderInfo, unsigned char *inputPixels, int imageSize);
int getSizeBMPFile(FILE *BMPfile);
int getSize(FILE *file);
void code();
void decode();

#endif
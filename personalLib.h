#ifndef __CODE_C__
#define __CODE_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void helpMenu();
int convertToNumb(int *array);
void getLSB(unsigned char *inputPixels, unsigned char *redPixels, int imageSize);
void writeBMPfile(char *bmpHeaderInfo, unsigned char *inputPixels, int imageSize, char *outputBMPFileName);
void convertToBinary(char inputChar, char *array);
void readBMPfile(char *bmpHeaderInfo, unsigned char *inputPixels, int imageSize, char *inputBMPFileName);
int getSizeBMPFile(FILE *BMPfile);
int getSize(FILE *file);
void code(char *inputTxtFileName, char *inputBMPFileName, char *outputBMPFileName);
void decode(char *outputBMPFileName, char *outputTxtFileName);

#endif
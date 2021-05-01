#include <stdio.h>
#include <stdlib.h>

int getSizeOfFile(FILE *fp, char path[]);

int main()
{
	FILE *inputFile = NULL;
	FILE *outputFile = NULL;
	FILE *inputBMPFile = NULL;
	int sizeFile = 0;
	
	//get size of input.txt
	sizeFile = getSizeOfFile(inputFile, "input.txt");
	printf("%d\n", sizeFile);
	
	// read data from input.txt
	inputFile = fopen("input.txt", "r");
	if(inputFile == NULL)
	{
		printf("Can't open file\n");
		exit(EXIT_FAILURE);
	}
	
	char buffer[sizeFile];
	
	// flush buffer memory
	for(int i=0; i<sizeFile; i++)
	{
		buffer[i]=0;
	}
	
	fread(buffer,sizeof(char), sizeFile, inputFile);
	fclose(inputFile);
	for(int i = 0; i < sizeFile; i++)
	{
		printf("%c", buffer[i]);
	}
	
	// write data from input.txt to output.txt
	outputFile = fopen("output.txt", "w");
	
	if(outputFile == NULL)
	{
		printf("Can't open file\n");
		exit(EXIT_FAILURE);
	}
	
	fwrite(buffer,sizeof(char), sizeFile, outputFile);
	fclose(outputFile);
	
	// read data from BMP file
	inputBMPFile = fopen("test.bmp", "rb");
	//rewind(inputBMPFile);
	if(inputBMPFile == NULL)
	{
		printf("Can't open file\n");
		exit(EXIT_FAILURE);
	}
	
	unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputBMPFile); // lees de 54-byte header
	
	printf("\n");
	
	for(int i = 0; i < 54; i++)
	{
		printf("%c", bmpHeader[i]);
	}
	printf("\n");	
	
    int breedte = bmpHeader[18];
    int hoogte = bmpHeader[22];
	
	printf("%d\n", breedte);
	printf("%d\n", hoogte);
	
	
	/*
    int imageSize = 3 * breedte * hoogte; //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB)
    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels
	

	
    fread(inputPixels, sizeof(unsigned char), imageSize, inputBMPFile); // Lees alle pixels (de rest van de file
    fclose(inputBMPFile);
	for(int i =0; i < imageSize-2; i+=3)
	{
		printf("%c", inputPixels[i+2]);
	}*/
   
    fclose(inputBMPFile);
    //free(inputPixels);
	
	
	
	return 0;
}





int getSizeOfFile(FILE *fp, char path[])
{
	fp = fopen(path, "r");
	if(fp == NULL)
	{
		printf("Can't open file\n");
		exit(EXIT_FAILURE);
	}
	
	fseek(fp, 0, SEEK_END);
	long int size = ftell(fp);
	fclose(fp);
  
    return size;
}



#include <stdio.h>
#include <stdlib.h>

#include <nameOfFiles.h>

int getSizeOfFile();
void readBMPfile();
void checkBMPdimension(int width, int height);

// get size of a file
int getSize(FILE *file)
{	

	fseek(file, 0, SEEK_END);
	long int size = ftell(file);
	rewind(file);
	
    return size;
}

int getSizeBmpFile();


void readBMPfile(char *bmpHeader, unsigned char *inputPixels, int imageSize)
{
    FILE *fp = fopen("test.bmp", "rb");
    if(fp == NULL)
    {
        printf("Something went wrong while trying to open %s\n", "test.bmp");
        exit(EXIT_FAILURE);
    }
    
	fread(bmpHeader, sizeof(unsigned char), 54, fp);

    fread(inputPixels, sizeof(unsigned char), imageSize, fp);
    fclose(fp);
}

// converts decimal number or character into a binary number
void convertToBinary(char inputChar, int *array)
{
	int bufferSize = 9;
	int temp = inputChar;
	
	array[8]= '\0';
	
	for (int i = bufferSize-2; i>0; i--) {
		array[i] = temp%2;
		temp /= 2; 
	}	
}

void writeBMPfile(char *bmpHeader, unsigned char *inputPixels, int imageSize)
{
    FILE *fp = fopen("output.bmp", "wb");
    if(fp == NULL)
    {
        printf("Something went wrong while trying to open %s\n", "test.bmp");
        exit(EXIT_FAILURE);
    }
    
	fwrite(bmpHeader, sizeof(char), 54, fp);
	fwrite(inputPixels, sizeof(char), imageSize, fp);
	
    fclose(fp);
}

void getFile(char *fileName);

int main() 
{
	FILE *txtFile = fopen(txtFileName, "r");		//File pointer to the input textfile
	
	int txtFileSize = getSize(txtFile);				// stores the size of the input textfile
	
	// buffer where to store all the data of the input textfile
	unsigned char *txtInputBuffer  = (unsigned char *) calloc(txtFileSize, sizeof(unsigned char));
	
	// storing the data of the input text file into the buffer (CHECKED)
	fread(txtInputBuffer,sizeof(char), txtFileSize, txtFile);
	
	fclose(txtFile);
	
	char bmpHeader[54];
	
	int imageSize = getSizeBmpFile();		//CHECKED
	
	
	// buffer where to store all the inputpixels of the BMPfile
	unsigned char *inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); 

	readBMPfile(bmpHeader, inputPixels, imageSize);	//CHECKED
	
	int bmpIndex = 2;
	int array[9] = {0};

	for (int i=0; i<txtFileSize; i++) 
	{
		//1. krijg character
		char inputChar = txtInputBuffer[i];
		
		//2. convert character naar binary
		convertToBinary(inputChar, array);	
		
		//3. loop door byte array
		for (int j =0; j<8; j++) 
		{
			//4. pas rode value aan met byte array value
			inputPixels[bmpIndex] += array[j];
			//5. verhoog index naar volgende rode pixel
			bmpIndex+=3;
		}
	}
	
	
	//4. insert "*" in BMPfile to mark the end of secret message
	bmpIndex = txtFileSize + 2;
	unsigned char temp= 0x2A;
	
	for (int i =0; i<8; i++) 
	{
		inputPixels[bmpIndex] += array[i];
		//5. verhoog index naar volgende rode pixel
		bmpIndex+=3;
	}
	
	writeBMPfile(bmpHeader, inputPixels, imageSize);
}

int getSizeBmpFile()
{
	FILE *fp = fopen("test.bmp", "rb");
    if(fp == NULL)
    {
        printf("Something went wrong while trying to open %s\n", "test.bmp");
        exit(EXIT_FAILURE);
    }

    unsigned char bmpHeader[54];
    
	fread(bmpHeader, sizeof(unsigned char), 54, fp);

    int width = bmpHeader[18];
    int height = bmpHeader[22];

    int imageSize = 3 * width * height;
	
    fclose(fp);
	
	return imageSize;
}

void validateBMPdimension(int width, int height)
{
	if(width != height)
    {
        printf("Please use a BMP picture where width and height are equal to eachother\n");
		printf("Width: %d\n", width);
		printf("Height: %d\n", height);
		
        exit(EXIT_FAILURE);
    }
}






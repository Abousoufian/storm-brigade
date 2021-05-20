#include "personalLib.h"
#include "nameOfFiles.h"
void helpMenu()
{
	printf("-c -> Compress\n");
	printf("-s -> The input text file that contains the secret message\n");
	printf("-i -> The input bmp file\n");
	printf("-d -> decompress\n");
	printf("-o -> The output text file or bmp file\n\n\n");
	
	
	printf("examples:\n");
	printf("\tstormBrigade -c -s inputfile.txt -i meme.bmp -o memeou.bmp\n");
	printf("\tstormBrigade -d -i meme.bmp -o bericht.txt\n");
}


// get size of a file
int getSize(FILE *file)
{	
	fseek(file, 0, SEEK_END);
	long int size = ftell(file);
	rewind(file);
	
    return size;
}

// get size of a BMPfile
int getSizeBMPFile(FILE *BMPfile)
{
	unsigned char bmpHeaderInfo[54];
    
	fread(bmpHeaderInfo, sizeof(unsigned char), 54, BMPfile);

	unsigned int width = bmpHeaderInfo[18] | bmpHeaderInfo[19] << 8 | bmpHeaderInfo[20] << 16 | bmpHeaderInfo[21] << 24;
	unsigned int height = bmpHeaderInfo[22] | bmpHeaderInfo[23] << 8 | bmpHeaderInfo[24] << 16 | bmpHeaderInfo[25] << 24;

    unsigned int imageSize = 3 * width * height;
	
	return imageSize;
}

// read data from a BMPfile
void readBMPfile(char *bmpHeaderInfo, unsigned char *inputPixels, int imageSize)
{
    FILE *fp = fopen(inputBMPFileName, "rb");
    if(fp == NULL)
    {
        printf("Something went wrong while trying to open %s\n", inputBMPFileName);
        exit(EXIT_FAILURE);
    }
    
	fread(bmpHeaderInfo, sizeof(unsigned char), 54, fp);

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

// write data to a BMPfile
void writeBMPfile(char *bmpHeaderInfo, unsigned char *inputPixels, int imageSize)
{
    FILE *fp = fopen(outputBMPFileName, "wb");
    if(fp == NULL)
    {
        printf("Something went wrong while trying to open %s\n", outputBMPFileName);
        exit(EXIT_FAILURE);
    }
  
	fwrite(bmpHeaderInfo, sizeof(char), 54, fp);
	fwrite(inputPixels, sizeof(char), imageSize, fp);
	
    fclose(fp);
}

void getLSB(unsigned char *inputPixels, unsigned char *redPixels, int imageSize)
{	
	int redPxIndex = 0;
	
	for(int i =0; i < imageSize-2; i+=3)
	{
		redPixels[redPxIndex] = inputPixels[i+2]%2;
		redPxIndex++;
	}	
}

// convert binary array to numb
int convertToNumb(int *array)
{
	int numb = 0;
	int power = 1;
	for(int i=0; i<8; i++)
	{
		numb += array[7-i] * power;
		power*=2;
	}	
	return numb;
}		

// encrypt a secret message from a text file to a BMPfile
void code()
{
	
	//--------------------------------------compressing-message--------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------//
	//1. open input textfile
	//2. get size of textfile
	//3. store data of textfile into a buffer
	//4. close input textfile
	
	//1. (CHECKED)
	FILE *inputTxtFile = fopen(inputTxtFileName, "r");
    
	if(inputTxtFile == NULL)
	{
        printf("Something went wrong while trying to open %s\n", inputTxtFileName);
        exit(EXIT_FAILURE);
    }
	
	//2. (CHECKED)
	int txtFileSize = getSize(inputTxtFile);
			
					/*
					//test: print txtFileSize
					printf("%d\n", txtFileSize);
					*/
			
	//3. (CHECKED)
	// stores the data of the input text file into the buffer (CHECKED)
	unsigned char *txtInputBuffer  = (unsigned char *) calloc(txtFileSize, sizeof(unsigned char));
	
	fread(txtInputBuffer,sizeof(char), txtFileSize, inputTxtFile);
	
					
					//test: check if txtInputBuffer stores data of inputTxtFile
					FILE *outputTxtFile = fopen(outputTxtFileName, "w");
			
					if(outputTxtFile == NULL)
					{
						printf("Something went wrong while trying to open %s\n", outputTxtFileName);
						exit(EXIT_FAILURE);
					}
						
					fwrite(txtInputBuffer,sizeof(char), txtFileSize, outputTxtFile);
					
			
	//4.
	fclose(inputTxtFile);
	
	//-----------------------------------------------------------------------------------------------------------------//
	//5. open BMPfile
	//6. get size of BMPfile
	//7. store data of BMPfile into a buffer
	//8. close BMPfile
	
	//5. (CHECKED)
	FILE *BMPfile = fopen(inputBMPFileName, "rb");
    if(BMPfile == NULL)
    {
        printf("Something went wrong while trying to open %s\n", inputBMPFileName);
        exit(EXIT_FAILURE);
    }
	
	//6. (CHECKED)
	unsigned int imageSize = getSizeBMPFile(BMPfile);
			
					/*
					//test: print imageSize
					printf("%d\n", imageSize);
					*/
			
	
	//7. (CHECKED)
	char bmpHeaderInfo[54];
	unsigned char *inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); 
	
	readBMPfile(bmpHeaderInfo, inputPixels, imageSize);	//CHECKED
			
					
					/*
					//test: check if inputPixels stores data of inputBMPFileName
					for(int i =0; i < imageSize-2; i+=3)
					{
						printf("pixel %d: B= %d, G=%d, R=%d\n", i, inputPixels[i], inputPixels[i+1], inputPixels[i+2]);
					}
					*/
					
	
	//8.
	fclose(BMPfile);
	
	//-----------------------------------------------------------------------------------------------------------------//

	int bmpIndex = 2;
	int array[9] = {0};

	for (int i=0; i<txtFileSize; i++) 
	{
		//1. krijg character (CHECKED)
		char inputChar = txtInputBuffer[i];
				
					
					//test: print inputChar
					printf("%c", inputChar);
					
				
			
		//2. convert character naar binary
		convertToBinary(inputChar, array);	
					
					/*
					//test: print array
					for(int i=0; i<8; i++)
					{
						printf("%d", array[i]);
					}
					printf("\n");
					*/
					
		

		//3. loop door byte array
		for(int i =0; i < 8; i++)
		{
			inputPixels[bmpIndex] = inputPixels[bmpIndex] & (0b11111110 | array[i]);
			bmpIndex+=3;
		}
		
					/*
					//test: print inputPixels after LSB of red is changed
					for(int i =0; i < imageSize-2; i+=3)
					{
						printf("pixel %d: B= %d, G=%d, R=%d\n", i, inputPixels[i], inputPixels[i+1], inputPixels[i+2]);
					}
					*/
					
	}
	
	//4. insert "*" in BMPfile to mark the end of secret message
	unsigned char temp[8]= {0,0,1,0,1,0,1,0};
	for (int i =0; i<8; i++) 
	{
		inputPixels[bmpIndex] = inputPixels[bmpIndex] & (0b11111110 | temp[i]);
		bmpIndex+=3;
	}
	
	writeBMPfile(bmpHeaderInfo, inputPixels, imageSize);
}

// decrypt a secret message from a BMPfile to a text file
void decode()
{
	//-----------------------------------------------------------------------------------------------------------------//
	//5. open BMPfile
	//6. get size of BMPfile
	//7. store data of BMPfile into a buffer
	//8. close BMPfile
	
	//5. (CHECKED)
	FILE *BMPfile = fopen(outputBMPFileName, "rb");
    if(BMPfile == NULL)
    {
        printf("Something went wrong while trying to open %s\n", outputBMPFileName);
        exit(EXIT_FAILURE);
    }
	
	//6. (CHECKED)
	unsigned int imageSize = getSizeBMPFile(BMPfile);
			
					/*
					//test: print imageSize
					printf("%d\n", imageSize);
					*/
			
	
	//7. (CHECKED)
	char bmpHeaderInfo[54];
	unsigned char *inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); 
	
	readBMPfile(bmpHeaderInfo, inputPixels, imageSize);	//CHECKED
			
					/*
					//test: check if inputPixels stores data of inputBMPFileName
					for(int i =0; i < imageSize-2; i+=3)
					{
						printf("pixel %d: B= %d, G=%d, R=%d\n", i, inputPixels[i], inputPixels[i+1], inputPixels[i+2]);
					}
					*/
	
	fclose(BMPfile);	
	
	
	unsigned char *redPixels = (unsigned char *) calloc(imageSize/3, sizeof(unsigned char));
	
	getLSB(inputPixels, redPixels, imageSize);
	
					/*
					//test: check if redPixels stores data of inputPixels
					for(int i =0; i < (imageSize-2)/3; i++)
					{
						printf("pixel %d: R=%d\n", i, redPixels[i]);
					}
					*/
					
				
	free(inputPixels); 	
	
	int array[9] = {0};
	int numb = 0;
	
	for(int i=0; i<imageSize/3; i+=8)
	{
		// store de LSB of red into a 8bit array
		for(int j=0; j<8; j++)
		{
			array[j] = redPixels[i+j];
		}
		
		// convert binary array to numb
		numb = convertToNumb(array);
		
		printf("%d\t", numb);
		
		if(numb==42)
		{
			
			i=imageSize/3;
		}
		
		FILE *outputTxtFile = fopen(outputTxtFileName, "a");
			
		if(outputTxtFile == NULL)
		{
			printf("Something went wrong while trying to open %s\n", outputTxtFileName);
			exit(EXIT_FAILURE);
		}
				
		putc(numb,outputTxtFile);
	}
}
	
	
	
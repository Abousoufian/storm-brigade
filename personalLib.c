#include "personalLib.h"

/*
* This function will print the help menu
*/
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

/*
* This function will get a size of een TXT file
* @Param: FILE pointer of txt file
* will return the value of SIZE as an integerr
*/
int getSize(FILE *file)
{	
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);
	
    return size;
}

/*
* This function will get a size of a BMP file
* @Param: FILE pointer bmp file
* @Return: will return the value of SIZE as an integer
*/
int getSizeBMPFile(FILE *BMPfile)
{
	unsigned char bmpHeaderInfo[54];
    
	fread(bmpHeaderInfo, sizeof(unsigned char), 54, BMPfile);

	unsigned int width = bmpHeaderInfo[18] | bmpHeaderInfo[19] << 8 | bmpHeaderInfo[20] << 16 | bmpHeaderInfo[21] << 24;
	unsigned int height = bmpHeaderInfo[22] | bmpHeaderInfo[23] << 8 | bmpHeaderInfo[24] << 16 | bmpHeaderInfo[25] << 24;
	
	validateDimension(width, height);

    unsigned int imageSize = 3 * width * height;
	
	return imageSize;
}

/*
* This function will check of the input BMP has the right specification
* @Param: unsigned int width of the bmp file 
* @Param: unsigned int height of the bmp file 
* @Return: nothing
*/
void validateDimension(unsigned int width, unsigned int height)
{
	if((width!=height) && width%2!=0)
	{
		printf("Please use a BMP file where the width and height of the pixels are equal and a multiply of 4\n");
        exit(EXIT_FAILURE);
	}
}

/*
* This function will read data from a BMPfile
* @Param: char pointer use to store the bmp header info  
* @Param: unsigned char pointer use to store the pixels of an image
* @Param: integer value of the immagesize
* @Param: char pointer to a bmp file
* @Return: nothing
*/
void readBMPfile(char *bmpHeaderInfo, unsigned char *inputPixels, int imageSize, char *BMPFileName)
{
    FILE *fp = fopen(BMPFileName, "rb");
    if(fp == NULL)
    {
        printf("Something went wrong while trying to open %s\n", BMPFileName);
        exit(EXIT_FAILURE);
    }
    
	fread(bmpHeaderInfo, sizeof(unsigned char), 54, fp);

    fread(inputPixels, sizeof(unsigned char), imageSize, fp);
    fclose(fp);
}

/*
* This function will convert a character into a binary number
* @Param: char pointer that holds a character
* @Param: char pointer that holds the number in binary of the converted character
* @Return: nothing
*/
void convertToBinary(char inputChar, char *array)
{
	int bufferSize = 9;
	int temp = inputChar;
	
	array[8]= '\0';
	
	for (int i = bufferSize-2; i>0; i--) 
	{
		array[i] = temp%2;
		temp /= 2;
	}	
}

/*
* This function will write data to a BMPfile
* @Param: char pointer use to store the bmp header info  
* @Param: unsigned char pointer use to store the pixels of an image
* @Param: integer value of the immagesize
* @Param: char pointer to a bmp file
* @Return: nothing
*/
void writeBMPfile(char *bmpHeaderInfo, unsigned char *inputPixels, int imageSize, char *BMPFileName)
{
    FILE *fp = fopen(BMPFileName, "wb");
    if(fp == NULL)
    {
        printf("Something went wrong while trying to open %s\n", BMPFileName);
        exit(EXIT_FAILURE);
    }
  
	fwrite(bmpHeaderInfo, sizeof(char), 54, fp);
	fwrite(inputPixels, sizeof(char), imageSize, fp);
	
    fclose(fp);
}

/*
* This function will get the LSB of the red color
* @Param: unsigned char pointer use to store the pixels of an image  
* @Param: unsigned char pointer use to store the LSB of the red color
* @Param: integer value of the immagesize
* @Return: nothing
*/
void getLSB(unsigned char *inputPixels, unsigned char *redPixels, int imageSize)
{	
	int redPxIndex = 0;
	
	for(int i =0; i < imageSize-2; i++)
	{
		redPixels[redPxIndex] = inputPixels[i]%2;
		redPxIndex++;
	}	
}

/*
* This function will convert binary array to numb
* @Param: pointer of an array of integer pointer use to store the pixels of an image  
* @Return: nothing
*/
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

/*
* This function will encrypt a secret message from a text file to a BMPfile
* @Param: char pointer use to store the input txt file
* @Param: char pointer use to store the input bmp file
* @Param: char pointer use to store the output bmp file
* @Return: nothing
*/
void code(char *inputTxtFileName, char *inputBMPFileName, char *outputBMPFileName)
{
	
	//--------------------------------------compressing-message--------------------------------------------------------//
	//-----------------------------------------------------------------------------------------------------------------//
	//1. open input textfile
	//2. get size of textfile
	//3. store data of textfile into a buffer
	//4. close input textfile
	
	//1.
	FILE *inputTxtFile = fopen(inputTxtFileName, "r");
    
	if(inputTxtFile == NULL)
	{
        printf("Something went wrong while trying to open %s\n", inputTxtFileName);
        exit(EXIT_FAILURE);
    }
	
	//2.
	int txtFileSize = getSize(inputTxtFile);
			
	//3.
	// stores the data of the input text file into the buffer (CHECKED)
	unsigned char *txtInputBuffer  = (unsigned char *) calloc(txtFileSize, sizeof(unsigned char));
	
	fread(txtInputBuffer,sizeof(char), txtFileSize, inputTxtFile);
				
	//4.
	fclose(inputTxtFile);
	
	//-----------------------------------------------------------------------------------------------------------------//
	//5. open BMPfile
	//6. get size of BMPfile
	//7. store data of BMPfile into a buffer
	//8. close BMPfile
	
	//5.
	FILE *BMPfile = fopen(inputBMPFileName, "rb");
    if(BMPfile == NULL)
    {
        printf("Something went wrong while trying to open %s\n", inputBMPFileName);
        exit(EXIT_FAILURE);
    }
	
	//6.
	unsigned int imageSize = getSizeBMPFile(BMPfile);
				
	//7.
	char *bmpHeaderInfo = (char *) calloc(54, sizeof(char));
	unsigned char *inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); 
	
	readBMPfile(bmpHeaderInfo, inputPixels, imageSize, inputBMPFileName);	//CHECKED
			
	//8.
	fclose(BMPfile);
	
	//-----------------------------------------------------------------------------------------------------------------//

	int bmpIndex = 0;
	char array[8] = {0};

	for (int i=0; i<txtFileSize; i++) 
	{
		//1. krijg character
		char inputChar = txtInputBuffer[i];

		//2. convert character naar binary
		convertToBinary(inputChar, array);	
										
		//3. loop door byte array
		for(char i=0; i<8;i++)
		{
			if((inputPixels[bmpIndex] & 0b00000001) != array[i])
			{
			inputPixels[bmpIndex] ^= 1;
			}	
			bmpIndex ++;
		}
	}
	
	//4. insert "*" in BMPfile to mark the end of secret message
	unsigned char temp= 0b01010100;
	for (char i =0; i<8; i++) 
	{
		if((inputPixels[bmpIndex] & 0b00000001) != (temp >> i & 0b00000001))
		{
			inputPixels[bmpIndex] ^= 1;
		}	
		bmpIndex++;
	}

	writeBMPfile(bmpHeaderInfo, inputPixels, imageSize, outputBMPFileName);
	
	free(bmpHeaderInfo);
	free(txtInputBuffer);
	free(inputPixels);
}

/*
* This function will decrypt a secret message from a BMPfile to a text file
* @Param: char pointer use to store the output bmp file
* @Param: char pointer use to store the output txt file
* @Return: nothing
*/
void decode(char *outputBMPFileName, char *outputTxtFileName)
{
	//-----------------------------------------------------------------------------------------------------------------//
	//5. open BMPfile
	//6. get size of BMPfile
	//7. store data of BMPfile into a buffer
	//8. close BMPfile
	
	//5.
	FILE *BMPfile = fopen(outputBMPFileName, "rb");
    if(BMPfile == NULL)
    {
        printf("Something went wrong while trying to open %s\n", outputBMPFileName);
        exit(EXIT_FAILURE);
    }
	
	//6.
	unsigned int imageSize = getSizeBMPFile(BMPfile);
	
	//7.
	char *bmpHeaderInfo = (char *) calloc(54, sizeof(char));
	unsigned char *inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); 
	
	readBMPfile(bmpHeaderInfo, inputPixels, imageSize, outputBMPFileName);
	
	fclose(BMPfile);	
	
	
	unsigned char *redPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char));
	
	getLSB(inputPixels, redPixels, imageSize);
				
	free(inputPixels); 	
	
	int array[9] = {0};
	int numb = 0;
	FILE *outputTxtFile = fopen(outputTxtFileName, "w");
	
	for(int i=0; i<imageSize; i+=8)
	{
		// store de LSB of red into a 8bit array
		for(int j=0; j<8; j++)
		{
			array[j] = redPixels[i+j];
		}
		
		// convert binary array to numb
		numb = convertToNumb(array);
		
		if(numb==42)
		{
			
			i=imageSize;
		}
		
		if(outputTxtFile == NULL)
		{
			printf("Something went wrong while trying to open %s\n", outputTxtFileName);
			exit(EXIT_FAILURE);
		}
		
		putc(numb, outputTxtFile);
	}
	fclose(outputTxtFile);
	free(bmpHeaderInfo);
	free(redPixels);
}
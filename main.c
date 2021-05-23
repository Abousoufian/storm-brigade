#include "personalLib.h"




int main(int argc, char* argv[]) 
{
	// stores the name of the input textfile	
	char inputTxtFileName[50];			

	// stores the name of the input BMPfile	
	char inputBMPFileName[50];

	// stores the name of the output textfile
	char outputTxtFileName[50];			

	// stores the name of the output BMPfile	
	char outputBMPFileName[50];
	
	char arguments = 0;

	if (argc == 2 && strcmp(argv[1], "--help") == 0)
	{
		helpMenu();
	}
	else if (argc == 8 && strcmp(argv[1], "-c") == 0)
	{
		for(int i=2; i<8; i+=2)
		{
			if(strcmp(argv[i], "-s") == 0)
			{
				strcpy(inputTxtFileName, argv[i+1]);
				arguments |= 0b00000001;
				
			}
			else if(strcmp(argv[i], "-i") == 0)
			{
				strcpy(inputBMPFileName, argv[i+1]);
				arguments |= 0b00000010;
			}
			else if(strcmp(argv[i], "-o") == 0)
			{
				strcpy(outputBMPFileName, argv[i+1]);
				arguments |= 0b00000100;
			}
		}
		if (arguments==0b00000111)
		{
			printf("start coding\n");
			code(inputTxtFileName, inputBMPFileName, outputBMPFileName);
			printf("coding finished\n");
		}
		else
		{
			printf("Not all arguments are filled in\n");
			printf("%d\n", arguments);
		}
	}
	else if (argc == 6 && strcmp(argv[1], "-d") == 0)
	{
		for(int i=2; i<6; i+=2)
		{
			if(strcmp(argv[i], "-i") == 0)
			{
				strcpy(outputBMPFileName, argv[i+1]);
				arguments |= 0b00000001;
			}
			else if(strcmp(argv[i], "-o") == 0)
			{
				strcpy(outputTxtFileName, argv[i+1]);
				arguments |= 0b00000010;
			}
		}
		
		if (arguments==0b00000011)
		{
			printf("start decoding\n");
			decode(outputBMPFileName, outputTxtFileName);
			printf("decoding finished\n");
		}
		else
		{
			printf("Not all arguments are filled in\n");
		}
	}
	else
	{
		printf("Something went wrong\n");
		printf("incorrect arguments\n");
	}
	return 0;
}





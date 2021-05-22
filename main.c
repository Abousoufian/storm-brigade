#include "personalLib.h"
#include <stdio.h>



int main() 
{
int main(int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1], "--help") == 0) //--help
	{
		helpMenu();
	}
	else if (argc == 8 && strcmp(argv[1], "-c") == 0)
	{
		//Project.exe -c -s inputfile.txt -i meme.bmp -o memeOut.bmp
		if (argc == 8 && strcmp(argv[2], "-s") == 0)
		{
			//InputTXT geen vaste grootte geven //werkt niet
			//InputTXT = (char*)malloc(strlen(argv[3]));
			//memcpy(InputTXT, argv[3], strlen(argv[3]));

			memcpy(InputTXT, argv[3], 20);
		}
		if (argc == 8 && strcmp(argv[4], "-i") == 0)
		{
			memcpy(BMPINPUTFILE, argv[5], 20);
		}
		if (argc == 8 && strcmp(argv[6], "-o") == 0)
		{
			memcpy(BMPOUTPUTFILE, argv[7], 20);
		}
		compressDecompress('c');
	}
	else if (argc == 6 && strcmp(argv[1], "-d") == 0)
	{
		//Project.exe -d -i memeOut.bmp -o bericht.txt

		if (argc == 6 && strcmp(argv[2], "-i") == 0)
		{
			memcpy(BMPINPUTFILE, argv[3], 20);
		}
		if (argc == 6 && strcmp(argv[4], "-o") == 0)
		{
			memcpy(OutputTXT, argv[5], 20);
		}
		compressDecompress('d');
	}
	else
	{
		printf("Fout!!! \nNiet de juiste argumenten \nKijk in --help voor de uitleg \n");
		exit(EXIT_FAILURE);
	}
	
	code();
	decode();
	
	helpMenu();
	
	return 0;
}






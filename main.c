#include "personalLib.h"
#include <stdio.h>
#include <string .h>
//voorbeelden Project.exe -c -s inputfile.txt -i inputbmpfile.bmp -o outputbmpfile.bmp
			//Project.exe -d -i memeOut.bmp -o bericht.txt

int main(int argc, char* argv[]) {
	if (argc > 1)
	{
		if(argc == 1 && strcmp(argv[2], "--help")==0)
		{
			helpMenu();
		}
		else if(argc == 8 && strcmp(argv[2], "-c")==0)
		{
			for(int i = 0; i < argc; i++)
			{
				if (strcmp(argv[i], "-s") == 0)
				{
					memcpy(InputTXT, argv[i+1], 20);
				}
				if (strcmp(argv[i], "-i") == 0)
				{
					memcpy(BMPINPUTFILE, argv[i+1], 20);
				}
				if (strcmp(argv[i], "-o") == 0)
				{
					memcpy(BMPOUTPUTFILE, argv[i+1], 20);
				}
			}
			i=0;
			code();
		}
		else if(argc == 6 && strcmp(argv[2], "-d")==0)
		{
			for(int i = 0; i < argc; i++)
			{
				if (strcmp(argv[2], "-i") == 0)
				{
					memcpy(BMPINPUTFILE, argv[3], 20);
				}
				if (strcmp(argv[4], "-o") == 0)
				{
					memcpy(OutputTXT, argv[5], 20);
				}	
			}
			i=0;
			decode();
		}
		else
		{
			printf("Fout!!! \nFout argument kijk in de --help");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}






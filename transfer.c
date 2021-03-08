#include<stdio.h>

void toFile(char name[100], int mapImport[15][10])
{
	FILE* infile;
	infile = fopen(name, "w");

	// Write numbers to file
	for (int j = 0; j < 10; j++) 
	{
		for (int i = 0; i < 15; i++)
		{
			fprintf(infile, "%d ", mapImport[i][j]);
		}
		fprintf(infile, "\n");
	}

	fclose(infile);
}

void clear(int mapImport[15][10])
{
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			mapImport[i][j] = 0;
		}
	}
}
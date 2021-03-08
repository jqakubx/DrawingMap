#include "useSDL.h"
#include "transfer.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char* args[])
{
	int mapImport[15][10];
	clear(mapImport);

	char nameFile[100] = "map.txt";

	//Prepare and start SDL
	init(); 
	loadMedia(); 
	mainLoop(mapImport, nameFile);

	//Create file
	toFile(nameFile, mapImport);

	closing();
	return 0;
}
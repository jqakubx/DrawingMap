#ifndef useSDL_h
#define useSDL_h
//Starts up SDL and creates window
void init();

//Loads media
void loadMedia();

//Frees media and shuts down SDL
void closing();

//Main loop of events
void mainLoop(int mapImport[15][10], char nameFile[100]);
#endif
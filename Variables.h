#ifndef VARIABLES_H_
#define VARIABLES_H_


#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include "Texture.h"
#include "Constant.h"
#include "Button.h"
#include <iostream>
#include <ctime>




extern SDL_Window* gWindow;

extern SDL_Renderer* gRenderer;


extern SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
extern LTexture gButtonSpriteSheetTexture;
extern LTexture gBackgroundTexture;
extern LTexture gWinnerTexture;
extern LTexture gGameOverTexture;

extern int countMineLeft;
extern bool gameOver;
extern bool isWinning;


extern int game_map[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];

extern int player_map[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];


#endif // VARIABLES_H_





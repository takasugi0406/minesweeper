#include "Variables.h"

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;


SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTexture;
LTexture gBackgroundTexture;
LTexture gWinnerTexture;
LTexture gGameOverTexture;

int game_map[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
int player_map[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];

int countMineLeft = NUMBER_OF_MINES;
bool gameOver = false;
bool isWinning = false;



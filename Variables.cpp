#include "Variables.h"

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;


SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTexture;
LTexture gBackgroundTexture;
LTexture gWinnerTexture;
LTexture gGameOverTexture;


int countMineLeft = 10;
int countTileLeft = NUMBER_OF_ROWS*NUMBER_OF_COLUMNS;
bool gameOver = false;
bool isWinning = false;



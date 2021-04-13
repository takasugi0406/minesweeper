
#include "Variables.h"


using namespace std;



LButton gButtons[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];

void setBeginPlayerMap();
bool init();

bool loadMedia();

void close();

void setMapWithMine();
void setMapWithNumber();

bool checkWinGame();
void playAgain(bool &quit);

int main(int argc, char *argv[])
{

    //Start up SDL and create window
	if( !init() )
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			cout << "Failed to load media!\n";
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			while(!quit)
            {
            //Set begin map
            setBeginPlayerMap();


			//Set map
			setMapWithMine();
            setMapWithNumber();

            //While game is not over yet
            while ( !gameOver && !quit && !isWinning)
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = true;
                    }

                    //Handle button events
                    for (int i = 0; i < NUMBER_OF_ROWS; i++)
                    {
                        for (int j = 0; j < NUMBER_OF_COLUMNS; j++)
                        {
                            gButtons[i][j].handleEvent( &e );
                        }
                    }
                    isWinning = checkWinGame();
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render background
                gBackgroundTexture.render(0, 0);

                //Render buttons
                for( int i = 0; i < NUMBER_OF_ROWS; i++ )
                {
                    for ( int j = 0; j < NUMBER_OF_COLUMNS; j++ )
                    {
                        gButtons[i][j].render(i, j);
                    }
                }
                if(isWinning)
                {
                    gWinnerTexture.render(50, 10);
                }
                if(gameOver)
                {
                    gGameOverTexture.render(50, 10);
                }
                SDL_RenderPresent( gRenderer );
            }
            playAgain(quit);

		}

		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

void setBeginPlayerMap()
{
    for(int i = 0; i < NUMBER_OF_ROWS; i++)
    {
        for (int j = 0; j < NUMBER_OF_COLUMNS; ++j)
        {
            game_map[i][j] = 0;
            player_map[i][j] = 10;
        }
    }
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	//Load background
	if( !gBackgroundTexture.loadFromFile( "image/background.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	//Load winner background
	if(!gWinnerTexture.loadFromFile("image/winner.png"))
    {
        printf("Failed to load winner texture!\n");
        success = false;
    }
	//Load game over texture
	if(!gGameOverTexture.loadFromFile("image/game_over.png"))
    {
        printf("Failed to load game over texture!\n");
        success = false;
    }
	//Load sprites
	if( !gButtonSpriteSheetTexture.loadFromFile( "image/tiles.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else
	{
		//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = i * 32;
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = TILE_SIZE;
			gSpriteClips[ i ].h = TILE_SIZE;
		}
		for (int i = 0; i < NUMBER_OF_ROWS; i++)
        {
            for (int j = 0; j < NUMBER_OF_COLUMNS; j++)
            {
                gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_BETWEEN, i * TILE_SIZE + DISTANCE_BETWEEN);
            }
        }
	}

	return success;
}

void close()
{
	//Free loaded images
	gButtonSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



void setMapWithMine()
{
    int k = NUMBER_OF_MINES;
    time_t t;
    int r;
    int row, col;
    srand((unsigned) time(&t));
    while(k > 0)
    {
        r = rand() % (NUMBER_OF_ROWS * NUMBER_OF_COLUMNS);
        row = (r - 1) / NUMBER_OF_ROWS;
        col = r - row * NUMBER_OF_COLUMNS - 1;

        if(game_map[row][col] == 0)
        {
            game_map[row][col] = 9;
            k--;
        }
    }
}
int countMinesInEightCells(int x, int y)
{
    int count_ = 0;
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(x + i >= 0 && y + j >= 0 &&
                x + i < NUMBER_OF_ROWS && y + j < NUMBER_OF_COLUMNS
                )
            {
                if(game_map[x + i][y + j] == 9)
                {
                    count_++;
                }
            }
        }
    }
    return count_;
}
void setMapWithNumber()
{
    for (int i = 0; i < NUMBER_OF_ROWS; i++)
    {
        for (int j = 0; j < NUMBER_OF_COLUMNS; j++)
        {
            if(game_map[i][j] == 0)
            {
                game_map[i][j] = countMinesInEightCells(i, j);
            }
        }
    }
}


bool checkWinGame()
{
    bool win_game = true;
    for(int i = 0; i < NUMBER_OF_ROWS; i++)
    {
        for(int j = 0; j < NUMBER_OF_COLUMNS; j++)
        {
            if(player_map[i][j] == 10 && game_map[i][j] != 9)
            {
                win_game = false;
                break;
            }
        }
    }
    return win_game;
}

void playAgain(bool &quit)
{
    SDL_Event  e;

    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.key.keysym.sym == SDLK_SPACE )
        {
            gameOver = false;
            isWinning = false;
            quit = false;
            countMineLeft = 10;
        }
        else if(e.key.keysym.sym == SDLK_ESCAPE) quit = true;
    }
}

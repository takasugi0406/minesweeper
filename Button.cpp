#include "Variables.h"


LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;

}
void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        int i = (y - DISTANCE_BETWEEN) / TILE_SIZE;
        int j = (x - DISTANCE_BETWEEN) / TILE_SIZE;
     //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + TILE_SIZE )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + TILE_SIZE )
        {
            inside = false;
        }
        //Mouse is inside button
        if(inside)
        {
            //Set mouse over sprite
            switch( e->button.button )
            {

                case SDL_BUTTON_LEFT:
                {
                    reveal(i, j);
                    if (game_map[i][j] == 9)
                    {
                        for(int i = 0; i < NUMBER_OF_ROWS; i++)
                        {
                            for(int j = 0; j < NUMBER_OF_COLUMNS; j++)
                            {

                                if(game_map[i][j] == 9)
                                {
                                    player_map[i][j] = 9;
                                }
                            }
                        }
                        gameOver = true;
                    }
                    break;
                }

                case SDL_BUTTON_RIGHT:
                if (player_map[i][j] >= 10)
                {
                    if (player_map[i][j] == 10)
                    {
                        if (countMineLeft == 0) break;
                        player_map[i][j] = 11;
                        countMineLeft--;
                    }
                    else
                    {
                        player_map[i][j] = 10;
                        countMineLeft++;
                    }
                }
                break;

            }
        }
    }
}

void LButton::render(int i, int j)
{
    //Show current button sprite
    gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ player_map[i][j] ] );
}


void reveal(int x, int y)
{
    if (player_map[x][y] == 10 || player_map[x][y] == 11)
    {
        if (player_map[x][y] == 11)
        {
            countMineLeft++;
        }
        player_map[x][y] = game_map[x][y];
        if(player_map[x][y] == 0)
        {
        for(int i = -1; i < 2; i++)
        {
            for(int j = -1; j < 2; j++)
            {
                if(x+i >= 0 && y+j >= 0 && x+i < NUMBER_OF_ROWS && y+j < NUMBER_OF_COLUMNS && (i!=0 || j!=0))
                {
                    reveal(x+i, y+j);
                }
            }
        }
        }
    }
}

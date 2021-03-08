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
                if (player_map[i][j] == 11)
                {
                    countMineLeft ++;
                    player_map[i][j] = 10;
                }

                if(game_map[i][j] == 0)
                {
                    player_map[i][j] = 10;
                }
                else{player_map[i][j] = game_map[i][j];}
                set_player_map(i, j);
                if(player_map[i][j] == 9) gameOver = true;
                break;

                case SDL_BUTTON_RIGHT:
                if(player_map[i][j] == 10 && countMineLeft > 0)
                {
                    player_map[i][j] = 11;
                    countMineLeft --;
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

void set_player_map(int i, int j)
{
    if(player_map[i][j] == 9)
    {
        for(int a = 0; a < NUMBER_OF_ROWS; ++a)
        {
            for(int b = 0; b < NUMBER_OF_COLUMNS; ++b)
            {
                if(game_map[a][b] == 9)
                {
                    player_map[a][b] = 9;
                }
            }
        }
    }
    else if(player_map[i][j] == 10)
    {
        reveal(i, j);
        player_map[i][j] = 0;
    }
    else if (player_map[i][j] == 11)
    {
    }
    else
    {
        player_map[i][j] = game_map[i][j];
    }
}


void reveal(int x, int y)
{
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(x + i >= 0 && y +j >= 0 && x+i < NUMBER_OF_ROWS && y+j < NUMBER_OF_COLUMNS && (i!=0 || j!=0))
            {
                if(game_map[x+i][y+j] == 0 && player_map[x+i][y+j] != 0)
                {
                    if(player_map[x+i][y+j] == 11) countMineLeft++;
                    player_map[x+i][y+j] = 0;
                    reveal(x+i, y+j);
                }
                if(game_map[x+i][y+j] > 0 && game_map[x+i][y+j] < 9)
                {
                    if(player_map[x+i][y+j] == 11) countMineLeft++;
                    player_map[x+i][y+j] = game_map[x+i][y+j];
                }
            }
        }
    }
}

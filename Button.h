
#ifndef BUTTON_H_
#define BUTTON_H_

#include "Constant.h"

void set_player_map(int i, int j);
void reveal(int x, int y);

class LButton
{
public:
    LButton();

    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void render(int x, int y);
private:
    SDL_Point mPosition;
};

#endif // BUTTON_H_

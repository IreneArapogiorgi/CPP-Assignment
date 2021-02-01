/* Copyright (C) 2020-2021, Irene Arapogiorgi and Dimitris Bastas
*
*  All rights reserved.
* 
*  This project is developed as the main assignment delivered for Programming in C++ course.
*/

#include "graphics.h"
#include "config.h"
#include "game.h"

using namespace graphics;

void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(getUserData());
    game->update();
}

void draw()
{
    Game* game = reinterpret_cast<Game*>(getUserData());
    game->draw();
}

int main()
{
    Game mygame;

    createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Battles");

    setUserData(&mygame);
    setDrawFunction(draw);
    setUpdateFunction(update);

    setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    setCanvasScaleMode(CANVAS_SCALE_FIT);

    mygame.init();
    startMessageLoop();
    return 0;
}
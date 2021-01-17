#include "graphics.h"
#include "config.h"
#include "game.h"

using namespace graphics;

void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->update();
}

void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game mygame;

    createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game");

    setUserData(&mygame);
    setDrawFunction(draw);
    setUpdateFunction(update);

    setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();
    startMessageLoop();
    return 0;
}
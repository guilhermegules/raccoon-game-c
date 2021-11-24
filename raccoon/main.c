#include <stdlib.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Window.h>
#include <SFML/System/Clock.h>
#include <stdbool.h>

#define RACCOON_WIDTH 320
#define RACCOON_HEIGHT 232

sfIntRect figures[5][5] =
{
    {320,  0, RACCOON_WIDTH, RACCOON_HEIGHT},
    {640,  0, RACCOON_WIDTH, RACCOON_HEIGHT},
    {960,  0, RACCOON_WIDTH, RACCOON_HEIGHT},
    {1280, 0, RACCOON_WIDTH, RACCOON_HEIGHT}
};

sfSprite* createSprite(sfIntRect spriteFrame, char* imagePath)
{
    sfTexture *texture = sfTexture_createFromFile(imagePath, NULL);
    sfSprite *draw = sfSprite_create();

    sfSprite_setTexture(draw, texture, 0);
    sfSprite_setTextureRect(draw, spriteFrame);

    return draw;
}

int main()
{
    sfClock *relogio = sfClock_create();
    sfRenderWindow *window;
    sfVideoMode videoMode = {800, 600, 32};
    window = sfRenderWindow_create(videoMode, "T-Game", sfResize | sfClose, NULL);
    int frameIdx=0;
    float posX = 0.0f, posY = 0.0f;

    sfSprite *raccoon;

    while(sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        sfIntRect spriteFrame = {};

        while(sfRenderWindow_pollEvent(window, &event))
        {
            if(event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
        }

        sfTime tempo = sfClock_getElapsedTime(relogio);

        if(tempo.microseconds >= 150000)
        {
            frameIdx++;
            if(frameIdx >= 4) frameIdx=0;
            sfClock_restart(relogio);
        }

        if(sfKeyboard_isKeyPressed(sfKeyRight))
        {
            posX += 1.0;
        }

        if(sfKeyboard_isKeyPressed(sfKeyLeft))
        {
            posX -= 1.0;
        }

        if(sfKeyboard_isKeyPressed(sfKeyUp))
        {
            posY -= 1.0;
        }

        if(sfKeyboard_isKeyPressed(sfKeyDown))
        {
            posY += 1.0;
        }


        spriteFrame = figures[frameIdx][0];
        raccoon = createSprite(spriteFrame, "assets/texugo.jpeg");

        sfRenderWindow_clear(window, sfBlack);

        sfSprite_setPosition(raccoon, (sfVector2f)
        {
            posX, posY
        });

        sfRenderWindow_drawSprite(window, raccoon, NULL);
        sfRenderWindow_display(window);
    }
}

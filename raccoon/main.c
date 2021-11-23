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

int main()
{
    sfClock *relogio = sfClock_create();
    sfRenderWindow *window;
    sfVideoMode videoMode = {800, 600, 32};
    window = sfRenderWindow_create(videoMode, "T-Game", sfResize | sfClose, NULL);
    int frameIdx=0;

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

        spriteFrame = figures[frameIdx][0];

        sfRenderWindow_clear(window, sfWhite);

        sfTexture *textura = sfTexture_createFromFile("assets/texugo.jpeg", NULL);
        sfSprite *desenho = sfSprite_create();

        sfSprite_setTexture(desenho, textura, 0);
        sfSprite_setTextureRect(desenho, spriteFrame);

        sfRenderWindow_drawSprite(window, desenho, NULL);
        sfRenderWindow_display(window);
    }
}

#include <stdlib.h>
#include<stdio.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Window.h>
#include <SFML/System/Clock.h>
#include <stdbool.h>

#define RACCOON_WIDTH 117
#define RACCOON_HEIGHT 85
#define RACCON_SPRITES 4

#define DOG_HEIGHT 23.8
#define DOG_WIDTH 82.3
#define DOG_SPRITES 5

#define LIVES 3

sfIntRect racconSprites[RACCON_SPRITES] =
{
    {117,  0, RACCOON_WIDTH, RACCOON_HEIGHT},
    {234,  0, RACCOON_WIDTH, RACCOON_HEIGHT},
    {353,  0, RACCOON_WIDTH, RACCOON_HEIGHT},
    {470,  0, RACCOON_WIDTH, RACCOON_HEIGHT}
};

sfIntRect dogSprites[DOG_SPRITES] =
{
    {82.3,  0, DOG_WIDTH, DOG_HEIGHT},
    {164.6,  0, DOG_WIDTH, DOG_HEIGHT},
    {246.9,  0, DOG_WIDTH, DOG_HEIGHT},
    {329.2,  0, DOG_WIDTH, DOG_HEIGHT},
    {411.5,  0, DOG_WIDTH, DOG_HEIGHT}
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
    sfClock *clock = sfClock_create();
    sfRenderWindow *window;
    sfVideoMode videoMode = {800, 600, 32};
    window = sfRenderWindow_create(videoMode, "Raccoon Game", sfResize | sfClose, NULL);
    int frameIdx = 0;
    float posX = 0.0f, posY = 0.0f;

    // Sprites
    sfSprite *raccoon;
    sfVector2f raccoonPos;

    // sfSprite *dog;

    //sfTexture *liveTexture = sfTexture_createFromFile("assets/heart.png", NULL);

    //sfSprite *live = sfSprite_create();

    //sfSprite_setTexture(live, liveTexture, 0);

    //sfIntRect liveFrame;
    //liveFrame.height = 323;
    //liveFrame.width = 378;
    //liveFrame.top = 0;
    //liveFrame.left = 0;

    //sfSprite_scale(live, (sfVector2f)
    //{
    //    0.15f, 0.15f
    //});

    //sfSprite_setTextureRect(live, liveFrame);

    //sfSprite_setPosition(live, (sfVector2f)
    //{
    //    5.00f, 5.00f
    //});

    while(sfRenderWindow_isOpen(window))
    {
        sfEvent event;

        if(raccoon != NULL)
        {
            raccoonPos = sfSprite_getPosition(raccoon);
        }

        while(sfRenderWindow_pollEvent(window, &event))
        {
            if(event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
        }

        sfTime time = sfClock_getElapsedTime(clock);

        if(sfKeyboard_isKeyPressed(sfKeyRight))
        {
            if(raccoonPos.x < 690)
            {
                posX += 1.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyLeft))
        {
            if(raccoonPos.x != -15)
            {
                posX -= 1.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyUp))
        {
            if(raccoonPos.y > -20)
            {
                posY -= 1.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyDown))
        {
            if(raccoonPos.y < 530)
            {
                posY += 1.0;
            }
        }

        if(time.microseconds >= 150000)
        {
            frameIdx++;

            if(frameIdx >= 3) frameIdx = 0;

            sfClock_restart(clock);
        }

        raccoon = createSprite(racconSprites[frameIdx], "assets/texugo.png");

        // dog = createSprite(dogSprites[frameIdx], "assets/dog.png");

        sfRenderWindow_clear(window, sfWhite);

        sfSprite_setPosition(raccoon, (sfVector2f)
        {
            posX, posY
        });

        sfRenderWindow_drawSprite(window, raccoon, NULL);

        //sfRenderWindow_drawSprite(window, dog, NULL);

        //sfRenderWindow_drawSprite(window, live, NULL);

        sfRenderWindow_display(window);
    }

    sfSprite_destroy(raccoon);
    //sfSprite_destroy(live);
    //sfSprite_destroy(dog);
    sfRenderWindow_destroy(window);
}

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Window.h>
#include <SFML/System/Clock.h>
#include <stdbool.h>

#define RACCOON_WIDTH 117
#define RACCOON_HEIGHT 85
#define RACCON_SPRITES 4

#define DOG_HEIGHT 122
#define DOG_WIDTH 161.2
#define DOG_SPRITES 10

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
    {806,   0, DOG_WIDTH, DOG_HEIGHT},
    {644.8, 0, DOG_WIDTH, DOG_HEIGHT},
    {483.6, 0, DOG_WIDTH, DOG_HEIGHT},
    {322.4, 0, DOG_WIDTH, DOG_HEIGHT},
    {161.2, 0, DOG_WIDTH, DOG_HEIGHT},
    {806, 122, DOG_WIDTH, DOG_HEIGHT},
    {644.8, 122, DOG_WIDTH, DOG_HEIGHT},
    {483.6, 122, DOG_WIDTH, DOG_HEIGHT},
    {322.4, 122, DOG_WIDTH, DOG_HEIGHT},
    {161.2, 122, DOG_WIDTH, DOG_HEIGHT},
};

sfSprite* createSprite(sfIntRect spriteFrame, char* imagePath)
{
    sfTexture *texture = sfTexture_createFromFile(imagePath, NULL);
    sfSprite *draw = sfSprite_create();

    sfSprite_setTexture(draw, texture, 0);
    sfSprite_setTextureRect(draw, spriteFrame);

    return draw;
}

sfSprite* gameOver()
{
    sfIntRect GameOverFrame;
    GameOverFrame.height = 629;
    GameOverFrame.width = 579;
    sfTexture *texture = sfTexture_createFromFile("assets/gameOver.png", NULL);
    sfSprite *draw = sfSprite_create();

    sfSprite_setTexture(draw, texture, 0);
    sfSprite_setTextureRect(draw, GameOverFrame);

    return draw;
}

float generateRandomDogPosition()
{
    int lowerNumber = 100, biggerNumber = 500;

    return (rand() % (biggerNumber - lowerNumber + 1)) + lowerNumber;
}

bool verificaColisao(sfSprite * first, sfSprite * second, float FIRST_WIDTH, float FIRST_HEIGHT, float SECOND_WIDTH, float SECOND_HEIGHT)
{
    sfVector2f position_first         = sfSprite_getPosition(first);

    float firstX                      = position_first.x;
    float firstY                      = position_first.y;

    sfVector2f position_second        = sfSprite_getPosition(second);

    float secondX                     = position_second.x;
    float secondY                     = position_second.y;

    if (
        firstX < secondX + SECOND_WIDTH &&
        firstX + FIRST_WIDTH > secondX &&
        firstY < secondY + SECOND_WIDTH &&
        FIRST_HEIGHT + firstY > secondY
    )
    {
        return true;
    }

    return false;
}

int main()
{
    srand(time(NULL));
    sfClock *clock = sfClock_create();
    sfRenderWindow *window;
    sfVideoMode videoMode = {800, 600, 32};
    window = sfRenderWindow_create(videoMode, "Raccoon Game", sfResize | sfClose, NULL);
    int frameIdx = 0;
    int dogFrameIndex = 0;
    float posX = 0.0f, posY = 0.0f;
    float dposX = 830.0f, dposY = generateRandomDogPosition();

    // Sprites
    sfSprite *raccoon;
    sfVector2f raccoonPos;

    sfSprite *dog;
    sfVector2f dogPos;
    sfVector2f liveTAM;
    liveTAM.x = 0.15;
    liveTAM.y = 0.15;

    //HEART
    sfTexture *liveTexture = sfTexture_createFromFile("assets/heart.png", NULL);
    sfSprite *live = sfSprite_create();

    sfSprite_setTexture(live, liveTexture, 0);

    sfIntRect liveFrame;
    liveFrame.height = 323;
    liveFrame.width = 378;

    sfSprite_scale(live, liveTAM);
    sfSprite_setTextureRect(live, liveFrame);

    sfSprite_setPosition(live, (sfVector2f)
    {
        720.0f, 0.9f
    });

    sfSprite *live_2 = sfSprite_copy(live);
    sfSprite *live_3 = sfSprite_copy(live);
    sfSprite_setPosition(live_2, (sfVector2f)
    {
        650.0f, 0.9f
    });
    sfSprite_setPosition(live_3, (sfVector2f)
    {
        580.0f, 0.9f
    });
    //END ALL HEART


    // ====================================================== EMPTY HEART ======================================================
    sfTexture *liveEmptyTexture = sfTexture_createFromFile("assets/emptyHeart.png", NULL);
    sfSprite *liveEmpty = sfSprite_create();

    sfSprite_setTexture(liveEmpty, liveEmptyTexture, 0);

    sfIntRect liveEmptyFrame;
    liveEmptyFrame.height = 323;
    liveEmptyFrame.width = 508;

    sfVector2f liveEmptyTAM;
    liveEmptyTAM.x = 1.3;
    liveEmptyTAM.y = 1.3;

    sfSprite_scale(liveEmpty, liveEmptyTAM);
    sfSprite_setTextureRect(liveEmpty, liveEmptyFrame);

    sfSprite_setPosition(liveEmpty, (sfVector2f)
    {
        500.0f, 0.9f
    });
    // ====================================================== END EMPTY HEART ======================================================
    int bateu = 0;
    while(sfRenderWindow_isOpen(window))
    {
        sfEvent event;

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
                posX += 8.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyLeft))
        {
            if(raccoonPos.x != -15)
            {
                posX -= 8.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyUp))
        {
            if(raccoonPos.y > -20)
            {
                posY -= 8.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyDown))
        {
            if(raccoonPos.y < 530)
            {
                posY += 8.0;
            }
        }

        if(time.microseconds >= 150000)
        {
            frameIdx++;
            dogFrameIndex++;

            if(frameIdx >= 3) frameIdx = 0;

            if(dogFrameIndex >= DOG_SPRITES) dogFrameIndex = 0;

            dposX -= 20.0;

            sfClock_restart(clock);
        }

        raccoon = createSprite(racconSprites[frameIdx], "assets/texugo.png");
        dog     = createSprite(dogSprites[dogFrameIndex], "assets/dog.png");

        sfRenderWindow_clear(window, sfWhite);

        if(dogPos.x < -200)
        {
            dposY = generateRandomDogPosition();
            dposX = 830.0f;
        }

        sfSprite_setPosition(raccoon, (sfVector2f)
        {
            posX, posY
        });

        sfSprite_setPosition(dog, (sfVector2f)
        {
            dposX, dposY
        });

        sfRenderWindow_drawSprite(window, dog, NULL);
        sfRenderWindow_drawSprite(window, raccoon, NULL);
        sfRenderWindow_drawSprite(window, live, NULL);
        sfRenderWindow_drawSprite(window, live_2, NULL);
        sfRenderWindow_drawSprite(window, live_3, NULL);

        if(verificaColisao(raccoon, dog, RACCOON_WIDTH, RACCOON_HEIGHT, DOG_WIDTH, DOG_HEIGHT))
        {
            bateu++;

            if( bateu == 1 )
            {
                sfSprite_destroy(live);
                posX = 0.0f;
                posY = 0.0f;
            }

            if( bateu == 2 )
            {
                sfSprite_destroy(live_2);
                posX = 0.0f;
                posY = 0.0f;
            }

            if( bateu == 3 )
            {
                sfSprite_destroy(live_3);
                posX = 0.0f;
                posY = 0.0f;
            }
        }

        if(raccoon != NULL)
        {
            raccoonPos = sfSprite_getPosition(raccoon);
        }

        if(dog!= NULL)
        {
            dogPos = sfSprite_getPosition(dog);
        }

        sfRenderWindow_display(window);
    }

    sfSprite_destroy(raccoon);
    sfSprite_destroy(live);
    sfSprite_destroy(dog);
    sfRenderWindow_destroy(window);
}

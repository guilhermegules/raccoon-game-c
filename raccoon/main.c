#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Window.h>
#include <SFML/System/Clock.h>
#include <stdbool.h>

#define RACCOON_WIDTH 48
#define RACCOON_HEIGHT 48
#define RACCON_SPRITES 3

#define DOG_HEIGHT 48
#define DOG_WIDTH 48
#define DOG_SPRITES 3

#define PANDA_HEIGHT 48
#define PANDA_WIDTH 48
#define PANDA_SPRITES 3

#define LIVES 3

sfIntRect racconSprites[RACCON_SPRITES] =
{
    {48,  96, RACCOON_WIDTH, RACCOON_HEIGHT},
    {96,  96, RACCOON_WIDTH, RACCOON_HEIGHT},
    {144,  96, RACCOON_WIDTH, RACCOON_HEIGHT},
};

sfIntRect dogSprites[DOG_SPRITES] =
{
    {48, 48, DOG_WIDTH, DOG_HEIGHT},
    {96, 48, DOG_WIDTH, DOG_HEIGHT},
    {144, 48, DOG_WIDTH, DOG_HEIGHT},
};

sfIntRect pandasSprites[PANDA_SPRITES] =
{
    {432, 240, PANDA_WIDTH, PANDA_HEIGHT},
    {480, 240, PANDA_WIDTH, PANDA_HEIGHT},
    {528, 240, PANDA_WIDTH, PANDA_HEIGHT},
};

// sfIntRect

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
    float rightFirstSide              = firstX + FIRST_WIDTH;
    float leftFirstSide               = firstX;
    float bottomFirstSide             = firstY + FIRST_HEIGHT;
    float topFirstSide                = firstY;

    sfVector2f position_second        = sfSprite_getPosition(  second  );

    float secondX                     = position_second.x;
    float secondY                     = position_second.y;
    float rightSecondSide             = secondX + SECOND_WIDTH;
    float leftSecondSide              = secondX;
    float bottomSecondSide            = secondY + SECOND_HEIGHT;
    float topSecondSide               = secondY;

    bool rightColision                = false;
    bool leftColision                 = false;
    bool topColision                  = false;
    bool bottomColision               = false;

    if ( rightFirstSide   >= leftSecondSide    ) rightColision  = true;
    if ( topFirstSide     <= bottomSecondSide  ) bottomColision = true;
    if ( bottomFirstSide  >= topSecondSide     ) topColision    = true;
    if ( leftFirstSide    <= rightSecondSide   ) leftColision   = true;

    if ( rightColision && bottomColision && topColision && leftColision ) return true;

    return false;
}

int main()
{
    int num_lives = 5;
    char str[1] = "";
    sfFont *font = sfFont_createFromFile("arialregular.ttf");
    str[1]=sprintf(str, "%d", num_lives);
    sfText * text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 38);
    sfText_setFillColor(text, sfBlack);
    sfText_setPosition(text, (sfVector2f)
    {
        775.0f, 0.9f
    });


    srand(time(NULL));
    sfClock *clock = sfClock_create();
    sfRenderWindow *window;
    sfVideoMode videoMode = {800, 600, 32};
    window = sfRenderWindow_create(videoMode, "Raccoon Game", sfResize | sfClose, NULL);
    int frameIdx = 0;
    int dogFrameIndex = 0;
    float posX = 0.0f, posY = 0.0f;
    float dposX = 830.0f, dposY = generateRandomDogPosition();
    float pandaPosX = 100.0f, pandaPosY = 100.0f;

    // Sprites
    sfSprite *raccoon;
    sfVector2f raccoonPos;

    sfSprite *dog;
    sfVector2f dogPos;

    sfSprite *panda;
    sfVector2f pandaPos;

    // HEART
    sfVector2f liveTAM;
    liveTAM.x = 0.15;
    liveTAM.y = 0.15;
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
        710.0f, 0.9f
    });

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


        sfText_setString(text, str);
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

            if(frameIdx >= 2) frameIdx = 0;

            if(dogFrameIndex >= 2) dogFrameIndex = 0;

            dposX -= 10.0;

            sfClock_restart(clock);
        }

        raccoon = createSprite(racconSprites[frameIdx], "assets/raccoon.png");
        dog     = createSprite(dogSprites[dogFrameIndex], "assets/dog.png");
        panda = createSprite(pandasSprites[frameIdx], "assets/panda.png");

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

        sfSprite_setPosition(panda, (sfVector2f)
        {
            pandaPosX,
            pandaPosY
        });

        sfRenderWindow_drawSprite(window, dog, NULL);
        sfRenderWindow_drawSprite(window, raccoon, NULL);
        sfRenderWindow_drawSprite(window, panda, NULL);
        sfRenderWindow_drawSprite(window, live, NULL);

        /* ================================================  controle de colisões com dog x vidas ================================================ */
        if( num_lives > 0 ) {
            if(verificaColisao(raccoon, dog, RACCOON_WIDTH, RACCOON_HEIGHT, DOG_WIDTH, DOG_HEIGHT)) {
                    str[1]=sprintf(str, "%d", --num_lives);
                    posX = 0.0f; posY = 0.0f;
            }
        } else {
            sfText_setString(text, "game over");
            sfText_setPosition(text, (sfVector2f)
            {
                280.0f, 200.0f
            });
        }
        /* ================================================ fim controle de colisão com dog ===================================================== */

        if(raccoon != NULL)
        {
            raccoonPos = sfSprite_getPosition(raccoon);
        }

        if(dog!= NULL)
        {
            dogPos = sfSprite_getPosition(dog);
        }

        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_display(window);
    }

    sfSprite_destroy(raccoon);
    sfSprite_destroy(live);
    sfSprite_destroy(dog);
    sfRenderWindow_destroy(window);
}

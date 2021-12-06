#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Window.h>
#include <SFML/System/Clock.h>
#include <stdbool.h>

#include "constants.h"

sfSprite* createSprite(sfIntRect spriteFrame, char* imagePath)
{
    sfTexture *texture = sfTexture_createFromFile(imagePath, NULL);
    sfSprite *draw = sfSprite_create();

    sfSprite_setTexture(draw, texture, 0);
    sfSprite_setTextureRect(draw, spriteFrame);

    return draw;
}

float generateRandomPosition()
{
    int lowerNumber = 100, biggerNumber = 500;

    return (rand() % (biggerNumber - lowerNumber + 1)) + lowerNumber;
}

bool colisionVerify(sfSprite * first, sfSprite * second, float FIRST_WIDTH, float FIRST_HEIGHT, float SECOND_WIDTH, float SECOND_HEIGHT)
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
    int acumulador = 0;
    float points = 0;
    char str[1];
    char totalPoints[1];

    bool hasPickedMeteor = false;
    bool invertDogPosition = false;

    sfFont *font = sfFont_createFromFile("arialregular.ttf");
    sfText *text = sfText_create();
    sprintf(str, "%d", num_lives);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 38);
    sfText_setFillColor(text, sfBlack);
    sfText_setPosition(text, (sfVector2f)
    {
        777.0f, 0.9f
    });

    sfFont *pointFont = sfFont_createFromFile("arialregular.ttf");
    sfText *pointText = sfText_create();
    sprintf(totalPoints, "%.1f", points);
    sfText_setFont(pointText , pointFont);
    sfText_setCharacterSize(pointText, 38);
    sfText_setFillColor(pointText, sfBlue);
    sfText_setPosition(pointText, (sfVector2f)
    {
        400.0f, 0.9f
    });


    srand(time(NULL));
    sfClock *clock = sfClock_create();
    sfRenderWindow *window;
    sfVideoMode videoMode = {800, 600, 32};
    window = sfRenderWindow_create(videoMode, "Raccoon Game", sfResize | sfClose, NULL);

    int frameIdx = 0;
    int dogFrameIndex = 0;

    // Sprite X|Y positions
    float raccoonPosX = 0.0f, raccoonPosY = 0.0f;
    float dogPosX = 830.0f, dogPosY = generateRandomPosition();
    float pandaPosX = 830.0f, pandaPosY = generateRandomPosition();
    float paperManPosX = 830.0f, paperManPosY = generateRandomPosition();
    float chocolatePosX = 400.0f, chocolatePosY = generateRandomPosition();
    float crownPosX = 250.0f, crownPosY = 250.0f;
    float meteorPosX = 900.0f, meteorPosY = -100.0f;

    // Sprites
    sfSprite *raccoon;
    sfVector2f raccoonPos;

    sfSprite *dog;
    sfVector2f dogPos;

    sfSprite *panda;
    sfVector2f pandaPos;

    sfSprite *meteor;
    sfVector2f meteorPosition;

    sfSprite *chocolate;
    sfVector2f chocolatePosition;

    // TODO: add crown functionality
    sfSprite *crown;
    sfVector2f crownPosition;

    sfSprite *paperMan;
    sfVector2f paperManPosition;

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

    sfVector2f raccoonTAM;
    raccoonTAM.x = 1.5;
    raccoonTAM.y = 1.5;

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

        if(acumulador >= 100){
            raccoonTAM.x = 1.5;
            raccoonTAM.y = 1.5;
            hasPickedMeteor = false;
        }

        sfText_setString(text, str);
        sfText_setString(pointText, totalPoints);

        sfTime time = sfClock_getElapsedTime(clock);

        if(sfKeyboard_isKeyPressed(sfKeyRight))
        {
            if(raccoonPos.x < 690)
            {
                raccoonPosX += 8.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyLeft))
        {
            if(raccoonPos.x != -15)
            {
                raccoonPosX -= 8.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyUp))
        {
            if(raccoonPos.y > -20)
            {
                raccoonPosY -= 8.0;
            }
        }

        if(sfKeyboard_isKeyPressed(sfKeyDown))
        {
            if(raccoonPos.y < 530)
            {
                raccoonPosY += 8.0;
            }
        }

        if(time.microseconds >= 150000)
        {
            frameIdx++;
            dogFrameIndex++;

            if(frameIdx >= 2) frameIdx = 0;

            if(dogFrameIndex >= 2) dogFrameIndex = 0;

            paperManPosX -= 10.0;

            dogPosX -= 10.0;

            if(dogPos.y <= 0)
            {
                invertDogPosition = true;
            }

            if(dogPos.y >= 545)
            {
                invertDogPosition = false;
            }

            if(!invertDogPosition && dogPos.y >= 0)
            {
                dogPosY -= 10.0;
            }


            if(invertDogPosition && dogPos.y <= 545)
            {
                dogPosY += 10.0f;
            }

            meteorPosY += 10.0;
            meteorPosX -= 10.0;

            pandaPosX -= 10.0;
            pandaPosY += 3.0;

            chocolatePosY += 10.0;

            sfClock_restart(clock);
        }

        if(time.microseconds >= 10000000)
        {
            chocolatePosX = generateRandomPosition();
            chocolatePosY = generateRandomPosition();
        }

        raccoon = createSprite(racconSprites[frameIdx], "assets/raccoon.png");
        dog     = createSprite(dogSprites[dogFrameIndex], "assets/dog.png");
        panda = createSprite(pandasSprites[frameIdx], "assets/panda.png");
        paperMan = createSprite(paperManSprites[frameIdx], "assets/paperman.png");
        chocolate = createSprite(chocolateSprite, "assets/chocolate.png");
        meteor = createSprite(meteoriteSprite, "assets/meteor.png");

        sfSprite_scale(chocolate, (sfVector2f)
        {
            0.1f, 0.1f
        });
        sfSprite_scale(raccoon, (sfVector2f)
        {
            raccoonTAM.x, raccoonTAM.y
        });

        sfSprite_scale(meteor, (sfVector2f)
        {
            0.30f, 0.30f
        });

        sfRenderWindow_clear(window, sfWhite);

        if(dogPos.x < -200)
        {
            dogPosY = generateRandomPosition();
            dogPosX = 830.0f;
        }

        if(paperManPosition.x < -200)
        {
            paperManPosY = generateRandomPosition();
            paperManPosX = 830.0f;
        }

        if(meteorPosition.x < -200)
        {
            meteorPosX = generateRandomPosition();
            meteorPosY = -100.0f;
        }

        if(pandaPos.x < -200)
        {
            pandaPosX = generateRandomPosition();
            pandaPosY = -100.0f;
        }

        if(chocolatePosition.y >= 600) {
            chocolatePosX = generateRandomPosition();
            chocolatePosY = generateRandomPosition();
        }

        sfSprite_setPosition(raccoon, (sfVector2f)
        {
            raccoonPosX, raccoonPosY
        });

        sfSprite_setPosition(dog, (sfVector2f)
        {
            dogPosX, dogPosY
        });

        sfSprite_setPosition(panda, (sfVector2f)
        {
            pandaPosX,
            pandaPosY
        });

        sfSprite_setPosition(paperMan, (sfVector2f)
        {
            paperManPosX,
            paperManPosY
        });

        sfSprite_setPosition(chocolate, (sfVector2f)
        {
            chocolatePosX,
            chocolatePosY
        });

        sfSprite_setPosition(meteor, (sfVector2f)
        {
            meteorPosX,
            meteorPosY
        });

        sfRenderWindow_drawSprite(window, chocolate, NULL);
        sfRenderWindow_drawSprite(window, meteor, NULL);
        sfRenderWindow_drawSprite(window, paperMan, NULL);
        sfRenderWindow_drawSprite(window, dog, NULL);
        sfRenderWindow_drawSprite(window, raccoon, NULL);
        sfRenderWindow_drawSprite(window, panda, NULL);
        sfRenderWindow_drawSprite(window, live, NULL);

        /* ================================================  controle de colisões ================================================ */
        if(num_lives > 0)
        {
            if(colisionVerify(raccoon, dog, RACCOON_WIDTH, RACCOON_HEIGHT, DOG_WIDTH, DOG_HEIGHT))
            {
                sprintf(str, "%d", num_lives -= 2);
                sprintf(totalPoints, "%.1f", points);
                raccoonPosX = 0.0f;
                raccoonPosY = 0.0f;
            }

            if(colisionVerify(raccoon, meteor, RACCOON_WIDTH, RACCOON_HEIGHT, METEOR_WIDTH, METEOR_HEIGHT))
            {
                acumulador = 0;
                raccoonTAM.x = 3.5;
                raccoonTAM.y = 3.5;
                hasPickedMeteor = true;
            }

            if(colisionVerify(raccoon, paperMan, RACCOON_WIDTH, RACCOON_HEIGHT, PAPERMAN_WIDTH, PAPERMAN_HEIGHT))
            {
                sprintf(str, "%d", --num_lives);
                sprintf(totalPoints, "%.1f", points);
                raccoonPosX = 0.0f;
                raccoonPosY = 0.0f;
            }

            if(colisionVerify(raccoon, panda, RACCOON_WIDTH, RACCOON_HEIGHT, PANDA_WIDTH, PANDA_HEIGHT))
            {
                sprintf(str, "%d", num_lives -= num_lives);
                sprintf(totalPoints, "%.1f", points);
                raccoonPosX = 0.0f;
                raccoonPosY = 0.0f;
            }

            if(colisionVerify(raccoon, chocolate, RACCOON_WIDTH, RACCOON_HEIGHT, CHOCOLATE_WIDTH, CHOCOLATE_HEIGHT) && num_lives < 5)
            {
                // TODO: validate why chocolate sprite isn't destroyed
                chocolatePosX = generateRandomPosition();
                chocolatePosY = generateRandomPosition();
                sprintf(str, "%d", ++num_lives);
                sprintf(totalPoints, "%.1f", points);
            }
        }
        else
        {
            sfText_setString(text, "Game Over");
            sfText_setPosition(text, (sfVector2f)
            {
                280.0f, 200.0f
            });
            sfSprite_destroy(live);
            raccoonPosX = -100.0f;
            chocolatePosX = -100.0f;
            paperManPosX = -100.0f;
            pandaPosX = -100.0f;
            dogPosX = -100.0f;
            meteorPosX = -100.0f;
        }
        /* ================================================ fim controle de colisão ===================================================== */

        if(raccoon != NULL)
        {
            raccoonPos = sfSprite_getPosition(raccoon);
        }

        if(dog != NULL)
        {
            dogPos = sfSprite_getPosition(dog);
        }

        if(paperMan != NULL)
        {
            paperManPosition = sfSprite_getPosition(paperMan);
        }

        if(meteor != NULL)
        {
            meteorPosition = sfSprite_getPosition(meteor);
        }

        if(panda != NULL)
        {
            pandaPos = sfSprite_getPosition(panda);
        }

        if(chocolate != NULL) {
            chocolatePosition = sfSprite_getPosition(chocolate);
        }

        if(hasPickedMeteor) acumulador++;
        points+=0.05;
        sprintf(totalPoints, "%.1f", points);

        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_drawText(window, pointText, NULL);
        sfRenderWindow_display(window);
    }

    sfSprite_destroy(raccoon);
    sfSprite_destroy(live);
    sfSprite_destroy(dog);
    sfSprite_destroy(meteor);
    sfSprite_destroy(panda);
    sfSprite_destroy(paperMan);
    sfSprite_destroy(chocolate);
    sfRenderWindow_destroy(window);
}

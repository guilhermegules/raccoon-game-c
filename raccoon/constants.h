#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define RACCOON_WIDTH     48
#define RACCOON_HEIGHT    48
#define RACCON_SPRITES    3

#define DOG_HEIGHT        48
#define DOG_WIDTH         48
#define DOG_SPRITES       3

#define PANDA_HEIGHT      48
#define PANDA_WIDTH       48
#define PANDA_SPRITES     3

#define PAPERMAN_HEIGHT   49.66
#define PAPERMAN_WIDTH    44.5
#define PAPERMAN_SPRITES  3

#define CHOCOLATE_WIDTH   512
#define CHOCOLATE_HEIGHT  512

#define METEOR_WIDTH      160
#define METEOR_HEIGHT     160

#define CROWN_WIDTH       800
#define CROWN_HEIGHT      600

#define STAR_WIDTH 578
#define STAR_HEIGHT 578

sfIntRect racconSprites[RACCON_SPRITES] =
{
    {48,   96, RACCOON_WIDTH, RACCOON_HEIGHT},
    {96,   96, RACCOON_WIDTH, RACCOON_HEIGHT},
    {144,  96, RACCOON_WIDTH, RACCOON_HEIGHT},
};

sfIntRect dogSprites[DOG_SPRITES] =
{
    {48,  48, DOG_WIDTH, DOG_HEIGHT},
    {96,  48, DOG_WIDTH, DOG_HEIGHT},
    {144, 48, DOG_WIDTH, DOG_HEIGHT},
};

sfIntRect pandasSprites[PANDA_SPRITES] =
{
    {432, 240, PANDA_WIDTH, PANDA_HEIGHT},
    {480, 240, PANDA_WIDTH, PANDA_HEIGHT},
    {528, 240, PANDA_WIDTH, PANDA_HEIGHT},
};

sfIntRect meteoriteSprite = { 0, 0, METEOR_WIDTH,    METEOR_HEIGHT    };

sfIntRect chocolateSprite = { 0, 0, CHOCOLATE_WIDTH, CHOCOLATE_HEIGHT };

sfIntRect crownSprite     = { 0, 0, CROWN_WIDTH,     CROWN_HEIGHT     };

sfIntRect starSprite = {0, 0, STAR_WIDTH, STAR_HEIGHT};

sfIntRect paperManSprites[PAPERMAN_SPRITES] =
{
    {44.5,  0, PAPERMAN_WIDTH, PAPERMAN_HEIGHT},
    {89,    0, PAPERMAN_WIDTH, PAPERMAN_HEIGHT},
    {133.5, 0, PAPERMAN_WIDTH, PAPERMAN_HEIGHT},
};

#endif // CONSTANTS_H_INCLUDED

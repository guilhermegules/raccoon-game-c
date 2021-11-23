#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>

int main()
{
    sfRenderWindow *window;
    sfVideoMode videoMode = {800,600,32};
    window = sfRenderWindow_create(videoMode, "T-Game", sfResize | sfClose, NULL);
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
        sfRenderWindow_clear(window, sfBlue);
        sfRenderWindow_display(window);
    }
}

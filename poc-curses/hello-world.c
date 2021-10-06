#include <ncurses.h>
#include <stdlib.h>

int main()
{
  initscr();

  addstr("-----------------\n| Hello |\n| World | ncurses Demo  |\n-----------------\n\n");
  refresh();

  addstr("\npress any key to exit...");
  refresh();

  getch();

  endwin();

  return EXIT_SUCCESS;
}
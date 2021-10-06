#include <stdlib.h>
#include <ctype.h>
#include <curses.h>

#define KEYS_LENGTH 25

/*  Struct to hold keycode/keyname information  */
struct KeyDescription
{
  int code;
  char name[20];
};

/*  Returns a string describing a character passed to it  */
char *typedKeyHandler(int charCode)
{

  /*  Define a selection of keys we will handle  */
  static struct KeyDescription keys[KEYS_LENGTH] = {
      {KEY_UP, "Up arrow"},
      {KEY_DOWN, "Down arrow"},
      {KEY_LEFT, "Left arrow"},
      {KEY_RIGHT, "Right arrow"},
      {KEY_HOME, "Home"},
      {KEY_END, "End"},
      {KEY_BACKSPACE, "Backspace"},
      {KEY_IC, "Insert"},
      {KEY_DC, "Delete"},
      {KEY_NPAGE, "Page down"},
      {KEY_PPAGE, "Page up"},
      {KEY_F(1), "Function key 1"},
      {KEY_F(2), "Function key 2"},
      {KEY_F(3), "Function key 3"},
      {KEY_F(4), "Function key 4"},
      {KEY_F(5), "Function key 5"},
      {KEY_F(6), "Function key 6"},
      {KEY_F(7), "Function key 7"},
      {KEY_F(8), "Function key 8"},
      {KEY_F(9), "Function key 9"},
      {KEY_F(10), "Function key 10"},
      {KEY_F(11), "Function key 11"},
      {KEY_F(12), "Function key 12"},
      {KEY_ENTER, "Enter"},
      {-1, "<unsupported>"}};

  static char keych[2] = {0};

  if (isprint(charCode) && !(charCode & KEY_CODE_YES))
  {
    /*  If a printable character  */
    keych[0] = charCode;
    return keych;
  }

  /*  Non-printable, so loop through our array of structs  */
  int index = 0;

  for (index = 0; index < KEYS_LENGTH; index++)
  {
    if (keys[index].code == charCode)
    {
      return keys[index].name;
    }
  }

  return keys[index].name;
}

int main()
{

  WINDOW *mainwin;
  int inputedValue;

  /*  Initialize ncurses  */
  mainwin = initscr();

  if (mainwin == NULL)
  {
    fprintf(stderr, "Error initializing ncurses.\n");
    exit(EXIT_FAILURE);
  }

  noecho();              /*  Turn off key echoing                 */
  keypad(mainwin, TRUE); /*  Enable the keypad for non-char keys  */

  /*  Print a prompt and refresh() the screen  */
  mvaddstr(5, 10, "Press a key ('q' to quit)...");
  mvprintw(7, 10, "You pressed: ");
  refresh();

  /*  Loop until user presses 'q'  */
  while ((inputedValue = getch()) != 'q')
  {
    /*  Delete the old response line, and print a new one  */
    deleteln();
    mvprintw(7, 10, "You pressed: 0x%x (%s)", inputedValue, typedKeyHandler(inputedValue));
    refresh();
  }

  /*  Clean  */
  delwin(mainwin);
  endwin();
  refresh();

  return EXIT_SUCCESS;
}
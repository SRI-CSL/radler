#include "keyboard.h"
#include <ncurses.h>

WINDOW *mainWin;

Keyboard::Keyboard() 
{
  mainWin = initscr();
  keypad(stdscr, true);
  cbreak();
  noecho();

  wprintw(mainWin, "- Controls -                                         \n");
  wprintw(mainWin, "   Up   / Down  Arrows         -- Speed  Up / Down   \n");
  wprintw(mainWin, "   Left / Right Arrows         -- Turn Left / Right  \n");
  wprintw(mainWin, "   Other Keys                  -- Restart            \n");
  wprintw(mainWin, "- Latest Teleop -                                    \n");
  move(5,0);
}

void Keyboard::step(const radl_in_t * in, const radl_in_flags_t* iflags, radl_out_t * out, radl_out_flags_t* oflags)
{
  int key = getch();
  switch (key) { 
    case KEY_UP:
      wprintw(mainWin, "   Speed UP\n");
      break;
    case KEY_DOWN:
      wprintw(mainWin, "   Speed DOWN\n");
      break;
    case KEY_LEFT:
      wprintw(mainWin, "   Turn LEFT\n");
      break;
    case KEY_RIGHT:
      wprintw(mainWin, "   Turn RIGHT\n");
      break;
    default:
      wprintw(mainWin, "   RESET\n");
      break;
  }
  move(5,0);

  out->key->value = key;
}

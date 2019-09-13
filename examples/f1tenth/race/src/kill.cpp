#include "kill.h"
#include <std_msgs/Bool.h>
#include <ncurses.h>

WINDOW *mainWin;

Kill::Kill() 
{
  pub = h.advertise<std_msgs::Bool>("/eStop", 1);

  mainWin = initscr();
  keypad(stdscr, true);
  cbreak();
  noecho();

  wprintw(mainWin, "- Controls -                            \n");
  wprintw(mainWin, "   s              -- Emergency Stop     \n");
  wprintw(mainWin, "   n              -- Normal Operation   \n");
  wprintw(mainWin, "- Current Mode -                        \n");
  wprintw(mainWin, "   Normal Operation                     \n");
  move(4,0);
}

void Kill::step(const radl_in_t * in, const radl_in_flags_t* iflags, radl_out_t * out, radl_out_flags_t* oflags)
{
  int key = getch();
  std_msgs::Bool eStop;

  switch (key) { 
    case 's':
      eStop.data = true; 
      pub.publish(eStop);
      wprintw(mainWin, "   Emergency STOP\n");
      break;
    case 'n': 
      eStop.data = false; 
      pub.publish(eStop);
      wprintw(mainWin, "   Normal Operation\n");
      break;
    default:
      break;
  }
  move(4,0);
}

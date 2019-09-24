#include "kill.h"
#include <ncurses.h>

WINDOW *mainWin;

Kill::Kill() 
{
	h = rclcpp::Node::make_shared("kill");
	pub = h->create_publisher<std_msgs::msg::Bool>("eStop", rmw_qos_profile_default);

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
  std_msgs::msg::Bool eStop;

  switch (key) { 
    case 's':
      eStop.data = true; 
      this->pub->publish(eStop);
      wprintw(mainWin, "   Emergency STOP\n");
      break;
    case 'n': 
      eStop.data = false; 
      this->pub->publish(eStop);
      wprintw(mainWin, "   Normal Operation\n");
      break;
    default:
      break;
  }
  move(4,0);
}

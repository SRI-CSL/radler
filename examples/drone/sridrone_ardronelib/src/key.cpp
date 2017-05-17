#include "ros/ros.h"
#include "key.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

using namespace std; 

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

Key::Key() {
    cout << "- Controls -                     " << endl;
    cout << "   'Space' -- Emergency Reset    " << endl;
    cout << "   '+'     -- Takeoff            " << endl;
    cout << "   '-'     -- Landing            " << endl;
    cout << "   'f/b'   -- Forward/Backward   " << endl;
    cout << "   'u/d'   -- Up/Down            " << endl;
    cout << "   'l/r'   -- Move Left/Right    " << endl;
    cout << "   '[/]'   -- Turn Left/Right    " << endl;
    cout << "   't'     -- Tag follwoing      " << endl;
}

void Key::step(const radl_in_t * in, const radl_in_flags_t* iflags,
               radl_out_t * out, radl_out_flags_t* oflags) 
{
	int key; 
	key = getch(); 

	if ( *RADL_THIS->print_data ) {
        cout << "key = " << (char)key << endl;
	}

	out->key_event->key = key;
}

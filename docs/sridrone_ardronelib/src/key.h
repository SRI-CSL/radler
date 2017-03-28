#include RADL_HEADER

#define KEY_TAKEOFF   43 
#define KEY_LANDING   45  
#define KEY_RESET     32
#define KEY_UP        117 
#define KEY_DOWN      100 
#define KEY_FORWARD   102 
#define KEY_BACKWARD  98
#define KEY_LEFT      108
#define KEY_RIGHT     114
#define KEY_TURNLEFT  91 
#define KEY_TURNRIGHT 93
#define KEY_HOVER     61 

class Key {
 	public:
		Key();
  		void step(const radl_in_t*, const radl_in_flags_t*, radl_out_t*, radl_out_flags_t*);
};

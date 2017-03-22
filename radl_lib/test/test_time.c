#include "radl_lib.h"
#include <unistd.h>

int main(){
	radl_init_lib();
	long long datediff = time(NULL) - radl_gettime()/1000000000;
	radl_duration_t datedelta = radl_gettime() - radl_gettime();
	int correct = -1 <= datediff && datediff <= 0 && datedelta > -2000;
	return !correct;
}

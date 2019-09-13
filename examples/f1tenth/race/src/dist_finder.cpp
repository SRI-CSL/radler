#include "dist_finder.h" 
#include "math.h"
#include "sensor_msgs/LaserScan.h"

using namespace std;

int theta = 50;
const double PI = 3.141592653589793238463;
double swing;
int a_idx, b_idx;

sensor_msgs::LaserScan::ConstPtr scan;

void subhandler(const sensor_msgs::LaserScan::ConstPtr& data)
{
  scan = data; 
}

DistFinder::DistFinder()
{
  swing = theta * PI / 180;
  a_idx = (theta + 45) * 4;
  b_idx = 45 * 4;

	sub = h.subscribe("/scan", 1, subhandler);
}

void DistFinder::step(const radl_in_t * in, const radl_in_flags_t* inflags, radl_out_t * out, radl_out_flags_t* outflags)
{
  double a, b;
  double tangle, alpha;
  double AB, CD;
  double AC = *RADL_THIS->horizon;
  
  if(scan) 
  {
    a = scan->ranges[a_idx];
    b = scan->ranges[b_idx];
    tangle = (a * cos(swing) - b) / (a * sin(swing));
    alpha = atan(tangle);

    AB = b * cos(alpha);
    CD = AB + AC * sin(alpha);

    out->error->value = CD - *RADL_THIS->desired_trajectory;
    cout << "Error: " << out->error->value << endl;
  }
}

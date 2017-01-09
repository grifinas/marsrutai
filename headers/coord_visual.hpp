#ifndef coord_visual_H
#define coord_visual_H

#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

#include <math.h>
#include <cstdlib>


int long2tilex(double lon, int z);
int lat2tiley(double lat, int z);
bool isCurlAvailable();


#endif
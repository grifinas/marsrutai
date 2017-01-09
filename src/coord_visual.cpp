#include "coord_visual.hpp"

inline int long2tilex(double lon, int z){ 
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
}

inline int lat2tiley(double lat, int z){ 
    return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
}

inline bool isCurlAvailable(){
    int exit_code = system("curl --version");
    if(exit_code == 0){
        return true;
    }
    return false;
}


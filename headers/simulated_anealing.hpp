#ifndef simulated_anealing_H
#define simulated_anealing_H

#include "math.h"
#include <chrono>

#include "vertex.hpp"
#include "graph.hpp"
#include "utils.hpp"


double acceptanceProbability(int newEn, int oldEn, double temp);
Tour SimulatedAnealing(Graph &gg, Tour T);

#endif
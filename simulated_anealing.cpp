double acceptanceProbability(int newEn, int oldEn, double temp){
    // if (newEn < oldEn) {
    //     return 1.0;
    // }
    // If the new solution is worse, calculate an acceptance probability
    return exp((oldEn - newEn) / temp);
}

Tour SimulatedAnealing(Graph &gg, int start, Tour T){
    //new random seed
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(0, 1);

    // Set initial temp
    double temp = ::current_count * ::current_count * ::max_edges;

    // Cooling rate
    double coolingRate = 0.001;

    Tour currentSolution = T;
    Tour best = T;

    int itterations = 0;

    while(temp > 1){
        itterations++;
        // Create new neighbour tour
        Tour newSolution = currentSolution;

        // Get a random positions in the tour
        int tourPos1 = (int) std::rand()%newSolution.size();
        int tourPos2 = (int) std::rand()%newSolution.size();

        newSolution = twoOptSwap(newSolution, tourPos1, tourPos2);
        // std::cout << "swap: [" << tourPos1 << "]" << newSolution[tourPos1] << " and [" << tourPos2 << "]" << newSolution[tourPos2] << " result " << std::endl;
        // printPath(newSolution, "ns ");
        // break;

        int new_energy = aStarGetTotalPathWeight(newSolution, true);
        int old_energy = aStarGetTotalPathWeight(currentSolution, true);

        double r = unif(rng); // 0 < r < 1
        if (acceptanceProbability(new_energy, old_energy, temp) > r) {
            currentSolution = newSolution;
        }

        if (aStarGetTotalPathWeight(currentSolution) < aStarGetTotalPathWeight(best)) {
            best = currentSolution;
        }

        temp *= 1-coolingRate;
    }

    std::cout << "sa iterations: " << itterations << std::endl;
    return best;
}



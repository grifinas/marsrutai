double acceptanceProbability(int newEn, int oldEn, double temp){
    if (newEn < oldEn) {
        return 1.0;
    }
    // If the new solution is worse, calculate an acceptance probability
    return exp((oldEn - newEn) / temp);
}

Tour SimulatedAnealing(Graph &gg, int start, Tour T){
    // Set initial temp
    double temp = 10000;

    // Cooling rate
    double coolingRate = 0.003;

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

        int new_energy = aStarGetTotalPathWeight(newSolution);
        int old_energy = aStarGetTotalPathWeight(currentSolution);

        if (acceptanceProbability(new_energy, old_energy, temp) > std::rand()) {
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



Tour GeneticAlgorithm(Graph &gg, int start, Tour &t1){
    Tour t2;
    for(int i=1, from=start; i<gg.vertexCount; from=i, i++){
        if(start != i){
            aStarRoute(t2, gg[from], gg[i]);
        }
    }

    
}
//implementacija skamba nelogiskai, veiksminga tik pilnam grafe??

Tour two_opt(Tour t){

}

Tour twoOptSwap(Tour T, int from, int to){
    Vertex *tmp;
    if(from > to){
        from += to;
        to = from-to;
        from -= to;
    }
    for(from; from < to; from++, to--){
        tmp = T[from];
        T[from] = T[to];
        T[to] = tmp;
    }

    return T;
}

// if (
//     solution[i-1]->dist(solution[j]) + solution[i]->dist(solution[j+1]) 
//     < 
//     solution[i-1]->dist(solution[i]) + solution[j]->dist(solution[j+1])
// )
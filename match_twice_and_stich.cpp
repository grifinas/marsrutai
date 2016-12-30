Tour MatchTwiceAndStich(Graph gg){
    //if number of points is odd
    int remove_id = 0;
    if(gg.vertexCount % 2 == 1 && gg.vertexCount > 2){
        //from 1 to vertex count 
        remove_id = std::rand() % gg.vertexCount + 1;
        gg[remove_id] -> disable();
    }

    //min weight matching

    //reinsert droped point
    if(remove_id){
        gg[remove_id] -> enable();
    }
}
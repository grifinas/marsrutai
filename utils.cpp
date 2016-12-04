void printPath(vector<Vertex*> ll, string name = "", bool showSize = true){
    int w;
    cout << name;
    for(int i=0; i<ll.size(); i++){
        cout << ll[i] -> getId() << " ==";
        if(showSize && i < ll.size()-1){
            Edge e = ll[i] -> getNeighbour(ll[i+1]);
            w = e.weight;
            cout << "(" << w << ")";
        }
        cout << ">> ";
    }
    cout << "total path weight: " << aStarGetTotalPathWeight(ll) << endl;
}

void printMap(std::map<Vertex*, auto> map, string name = ""){
    cout << "===" << name << "===" << endl;
    for(auto const& i : map){
        cout << "[id:" << i.first -> getId() << "] = " << i.second << endl; 
    }
    cout << endl;
}

void timestamp(bool renew = false){
    static int timesTimeStamped = 0;
    auto now = std::chrono::high_resolution_clock::now(); 
    static auto t_start = now;
    if(timesTimeStamped > 0){ 
        std::cout <<  std::chrono::duration<double, std::milli>(now-t_start).count() << " ms" << std::endl;
        if(renew){
            t_start = now;
        }
    }
    ++timesTimeStamped;
}
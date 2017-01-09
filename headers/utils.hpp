#ifndef utils_H
#define utils_H

#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>

#include "coord_visual.hpp"
#include "vertex.hpp"
#include "graph.hpp"

#include "my_globals.hpp"

void printPath(Tour ll, std::string name = "", bool showSize = true);
void printMap(std::map<Vertex*, auto> map, std::string name = "");
void printVector(std::vector<auto> v);
void timestamp(bool renew = false);
Graph* generateRandomGraph(int v_count = 0, int link_count = 10);
void exportGraphToCSV(Graph &gg, std::string name = "");
void swap(int &a, int &b);
// std::ostream& recursiveMapPrint(std::ostream& os, const auto not_map, int recurse = 1);
// std::ostream& recursiveMapPrint(std::ostream& os, const std::map<auto, auto> &M, int recurse = 0);
// std::ostream& operator<<(std::ostream& os, const std::map<auto, auto> &M);
std::ostream& operator<<(std::ostream& os, Vertex *V);
Tour twoOptSwap(Tour T, int from, int to);

// std::ostream& operator<<(std::ostream& os, const std::map<auto, auto> &M);

template<class T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T> &V){
    for(int i=0; i<V.size(); i++){
        os << "[" << i << "]" << " => \r\n\t" << V[i] << std::endl; 
    }
    return os;
}


template<class T>
inline std::vector<T> operator-(std::vector<T> A, std::vector<T> B){
    std::vector<T> R;
    for(auto const &i : A){
        bool found = false;
        for(auto const &j : B){
            if(i == j){
                found = true;
            }
        }
        if(!found){
            R.push_back(i);
        }
    }
    return R;
}

template<class K, class V> 
inline std::map<K, V> operator-(std::map<K, V>A, std::map<K, V>B){
    std::map<K, V> R;
    for(auto const &i : A){
        if(B.find(i.first) == B.end()){
            R[i.first] = i.second;
        }
    }
    return R;
}

template<class K, class V>
inline std::ostream& operator<<(std::ostream& os, const std::map<K, V> &M){
    recursiveMapPrint(os, M);
    return os;
}

template<class K>
std::ostream& recursiveMapPrint(std::ostream& os, const K not_map, int recurse = 1){
    std::string tabulation;
    for(int i=0; i<recurse; i++){
        tabulation += "\t";
    }
    os << tabulation << not_map;
    return os;
}

template<class K, class V>
std::ostream& recursiveMapPrint(std::ostream& os, const std::map<K, V> &M, int recurse = 1){
    std::string tabulation;
    for(int i=0; i<recurse; i++){
        tabulation += "\t";
    }
    int itte=0;
    for(auto const &i : M){
        if(i.first != nullptr){
            os << tabulation << "[" << i.first << "] => \r\n";
            recursiveMapPrint(os, i.second, recurse+1);
        }else{
            os << tabulation << "[null] => \r\n";
        }
        os << "\r\n";
    }
    return os;
}

#endif
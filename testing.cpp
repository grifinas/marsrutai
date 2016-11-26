//comment
/*
    multiline comment
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main(){
    cout << "hello world" << endl;

    vector <int> jj;    

    jj.push_back(7);

    cout << "v" << jj.at(0) << endl;

    return 0;
}
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <utility>
#define ordem 8
using namespace std;
typedef vector<pair<int,int> > Caminho;

int main(int argc, char const *argv[]) {

//map<pair<int,int>,int> m;

//m.insert(make_pair(par,1));

//cout <<  << ": "<< << endl;
    
    //typedef vector<pair<int,int> > Caminho;
    
    Caminho car;
    car.push_back(make_pair(4,5));
    
    cout << car[0].first << ": " << car[0].second <<endl;
    
  return 0;
}

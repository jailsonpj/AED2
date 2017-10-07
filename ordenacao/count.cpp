#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#define SENTINELA -1
#include <climits>
#include <cmath>

using namespace std;

template <typename T>
void print(vector<T> &v){
  for (int i = 1; i < v.size(); i++) {
      cout << v[i] << ", ";
  }
  cout << "\n";
}



template <typename T>
void countingSort(vector<T> &v,vector<T> &b,int k){
    
    vector<int> c(k+1);
    
    for(int i=0;i<k;i++){
        c[i] = 0;
    }
    
    for(int j=1;j<= v.size()-1;j++){
        c[v[j]] = c[v[j]] + 1;
    }
    
    for(int i=1;i<=k;i++){
        c[i] = c[i] + c[i-1];
    }
    
    for(int j=v.size(); j>=1; j--){
        b[c[v[j]]] = v[j];
        c[v[j]] = c[v[j]] - 1;
    
    }
}
    



int main(int argc, char const *argv[]) {
  
    vector<int> v = {-1, 2,5,3,0,2,3,0,3};
    vector<int> b(v.size());
    int k = 5;
    print(v);
    countingSort(v,b,k);
    print(b);
    
    
  return 0;
}

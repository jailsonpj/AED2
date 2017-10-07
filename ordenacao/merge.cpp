#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#define SENTINELA -1
#include <climits>
#include <cmath>

using namespace std;

template <typename T>
void povoaRandom(vector<T> &v) {
    const int MAX_TAM = 30;
    const int novoTamanho  = (int) (rand()%MAX_TAM) + 1;
    const int MAX_VALOR = 100;
    int valor = 0;
    for (int i = 1; i <= novoTamanho; i++) {
        valor = (int) rand()%MAX_VALOR;
        v.push_back(valor);
    }
}

template <typename T>
void print(vector<T> &v){
  for (int i = 1; i < v.size(); i++) {
      cout << v[i] << ", ";
  }
  cout << "\n";
  cout << v[v.size() - 1] << "\n";
}


template <typename T>
void merge(vector<T> &v, int p, int q,int r){ //função Merge usada no Merge Sort
        int n1 = q-p+1;
        int n2 = r-q;
        
        vector<int> L(n1+2);
        vector<int> R(n2+2);
        
        int i,j;
        
        for(i=1;i<=n1;i++){
        
            L[i] = v[p+i-1];
        }
        
        for(j=1;j<=n2;j++){
            R[j] = v[q+j];
        }
        
        L[n1+1] = INT_MAX;
        R[n2+1] = INT_MAX;
        
        i = 1;
        j = 1;
        
        for(int k = p;k<=r;k++){
            v[k] = L[i] <= R[j];
            if(L[i] <= R[j]){
                v[k] = L[i];
                i++;
            }else{
                v[k] = R[j];
                j++;
            }
        }
}

template <typename T>
void mergeSort(vector<T> &v,int p,int r ){ //MergeSort
        if(p < r){
            int q = floor((p+r)/2);
            mergeSort(v,p,q);
            mergeSort(v,q+1,r);
            merge(v,p,q,r);
        }
}


int main(int argc, char const *argv[]) {
    srand( (unsigned)time(NULL) );

    vector<int> v = {SENTINELA};
    povoaRandom(v);
    print(v);
  
    mergeSort(v,0,v.size()-1);

    
  return 0;
}

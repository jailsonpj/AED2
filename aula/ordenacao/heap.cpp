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


int pai(int i){
    return i/2;
}

int esq (int i){
    return 2*i;
}

int dir(int i){
    return 2*i + 1;
}

template <typename T>
void heapfica (vector<T> &v,int i,int heapSize){
    
    int l = esq(i);
    int r = dir(i);
    int maior;
    int aux;
    
    if(l<= heapSize && v[l] > v[i]){
        maior = l;
    }else{
        maior = i;
    }
    
    if(r <= heapSize && v[r] > v[maior]){
        maior = r;
    }
    
    if(maior != i){
        //torca
        aux = v[i];
        v[i] = v[maior];
        v[maior] = aux;
        //troca(v[i],v[maior]);
        //chama recursivo
        heapfica(v,maior,heapSize);
    }
    
}

template <typename T>
void constroiHeap(vector<T> &v,int &heapSize){
    heapSize =  v.size() - 1;
    for(int i= (int)floor(heapSize/2); i>=1;i--){
        heapfica(v,i,heapSize);
    }
    
}

template <typename T>
void heapSort (vector<T> &v){
    int aux;
    cout<< "foi" << endl;
    int heapSize = 0;
    constroiHeap(v,heapSize);
    int N = (int) v.size() - 1;
    for(int i = N; i >= 2; i--){
        aux = v[1];
        v[1] = v[i];
        v[i] = aux;
        //swap(v[1],v[i]);
        heapSize--;
        heapfica(v,1,heapSize);
    }
    
}

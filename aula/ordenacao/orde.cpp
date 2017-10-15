#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#define SENTINELA -1
#include <climits>
#include <cmath>
#define TAM 5

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
void bubble (vector<T> &v){ //ordena vetor
  int aux;
  for(int i=v.size()-1;i>0;i--){
    for(int j=0;j<i;j++){
      if (v[j]>v[j+1]) {
        aux = v[j];
        v[j]=v[j+1];
        v[j+1] = aux;
      }
    }
  }
}

template <typename T>
void select(vector<T> &v) { //select sort
  int min;
  int tem;
  for(int i = 0;i < v.size()-1;i++){
    min = i;
    for(int j = i+1;j < v.size();j++){
      if (v[j] < v[min]) {
        min = j;
      }
    tem = v[i];
    v[i] = v[min];
    v[min] = tem;
    }
  }
}

template <typename T>
void insert(vector<T> &v){ //insert sort
  int x;
  int j;
  for(int i = 2;i <v.size(); i++){
    x = v[i];
    j = i-1;
    v[0] = x; //sentinela
    while(x < v[j]){
      v[j+1] = v[j];
      j = j-1;
    }
    v[j+1] = x;
  }
}

template <typename T>
void print(vector<T> &v){
  for (int i = 1; i < v.size(); i++) {
      cout << v[i] << ", ";
  }
  cout << "\n";
  //cout << v[v.size() - 1] << "\n";
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
  srand( (unsigned)time(NULL) );

    vector<int> v = {SENTINELA};
    povoaRandom(v);
    print(v);
  //bubble(v);
  //select(v);
    insert(v);
 // mergeSort(v,0,v.size()-1);
//heapSort(v);
    print(v);

   /*vector<int> v = {-1, 2,5,3,0,2,3,0,3};
    vector<int> b(v.size());
    int k = 5;
    //print(v);
    countingSort(v,b,k);
    print(b);*/
    
    
  return 0;
}

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void print(int v[],int n){
  for (int i = 0; i < n; i++) {
      cout << v[i] << " ";
  }
  cout << "\n";
  //cout << v[v.size() - 1] << "\n";
}

void heapify(int v[],int n,int i){
 
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    if (left < n && v[left] > v[largest]){
            largest = left;
    }
    
    if(right < n && v[right] > v[largest]){
            largest = right;
    }
    
    if(largest != i){
            swap(v[i],v[largest]);
            heapify(v,n,largest);
    }
    
}

void heapSort(int v[],int n){
 
    for(int i= n/2 - 1;i >=0;i--){
        heapify(v,n,i);
    }
    for(int i = n-1;i>=0;i--){
        swap(v[0],v[i]);
        heapify(v,i,0);
    }
    
}


/*
 * sizeof(v) = me retorna o tamanho do array *byte do tipo o array
   sizeof(v[0]) = me retorna o tamanho de byte do numero na posicao [0]
 */

int main(){
    
    int v[] = {12,11,13,5,6,7,4};
    int n = sizeof(v)/sizeof(v[0]); 
    cout << sizeof(v) << endl;
    cout << sizeof(v[0]) << endl;
    cout << n << endl;
    cout <<  n/2 - 1 << endl;
    print(v,n);
    heapSort(v,7);
    print(v,n);
    
  return 0;
}

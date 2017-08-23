#include<iostream>
//#include<cstdlib>
using namespace std;

template <typename T>
class Lista{
private:
  T *item; //vetor de itens
  int TAM;
  int n; //tamanho corrente
public:
  Lista ();
  Lista(int tam) {
      n = 0;
      TAM = tam;
      item = new T[TAM];
  }
  void insere(T *);
  void print();
  int getN();
  T* getItem(int);
};
template <typename T>
void Lista<T>::insere(T *x){
  if(n < TAM){
    n++;
    item[n] = *x;
  }else{
    cout << "Lista cheia!";
  }
}

template <typename T>
void Lista<T>::print(){
  for(int i = 1;i<= n; i++){
    item[i].print();
    cout<<endl;
  }
}

template <typename T>
int Lista<T>::getN(){
  return n;
}

template <typename T> //retorna um item
T* Lista<T>::getItem(int i){
  return &item[i];
}

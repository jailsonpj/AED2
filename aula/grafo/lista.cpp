#include <iostream>
#include <cstdlib>
using namespace std;


template <class T>
class No{
private:
  T item; //vetor de itens
  No* prox; //ponteiro para o proximo iostream
public:
  No(){
    this->prox = NULL;
  }
  No(T item){
    this->item = item;
    this->prox = NULL;
  }

  No* getProx(){
    return prox;
  }

  void setProx(No* prox){
    this->prox = prox;
  }

  T getItem(){
    return item;
  }

  void setItem(T item){
    this->item = item;
  }
};

template <class T>
class Lista{
private:
  No <T> *prim;
  No <T> *ult;
public:
  Lista(){
    prim = new No <T>; //Nó cabeça
    prim->setProx(NULL);
    ult = prim;
  }

  No<T>* getPrim(){
    return prim;
  }

  No<T>* getUlt(){
    return ult;
  }

  void insere(T item);
  void mostra();
  void destroy();
};

template <class T>
void Lista<T>::insere(T item){
  ult->setProx(new No<T>);
  ult = ult->getProx();
  ult->setProx(NULL);
  ult->setItem(item);
}

template <class T>
void Lista<T>::mostra(){
  No<T> *p = prim->getProx();
  while(p != NULL){
    cout << p->getItem() << " ";
    p = p->getProx();
  }
  cout << '\n';
}

template <class T>
void Lista<T>::destroy(){
  No<T> * p = getPrim()->getProx();
  while (p != NULL) {
      delete(p);
  }
  p = p->prox;
}

int main(int argc, char const *argv[]) {
  Lista <int> lista;

  lista.insere(1);
  lista.insere(2);
  lista.insere(3);
  lista.mostra();

  return 0;
}

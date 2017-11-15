#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <map>
#define NIL -1

using namespace std;

template <class T>
class No{
private:
  T item;
  No* prox;
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

//classe Grafo
template <class T>
class Lista{
private:
  No <T> *prim;
  No <T> *ult;
  int tamLista = 0;
public:
  Lista(){
    prim = new No <T>;
    prim->setProx(NULL);
    ult = prim;
  }

  No <T>* getPrim(){
    return prim;
  }

  No <T>* getUlt(){
    return ult;
  }

  void insere(int vertice);
  void mostra();
  void destroy();
  int getTamLista();
  int busca(int);
};

template <class T>
void Lista<T>::insere(int vertice){
  ult->setProx(new No<T>);
  ult = ult->getProx();
  ult->setProx(NULL);
  ult->setItem(vertice);
  tamLista++;
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
  p = p->getProx();
}

template <class T>
int Lista<T>::getTamLista(){
  return tamLista;
}

template <class T>
int Lista<T>::busca(int i){
    No<T> *p = getPrim()->getProx();
    int cont = 1;
    int achou;
    while(p != NULL){
      if(cont == i){
         achou = p->getItem();
      }
      cont++;
      p = p->getProx();
    }

    return achou;
}

//Classe Grafo
class Neuronio{
private:
  //Lista<int> *adj;
  Lista<int> *adj;
  int ordemNeuronio,tamanhoNeuronio;
  map<pair<int,int>,float> pesoNeuronio;
public:
  Neuronio();
  Neuronio(int,int);
  void inicializaNeuronio(int,int);
  void insereVerticeNeuronio(int,int,float);
  void imprimeNeuronio();
  void destroyNeuronio();
  Lista<int> *getAdjNeuronio();
  int getOrdemNeuronio();
  int getTamanhoNeuronio();
  int getPesoNeuronio(int,int);
};

Neuronio::Neuronio(){}

void Neuronio::inicializaNeuronio(int ordem,int tamanho){
 this->ordemNeuronio = ordem;
 this->tamanhoNeuronio = tamanho;
 adj = new Lista<int>[ordem+1];
}

void Neuronio::insereVerticeNeuronio(int u, int v,float peso){
 int vertice = {v};
 adj[u].insere(vertice);
 pesoNeuronio[{u,v}] = peso; //adiciona o peso da aresta de u para v

}

void Neuronio::imprimeNeuronio(){
 for(int i= 1; i<= ordemNeuronio; i++){
   cout <<"v[" << i << "] = ";
   adj[i].mostra();
 }
}

void Neuronio::destroyNeuronio(){
 for(int i = 0;i <= ordemNeuronio; i++){
   adj[i].destroy();
 }
 delete(adj);
 ordemNeuronio = tamanhoNeuronio = 0;
}

Lista<int> * Neuronio::getAdjNeuronio(){
 return adj;
}

int Neuronio::getOrdemNeuronio(){
 return ordemNeuronio;
}

int Neuronio::getTamanhoNeuronio(){
 return tamanhoNeuronio;
}

int Neuronio::getPesoNeuronio(int u,int v){
 return pesoNeuronio[{u,v}];
}

class Cerebro{
private:
  Lista<int> *vertices;
  int ordemCerebro,tamanhoCerebro;
  map<pair<int,int>,float> pesoCerebro;
  Neuronio *neuronio;
public:
  Cerebro(int,int);
  void inicializaCerebro(int,int);
  void insereVerticeCerebro(int,int,float);
  void imprimeCerebro();
  void destroyCerebro();
  Lista<int> *getAdjCerebro();
  int getOrdemCerebro();
  int getTamanhoCerebro();
  int getPesoCerebro(int,int);
  void inicializaCerebroNeuronio(int,int, int);
  void insereCerebroNeuronio(int,int,int,float);

};
Cerebro::Cerebro(int ordem,int tamanho){
 inicializaCerebro(ordem,tamanho);
}

void Cerebro::inicializaCerebro(int ordem,int tamanho){
 this->ordemCerebro = ordem;
 this->tamanhoCerebro = tamanho;
 vertices = new Lista<int>[ordem+1];
 neuronio = new Neuronio[ordem+1];
}

void Cerebro::insereVerticeCerebro(int u, int v,float peso){
 int vertice = {v};
 vertices[u].insere(vertice);
 pesoCerebro[{u,v}] = peso; //adiciona o peso da aresta de u para v
}

void Cerebro::imprimeCerebro(){
 for(int i= 1; i<= ordemCerebro; i++){
   cout <<"v[" << i << "] = ";
   vertices[i].mostra();
 }
}

void Cerebro::destroyCerebro(){
 for(int i = 0;i <= ordemCerebro; i++){
   vertices[i].destroy();
 }
 delete(vertices);
  ordemCerebro = tamanhoCerebro = 0;
}

Lista<int> * Cerebro::getAdjCerebro(){
 return vertices;
}

int Cerebro::getTamanhoCerebro(){
 return tamanhoCerebro;
}

int Cerebro::getOrdemCerebro(){
 return ordemCerebro;
}

int Cerebro::getPesoCerebro(int u,int v){
 return pesoCerebro[{u,v}];
}

void Cerebro::inicializaCerebroNeuronio(int indice,int ordem,int tamanho){
    neuronio[indice].inicializaNeuronio(ordem,tamanho);
}

void Cerebro::insereCerebroNeuronio(int indice,int u,int v,float peso){
    neuronio[indice].insereVerticeNeuronio(u,v,peso);
}

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}

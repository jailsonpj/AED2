#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <map>
#define NIL -1

typedef int Vertex;
enum Cores {BRANCO,CINZA,PRETO};
int TEMPO;
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

template<class T>
class Fila{
private:
	No<T> *frente, *tras;
public:
	Fila();
	void enfileira(T);
	T  desenfileira();
	void mostra();
	bool vazia();
};

template<class T>
Fila<T>::Fila(){
	frente = new No<T>();
  frente->setProx(NULL);
  tras = frente;
}

template<class T>
void Fila<T>::enfileira(T item){
	tras->setProx(new No<T>());
  tras = tras->getProx();
  tras->setItem(item);
  tras->setProx(NULL);
}

template<class T>
T Fila<T>::desenfileira(){
	No<T> *aux = frente;
  frente =  frente->getProx();
  T item = frente->getItem();
  delete aux;

  return item;
}

template<class T>
void Fila<T>::mostra(){
	No<T> *aux;
  aux = frente->getProx();
  if(aux == NULL){
    cout << "Fila Vazia";
  }else{
    while(aux != NULL){
      cout << aux->getItem() << " ";
      aux = aux->getProx();
    }
  }
  cout << endl;
}

template<class T>
bool Fila<T>::vazia(){
	No<T> *aux;
  aux = frente->getProx();
  if(aux == NULL){
    return false;
  }else{
    return true;
  }
}

template <class T>
class Vertice{
private:
  T vertice;
  T peso;
  Vertice *prox;
public:
  Vertice(){
    this->prox = NULL;
  }
  Vertice(T vertice){
    this->vertice = vertice;
    this->prox = NULL;
  }

  Vertice* getProx(){
    return prox;
  }

  void setProx(Vertice* prox){
    this->prox = prox;
  }

  T getVertice(){
    return vertice;
  }

  void setVertice(T vertice){
    this->vertice = vertice;
  }

};

template <class T>
class Lista{
private:
  Vertice <T> *prim;
  Vertice <T> *ult;
  int tamLista = 0;
public:
  Lista(){
    prim = new Vertice <T>;
    prim->setProx(NULL);
    ult = prim;
  }

  Vertice<T>* getPrim(){
    return prim;
  }

  Vertice<T>* getUlt(){
    return ult;
  }

  void insere(T vertice);
  void mostra();
  void destroy();
  int getTamLista();
  int busca(Vertex);
};

template <class T>
void Lista<T>::insere(T vertice){
  ult->setProx(new Vertice<T>);
  ult = ult->getProx();
  ult->setProx(NULL);
  ult->setItem(vertice);
  tamLista++;
}

template <class T>
void Lista<T>::mostra(){
  Vertice<T> *p = prim->getProx();
  while(p != NULL){
    cout << p->getVertice() << " ";
    //cout << p->getPeso() << " ";
    p = p->getProx();
  }
  cout << '\n';
}

template <class T>
void Lista<T>::destroy(){
  Vertice<T> * p = getPrim()->getProx();
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
int Lista<T>::busca(Vertex i){
    Vertice<T> *p = getPrim()->getProx();
    int cont = 1;
    Vertex achou;
    while(p != NULL){
      if(cont == i){
         achou = p->getVertice();
      }
      cont++;
      p = p->getProx();
    }

    return achou;
}


class Grafo{
  Lista<Vertex> *adj;
  int n,m;
  map<pair<int,int>,int> peso;
public:
  Grafo(int);
  void initialize(int);
  void insertEdge(Vertex,Vertex,Vertex);
  void print();
  void destroy();
  Lista<Vertex> *getAdj();
  int getN();
  int getM();
  int getPeso(int,int);
};

 Grafo::Grafo(int n){
  initialize(n);
}

void Grafo::initialize(int n){
  this->n = n;
  adj = new Lista<Vertex>[n+1];
}

void Grafo::insertEdge(Vertex u, Vertex v,Vertex p){
  Vertex x = {v};
  adj[u].insere(x);
  peso[{u,v}] = p; //adiciona o pesoda aresta de u para v
  m++;
}

void Grafo::print(){
  for(int i= 1; i<= n; i++){
    cout <<"v[" << i << "] = ";
    adj[i].mostra();
  }
}

void Grafo::destroy(){
  for(int i = 0;i <= n; i++){
    adj[i].destroy();
  }
  delete(adj);
  n = m = 0;
}

Lista<Vertex> * Grafo::getAdj(){
  return adj;
}

int Grafo::getN(){
  return n;
}

int Grafo::getM(){
  return m;
}

int Grafo::getPeso(int u,int v){
  return peso[{u,v}];
}

class DKJ{
private:
  int *d;
  int *pred;
  int *vertex;
  void dkj(Grafo &,int );
public:
  DKJ();
  void run(Grafo &,int);
  int getD(int);
  void InicializaDKJ(Grafo &,int);
  void relaxa(Vertice<Vertex> &u,Vertice<Vertex> &v);
};
DKJ::DKJ(){
}

void DKJ::run(Grafo &g,int s){
  dkj(g,s);
}

int getD::(int vertex){
  return d[vertex];
}

void DKJ::inicializaDKJ(Grafo &g,int s){ // Inicializa predecessor,distancia
  vertex = new int[g.getN()];
  pred = new int[g.getN()];
  d = new int[g.getN()];

  for(int i=0;i<g.getN();i++){
    vertex[i] = i;
    pred[i] = NIL;
    d[i] = 1111;
  }
  d[s] = 0;
}

/*int DKJ::somaDist(Grafo &g,int u,int v){
  return g.getPeso(u,v) + d[u];
}*/

void DKJ::relaxa(int u,int v,int w){
  if(d[v] > (d[u] + w)){
    d[v] = d[u] + w;
    pred[v] = u;
  }
}

void dkj(Grafo &g,int s){
  InicializaDKJ(g,s);

}

int main(int argc, char const *argv[]) {

  return 0;
}

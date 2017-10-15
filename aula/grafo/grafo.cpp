#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

typedef int Vertex;
enum Cores {BRANCO,CINZA,PRETO};
int TEMPO;


using namespace std;

//Classe Nó
template <class T>
class No{
private:
  T item; //vetor de itens
  No* prox; //ponteiro para o proximo item
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

//Classe Lista
template <class T>
class Lista{
private:
  No <T> *prim;
  No <T> *ult;
  int tamLista = 0;
  //No <T> *pred(No<T>*);
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
  int gettamLista();
  int busca(Vertex);
};

template <class T>
void Lista<T>::insere(T item){
  ult->setProx(new No<T>);
  ult = ult->getProx();
  ult->setProx(NULL);
  ult->setItem(item);
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
  p = p->prox;
}

template <class T>
int Lista<T>::gettamLista(){
  return tamLista;
}

template <class T>
int Lista<T>::busca(Vertex i){ //busca um elemento na lista de adjacencia em um determinado indice
    No<T> *p = getPrim()->getProx();
    int cont = 1;
    Vertex achou;
    while(p != NULL){
      if(cont == i){
         achou = p->getItem();
      }
      cont++;
      p = p->getProx();
    }

    return achou;
}

//Grafo
template <class T>
class Grafo{ //não direcionado
  Lista<Vertex> *adj;
  int n,m; //ordem e tamanho
  //void destroy();

public:
  Grafo(int); //construtor
  void initialize(int);
  void insertEdge(Vertex,Vertex);
  void print();
  void destroy();
  Lista<Vertex> *getAdj();
  int getN();
  int getM();
};

template <class T>
 Grafo<T>::Grafo(int n){
  initialize(n);
}

template <class T>
void Grafo<T>::initialize(int n){
  this->n = n;
  adj = new Lista<Vertex>[n+1];
}

template <class T>
void Grafo<T>::insertEdge(Vertex u, Vertex v){
  T x = {v}; //chave = vértice
  adj[u].insere(x); //Insere na Lista
  x = {u};
  adj[v].insere(x); //Insere na Lista
  m++;
}

template <class T>
void Grafo<T>::print(){
  for(int i= 1; i<= n; i++){
    cout <<"v[" << i << "] = ";
    adj[i].mostra(); // Imprime elemento da lista
  }
}

template <class T>
void Grafo<T>::destroy(){
  for(int i = 0;i <= n; i++){
    adj[i].destroy(); // Destroi Lista
  }
  delete(adj);
  n = m = 0;
}

template <class T>
Lista<Vertex> * Grafo<T>::getAdj(){
  return adj;
}

template <class T>
int Grafo<T>:: getN(){
  return n;
}

template <class T>
int Grafo<T>::getM(){
  return m;
}


// CLasse da Busca em Profundidade
class DFS {
private:
  int *pred;
  Cores *cor;
  int *d;
  int *f;
  void dfs(Grafo<int> &);
  void dfsVisita(Grafo<int> &,Vertex);
public:
  DFS();
  void run(Grafo<int> &);
  int *getPred();
  Cores *getCor();
  int *getF();
  int *getD();
};

DFS::DFS(){ }
void DFS::run(Grafo<int> &g){
  dfs(g);
}

int * DFS::getPred(){
  return pred;
}

Cores * DFS::getCor(){
  return cor;
}

int *DFS::getF(){
  return f;
}

int *DFS::getD(){
  return d;
}

void DFS::dfsVisita(Grafo<int> &g, Vertex u){
  TEMPO = TEMPO +1;
  d[u] = TEMPO;
  cor[u] = CINZA;
  Lista<Vertex> adj = g.getAdj()[u];
  int i = 1;
  while(i <= adj.gettamLista()){
        Vertex v = adj.busca(i);
        if(cor[v] == BRANCO){
          pred[v] = u;
          dfsVisita(g,v);
        }
        i++;
    }
  cor[u] = PRETO;
  TEMPO = TEMPO + 1;
  f[u] = TEMPO;
}

void DFS::dfs(Grafo<int> &g){
    const int N = g.getN();
    pred = new int[N];
    cor = new Cores[N];
    d = new int[N];
    f = new int[N];

    for(Vertex u=1;u<=N;u++){
      cor[u] = BRANCO;
      pred[u] = -1;
    }
    TEMPO = 0;
    for(Vertex u=1;u<=N;u++){
      if(cor[u] == BRANCO){
         dfsVisita(g,u);
      }
    }
}

void testeGrafo(Grafo<int> &g){
  g.insertEdge(1,2);
  cout << "---1-----" << endl;
  g.insertEdge(2,3);
  cout << "---2-----" << endl;
  g.insertEdge(3,4);
  cout << "---3-----" << endl;
  g.insertEdge(4,5);
  cout << "---4-----" << endl;
  g.insertEdge(5,1);
  cout << "---5-----" << endl;
  g.insertEdge(5,2);
  cout << "---6-----" << endl;
  g.insertEdge(2,4);
  cout << "---7-----" << endl;
  g.print();
  cout << "fim" << endl;
}

int main (int argc, const char * argv[]){
  int n,m;

  cout << "ordem: "; cin >> n;
  Grafo<int> g(n);
  cout << "-----grafo-----" << endl;
  testeGrafo(g);
  /*Vertex cont = g.getAdj()[1].busca(2);

  cout << cont << '\n';*/

  DFS dfs;
  dfs.run(g);
  //int *pred = dfs.getPred();

  for(int i=1;i<=g.getN();i++){
    cout << dfs.getPred()[i] << '\n';
  }

  for(int i=0;i<=g.getN();i++){
    cout <<"Tempo inicial: "<< dfs.getD()[i] <<"Tempo final: " << dfs.getF()[i]<<'\n';
  }

  return 0;
}

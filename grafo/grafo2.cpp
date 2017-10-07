#include <iostream>
#include <cstdlib>
#include <vector>
#define NIL -1

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

// Classe de Fila
template<class T>
class Fila{
private:
	Vertex *vertices;
	int frente, tras;
	int TAM;
public:
	Fila(int tam);
	void enfileira(Vertex);
	Vertex desenfileira();
	void mostra();
	bool vazia();
};

template<class T>
Fila<T>::Fila(int tam){
	TAM = tam;
	vertices = new Vertex[TAM];
	frente = 0;
	tras = frente;
}

template<class T>
void Fila<T>::enfileira(Vertex item){
	if((tras + 1) % TAM == frente){
		cout << "Fila Cheia!!" << endl;
	}
	else
	{
		vertices[tras] = item;
		tras = (tras+1) % TAM;
	}
}

template<class T>
Vertex Fila<T>::desenfileira(){
	if(frente == tras){
		cout << "Fila vazia!!" << endl;
		return NIL;
	}
	else
	{
		Vertex item;
		item = vertices[frente];
		frente = (frente + 1) % TAM;
		return item;
	}
}

template<class T>
void Fila<T>::mostra(){
	for(int i = frente; i < tras; i++){
		cout << vertices[i] << '\n';
	}
	cout << endl;
}

template<class T>
bool Fila<T>::vazia(){
	if(frente == tras){
		return true;
	}
	else{
		return false;
	}
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

// Busca em Largura
class BFS {
private:
  int *pred;
  Cores *cor;
  int d;
  void bfs(Grafo<int> &, int );
public:
  BFS();
  void run(Grafo<int> &,int);
  int *getPred();
  Cores *getCor();
  int getD();
};

BFS::BFS(){ }
void BFS::run(Grafo<int> &g,int s){
  bfs(g,s);
}

int * BFS::getPred(){
  return pred;
}

Cores * BFS::getCor(){
  return cor;
}

void BFS::bfs(Grafo<int> &g,int ini){
  const int N = g.getN();
  pred = new int[N];
  cor = new Cores[N];
  Vertex r;

  for(Vertex u=1;u<=N;u++){ //inicia todos os vértices com Branco
    cor[u] = BRANCO;
    pred[u] = -1;
    d = 1111;
  }
  cor[ini] = CINZA;
  d = 0;
  pred[ini] = NIL;

  Fila<int> fila(g.getM()*2);
  No<int> *s = g.getAdj()[ini].getPrim()->getProx();
  while(s != NULL){ //adiciona os itens do vértice da lista de adj na fila
    fila.enfileira(s->getItem());
    cor[s->getItem()] = CINZA;
    pred[s->getItem()] = ini;
    s = s->getProx();
  }

  while (!fila.vazia()) {
    r = fila.desenfileira();//desenfileira o valor do vertice
    No<int> *q = g.getAdj()[r].getPrim()->getProx();
    while(q != NULL){
      Vertex v = q->getItem();
        if (cor[v] == BRANCO) {
          cor[v] = CINZA;
          d++;
          pred[v] = r;
          No<int> *aux = g.getAdj()[v].getPrim()->getProx();
          while(aux != NULL){
            fila.enfileira(aux->getItem());
            aux = aux->getProx();
          }
        }
        q = q->getProx();
      }
      cor[r] = PRETO;
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

  BFS bfs;
  bfs.run(g,1);

  for(int i=1;i<=g.getN();i++){
    cout << bfs.getPred()[i] << '\n';
  }

  return 0;
}

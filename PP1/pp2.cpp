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

//classe fila
template<class T>
class Fila{
private:
	No<T> *frente, *tras;
	//int TAM;
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
  p = p->getProx();
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

 Grafo::Grafo(int n){
  initialize(n);
}

void Grafo::initialize(int n){
  this->n = n;
  adj = new Lista<Vertex>[n+1];
}

void Grafo::insertEdge(Vertex u, Vertex v){
  Vertex x = {v}; //chave = vértice
  adj[u].insere(x); //Insere na Lista
  x = {u};
  adj[v].insere(x); //Insere na Lista
  m++;
}

void Grafo::print(){
  for(int i= 1; i<= n; i++){
    cout <<"v[" << i << "] = ";
    adj[i].mostra(); // Imprime elemento da lista
  }
}

void Grafo::destroy(){
  for(int i = 0;i <= n; i++){
    adj[i].destroy(); // Destroi Lista
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

/*Classe Busca em Largura*/
class BFS{
private:
  int *pred;
  Cores *cor;
  int *d;
  int *vertex;
  int achado;
  vector<int> caminho;
  void bfs(Grafo &, int , int );
public:
  BFS();
  void run(Grafo &,int,int);
  int *getPred();
  Cores *getCor();
  int getD(int);
  void mostraBFS();
  void menorCaminho();
  int getAchado();
  vector<int> getCaminho();
};
BFS::BFS(){ }
void BFS::run(Grafo &g,int s,int c){
  bfs(g,s,c);
}

int * BFS::getPred(){
  return pred;
}

Cores * BFS::getCor(){
  return cor;
}

int BFS::getAchado(){
  return achado;
}

int BFS::getD(int vertex){
  return d[vertex];
}

void BFS::bfs(Grafo &g,int s,int c){
  const int N = g.getN();
  vertex = new int[N];
  pred = new int[N];
  cor = new Cores[N];
  d = new int[N];
  Vertex r;

  for(int i = 0;i<=N;i++){
    vertex[i] = i;
    cor[i] = BRANCO;
    d[i] = 1111;
    pred[i] = NIL;
  }
  cor[s] = CINZA;
  d[s] = 0;
  pred[s] = NIL;

  Fila<Vertex> fila;
  fila.enfileira(s);

  while (fila.vazia() ) {
    int u,v;
    u = fila.desenfileira();
    No<Vertex> *p = g.getAdj()[u].getPrim()->getProx();
    while( p != NULL){
      v = p->getItem();
        if(cor[v] == BRANCO){
          cor[v] = CINZA;
          d[v] = d[u] + 1;
          if(v == c){
            achado = u;
          }
          pred[v] = u;
          fila.enfileira(v);
        }
        p = p->getProx();
    }
    cor[u] = PRETO;
  }
}

void BFS::mostraBFS(){
cout << "Vertex - Predecessor - Distancia " << endl;
  for( int i = 1; i <= 64; i ++) {
      cout << vertex[i] << " [] " << pred[i] <<" [] " << d[i] << endl;
  }

}

void BFS::menorCaminho(){
  int i = achado;
  caminho.push_back(i);
  while (pred[i] != -1) {
      int u = pred[i];
      caminho.push_back(u);
      i = u;
  }

  for(int j=0;j<caminho.size();j++){
    cout << caminho[j] << '\t';
  }
  cout << '\n';
}

vector<int> BFS::getCaminho(){
  return caminho;
}

/*classe responsavel pela criação das matrizes de movimentos e a BFS de cada cavalo*/
class Matriz{
private:
  vector<vector<int> > mat;
  pair<int,int> grafo_tabuleiro[64];
  map<pair<int,int>,int> tabuleiro_grafo;
  vector<int> ext; //vetor do caminho
  int menor;
  BFS bfs;
  //Ordena ord;
public:
  Matriz();
  void inicializa();
  void mapeaRei(int l,int c,int lr,int cr);
  void preenche();
  void mostraMatriz();
  int getMenor();
  void saidaMatriz();
  pair<int,int> getGrafoTabuleiro(int );
  vector<int> getExt();
  int particao(vector<int> &v, int p, int r);
  void quicksort(vector<int> &v, int p, int r);
};
Matriz::Matriz(){}
void Matriz::inicializa(){
  for(int i=0;i<=8;i++){
    vector<int> v(9);
    mat.push_back(v);
  }


  int k = 1;
  for(int i=1;i<=8;i++){
    for(int j=1;j<=8;j++){
      grafo_tabuleiro[k] = {j,i};
      tabuleiro_grafo[{j,i}] = k;
      k++;
    }
  }

}

void Matriz::preenche(){
  for(int i=1;i<=8;i++){
    for(int j=1;j<=8;j++){
      mat[i][j] = 0;
    }
  }
}

void Matriz::mostraMatriz(){
  for(int i=8;i>=1;i--){
    cout <<"V = "<< i<< '\t';
    for(int j=1;j<=8;j++){
      cout << mat[i][j];
    }
    cout <<endl;
  }
  cout << endl;
}

int Matriz::getMenor(){
  return menor;
}

int Matriz::particao(vector<int> &v, int p, int r){
	int x = v[p], tmp = v[r+1];
	v[r+1] = x;

	int i = p, j = r+1;

	while(true){
		do{
			i = i+1;
		}while(v[i] < x);

		do{
			j = j-1;
		}while(v[j] > x);

		if(i < j){
			swap(v[i], v[j]);
		}
		else{
			swap(v[p],v[j]);
			v[r+1] = tmp;
			return j;
		}
	}
}

void Matriz::quicksort(vector<int> &v, int p, int r){
	int q;
	if(p < r){
		q = particao(v, p, r);
		quicksort(v, p, q-1);
		quicksort(v, q+1, r);
	}
}

void Matriz::mapeaRei(int l,int c,int lr,int cr){
  vector<int> di = {-1,+1,-2,+2,-2,-2,+2,-1,+1};
  vector<int> dj = {-2,-2,-1,-1,-1,+1,+1,+2,+2};
  int l1,c1;
  int cont = 0;
  mat[l][c] = 3;
  Fila<pair<int,int> > fila;
  pair<int,int> cord1;
  cord1 = make_pair(l,c);
  fila.enfileira(cord1);

  Grafo g(64);
  while(fila.vazia()){
    pair<int,int> cord2;
    cord2 = fila.desenfileira();
      vector<int> ent; //vector para as entradas
      for(int i=0;i<=8;i++){
        //vector<int> ent; //vector para as entradas
        l1 = cord2.first + di[i];
        c1 = cord2.second +dj[i];
        pair<int,int> cord;
        if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
          if(mat[l1][c1] != 3){
            mat[l1][c1] = 3;
            fila.enfileira({l1,c1});
            int indice_vertice = tabuleiro_grafo[{l1,c1}];
            ent.push_back(indice_vertice);
            //g.insertEdge(tabuleiro_grafo[cord2],indice_vertice);
          }
        }
      }
      //Aqui
      //Ordena ord;
      quicksort(ent,0,ent.size()-1);
      //g.insertEdge(tabuleiro_grafo[cord2],ent[i]);
      for(int j=0;j<ent.size();j++){
        g.insertEdge(tabuleiro_grafo[cord2],ent[j]);
      }

    }

    g.print();
    int inicio = tabuleiro_grafo[{l,c}];
    //cout << inicio << endl;
    bfs.run(g,inicio,tabuleiro_grafo[{lr,cr}]);
    //bfs.mostraBFS(); Tá pegando
    //bfs.menorCaminho(); Tá pegando
    menor = bfs.getD(bfs.getAchado());
    cout << menor << endl;
    //ext = bfs.getCaminho();
}

pair<int,int> Matriz::getGrafoTabuleiro(int i){
  return grafo_tabuleiro[i];
}

vector<int> Matriz::getExt(){
  return ext;
}

int main(int argc, char const *argv[]) {
  /*Grafo g(5);
  cout << "-----grafo-----" << endl;
  testeGrafo(g);
  BFS bfs;
  bfs.run(g,2,5);
  bfs.mostraBFS();*/

  Matriz mat;
  mat.inicializa();
  mat.preenche();
  mat.mapeaRei(1,8,4,5);
  mat.mostraMatriz();


  return 0;
}

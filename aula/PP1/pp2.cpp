#include <iostream>
#include <cstdlib>
#include <vector>
#define NIL -1

typedef int Vertex;
enum Cores {BRANCO,CINZA,PRETO};
//enum Pos {a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8};
int TEMPO;
using namespace std;


//classe Nó
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

  void setProx(No<T>* prox){
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
	int desenfileira();
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
int Fila<T>::desenfileira(){
	No<T> *aux = frente;
  frente =  frente->getProx();
  int item = frente->getItem();
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

//Classe lista
template <class T>
class List{
private:
  vector<T> lista;
public:
  List(){
  }
  ~List(){
    destroy();
  }
  void insere(T item);
//  void remove(T item);
  int busca(T item);
  void mostra();
  void destroy();
  T getItem(int pos);
  int getTam();


};

template <class T>
void List<T>::insere(T item){
  lista.push_back(item);
}

template <class T>
int List<T>::busca(T item){
  int aux = -1;
  for(int i=0;i<lista.size();i++){
    if( item == lista[i]){
      aux = i;
      i = lista.size();
    }
  }
  return aux ;
}

template <class T>
void List<T> :: mostra() {
  for(int i =0;i<lista.size();i++){
    cout << lista[i] << " ";
  }
  cout << endl;
}

template <class T>
void List<T> :: destroy(){
  lista.clear();
  lista.shrink_to_fit();
}

template <class T>
int List<T>::getTam(){
  return lista.size();
}

template <class T>
T List<T>::getItem(int pos){
  return lista[pos];
}




//Grafo
class Grafo{ //não direcionado
  List<Vertex> *adj;
  int n,m; //ordem e tamanho

  void initialize(int n){
    /*if(this->n != 0){
      destroy();
    }*/
    this->n = n;
    this->m = 0;
    adj = new List<Vertex>[n+1];
  }
  void destroy(){
    for(int i=0;i<= this->n;i++){
      adj[i].destroy();
    }
    delete[] adj;
    n = m = 0;
  }
public:
  Grafo(int); //construtor
  void insertEdge(Vertex,Vertex);
  void print();
  int getN();
  int getM();
  List<Vertex> getAdj(int);


};

 Grafo::Grafo(int n){
  initialize(n);
}

void Grafo::insertEdge(Vertex u, Vertex v){
  adj[u].insere(v);
//  adj[v].insere(u);
  m++;
}

void Grafo::print(){
  for(int i=this->n;i>=1;i--){
    cout << "v[" << i <<"] = ";
    adj[i].mostra();
  }
  cout << endl;
}

int Grafo:: getN(){
  return n;
}

int Grafo::getM(){
  return m;
}

List<Vertex> Grafo::getAdj(int pos){
  return adj[pos];
}

class BFS{
private:
  int *pred;
  Cores *cor;
  int *d;
  void bfs(Grafo &, int  );
public:
  BFS();
  void run(Grafo &,int);
  int *getPred();
  Cores *getCor();
  int getD();
};
BFS::BFS(){ }
void BFS::run(Grafo &g,int s){
  bfs(g,s);
}

int * BFS::getPred(){
  return pred;
}

Cores * BFS::getCor(){
  return cor;
}

void BFS::bfs(Grafo &g,int s){
  const int N = g.getN();
  pred = new int[N];
  cor = new Cores[N];
  d = new int[N];
  Vertex r;

  for(int i = 0;i<=N;i++){
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
    for(int i=0;i<=g.getAdj(u).getTam();i++){
      v = g.getAdj(u).getItem(i);
        if(cor[v] == BRANCO){
          cor[v] = CINZA;
          d[v] = d[u] + 1;
          pred[v] = u;
          fila.enfileira(v);
        }
    }
    cor[u] = PRETO;
  }

}


class Matriz{
private:
  vector<vector<int> > mat;
public:
  Matriz();
  void inicializa();
  void adicionaCavalo(int l,int c);
  void adicionaRei(int l,int c);
  void mapeaRei(int l,int c);
  void mapeaCavalo(int l,int c);
  void preenche();
  void mostraMatriz();
};
Matriz::Matriz(){}
void Matriz::inicializa(){
  for(int i=0;i<=8;i++){
    vector<int> v(9);
    mat.push_back(v);
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
      cout << mat[i][j] << '\t';
    }
    cout <<endl;
  }
  cout << endl;
}

void Matriz::adicionaCavalo(int l,int c){
  mat[l][c] = 1;
}

void Matriz::adicionaRei(int l,int c){
  mat[l][c] = 2;
}

void Matriz::mapeaRei(int l,int c){
  vector<int> di = {-1,+1,-2,+2,-2,-2,+2,-1,+1};
  vector<int> dj = {-2,-2,-1,-1,-1,+1,+1,+2,+2};

  int l1,c1;
  int cont = 0;
  int aux = 3;
  int ver = 1;

  for(int i=0;i<8;i++){
    l1 = l+ di[i];
    c1 = c+dj[i];
    if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
      cont++;
    }
  }

//  Grafo g(cont);
  for(int i=0;i<=8;i++){
    l1 = l+ di[i];
    c1 = c+dj[i];
    if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
      mat[l1][c1] = aux;
    //  g.insertEdge(1,ver++);
      aux++;
    }
  }

  //g.print();
}


void mapeaRei(Grafo &g,int l,int c){
  vector<int> di = {-1,+1,-2,+2,-2,-2,+2,-1,+1};
  vector<int> dj = {-2,-2,-1,-1,-1,+1,+1,+2,+2};

  int l1,c1;
  int cont = 0;
  int aux = 3;
  int ver = 1;

  for(int i=0;i<8;i++){
    l1 = l+ di[i];
    c1 = c+dj[i];
    if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
      cont++;
    }
  }

//  Grafo g(cont);
  for(int i=0;i<=8;i++){
    l1 = l+ di[i];
    c1 = c+dj[i];
    if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
      g.insertEdge(2,aux++);
    }
  }

  //g.print();
}

int main(int argc, char const *argv[]) {

  Matriz mat;
  mat.inicializa();
  mat.preenche();
  mat.mostraMatriz();
  cout << "****************" << endl;

  mat.adicionaRei(4,5);
  mat.adicionaCavalo(1,1);
  mat.adicionaCavalo(7,3);
  mat.adicionaCavalo(8,5);
  mat.adicionaCavalo(1,8);
  //mat.mostraMatriz();
  mat.mapeaRei(4,5);
  mat.mostraMatriz();

  Grafo g(9);
  mapeaRei(g,4,5);
  g.print();


  return 0;
}

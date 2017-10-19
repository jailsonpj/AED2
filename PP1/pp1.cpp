#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
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
  for(int i=this->n;i>=0;i--){
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
  void mostraMenorCaminho();
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

    for(int i=0;i<g.getAdj(u).getTam();i++){
      v = g.getAdj(u).getItem(i);
        if(cor[v] == BRANCO){
          cor[v] = CINZA;
          d[v] = d[u] + 1;
          if(v == c){
            //return d[v];
            //cout << d[v] << endl;
            achado = u;
          }
          pred[v] = u;
          fila.enfileira(v);
        }
    }
    cor[u] = PRETO;
  }

}

void BFS::mostraBFS(){
cout << "Vertex - Predecessor - Distancia " << endl;
  for( int i = 0; i <= 64; i ++) {
      cout << vertex[i] << " [] " << pred[i] <<" [] " << d[i] << endl;

  }

}

void BFS::menorCaminho(){

  int i = achado;
  //cout << d[i] <<'\t';
  caminho.push_back(i);
  while (pred[i] != -1) {
      int u = pred[i];
      caminho.push_back(u);
      //cout << u <<'\t';
      i = u;
  }
/*  for(int i=0;i<caminho.size();i++){
    cout << caminho[i] << endl;
  }*/
}

void BFS::mostraMenorCaminho(){
  cout << d[achado] <<'\t';
  for(int i=0;i<caminho.size();i++){
      cout << caminho[i] <<'\t';
    }
    cout << endl;
}

class Matriz{
private:
  vector<vector<int> > mat;
  pair<int,int> grafo_tabuleiro[64];
  map<pair<int,int>,int> tabuleiro_grafo;
  int menor;
  BFS bfs;
public:
  Matriz();
  void inicializa();
  void adicionaCavalo(int l,int c);
  void adicionaRei(int l,int c);
  void mapeaRei(int l,int c,int lr,int cr);
  void mapeaCavalo(int l,int c);
  void preenche();
  void mostraMatriz();
  int getMenor();
  void saida() ;
};
Matriz::Matriz(){}
void Matriz::inicializa(){
  for(int i=0;i<=8;i++){
    vector<int> v(9);
    mat.push_back(v);
  }


  int k = 0;
  for(int i=1;i<=8;i++){
    for(int j=1;j<=8;j++){
      grafo_tabuleiro[k] = {i,j};
      tabuleiro_grafo[{i,j}] = k;
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

void Matriz::adicionaCavalo(int l,int c){
  mat[l][c] = 1;
}

void Matriz::adicionaRei(int l,int c){
  mat[l][c] = 2;
}

int Matriz::getMenor(){
  return menor;
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
      for(int i=0;i<=8;i++){
        l1 = cord2.first + di[i];
        c1 = cord2.second +dj[i];
        pair<int,int> cord;
        if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
          if(mat[l1][c1] != 3){
            mat[l1][c1] = 3;
            fila.enfileira({l1,c1});
            int indice_vertice = tabuleiro_grafo[{l1,c1}];

            g.insertEdge(tabuleiro_grafo[cord2],indice_vertice);
          }
        }
      }
  }
    //g.print();
    //BFS bfs;
    int inicio = tabuleiro_grafo[{l,c}];
    bfs.run(g,inicio,tabuleiro_grafo[{lr,cr}]);
    //bfs.mostraBFS();
    bfs.menorCaminho();

    menor = bfs.getD(bfs.getAchado());

    //cout << menor <<endl;
  //  bfs.mostraMenorCaminho();
}

void Matriz::saida() {
  bfs.mostraMenorCaminho();
}





int main(int argc, char const *argv[]) {

vector<pair<int,int> > minimo;
vector<int> menor;
vector<pair<int,int> > cord {{0,0},{1,8},{7,3},{8,5}};
Matriz mat[4];


for(int i=0;i<4;i++){
  mat[i].inicializa();
  mat[i].preenche();
  mat[i].mapeaRei(cord[i].first,cord[i].second,4,5);
  minimo.push_back({mat[i].getMenor(),i});
}

int aux = minimo[0].first;
int i = 1;
int it;
int j = 0;
while( i <= minimo.size()){
  if(minimo[i].first < aux ){
      aux = minimo[i].first;
      it = i;
  }
  i++;
}

menor.push_back(minimo[it].second);
while(j < minimo.size()){
  if(j != it){
    if(aux == minimo[j].first){
      menor.push_back(minimo[j].second);
    }
  }
  j++;
}

for(int i =0;i<menor.size();i++){
   mat[menor[i]].saida();
}

  return 0;
}

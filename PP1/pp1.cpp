#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#define NIL -1

typedef int Vertex;
enum Cores {BRANCO,CINZA,PRETO};
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
  vector<T> getLista();
  int particao(vector<T> &v, int p, int r);
  void quicksort(vector<T> &v, int p, int r);
	void ordenaListas();
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

template <class T>
vector<T> List<T>::getLista(){
  return lista;
}

template <class T>
int List<T>::particao(vector<T> &v, int p, int r){
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

template <class T>
void List<T>::quicksort(vector<T> &v, int p, int r){
	int q;
	if(p < r){
		q = particao(v, p, r);
		quicksort(v, p, q-1);
		quicksort(v, q+1, r);
	}
}


template <class T>
void List<T>::ordenaListas(){
    quicksort(lista,0,lista.size()-1);
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
  void ordena();
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

void Grafo::ordena(){
  for(int i=0;i<this->n;i++){
    adj[i].ordenaListas();
  }
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
    for(int i=0;i<g.getAdj(u).getTam();i++){
      v = g.getAdj(u).getItem(i);
        if(cor[v] == BRANCO){
          cor[v] = CINZA;
          d[v] = d[u] + 1;
          if(v == c){
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
  caminho.push_back(i);
  while (pred[i] != -1) {
      int u = pred[i];
      caminho.push_back(u);
      i = u;
  }
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
    g.ordena();
    int inicio = tabuleiro_grafo[{l,c}];
    bfs.run(g,inicio,tabuleiro_grafo[{lr,cr}]);
    bfs.menorCaminho();
    menor = bfs.getD(bfs.getAchado());
    ext = bfs.getCaminho();
}

pair<int,int> Matriz::getGrafoTabuleiro(int i){
  return grafo_tabuleiro[i];
}

vector<int> Matriz::getExt(){
  return ext;
}

/*Classe responsavel pelo Processamento da entrada e saida do projeto*/
class Processamento{
private:
	vector<int> numeros {NIL, 49, 50, 51, 52, 53, 54, 55, 56}; //1,2,3...
	vector<int> letras {NIL, 97, 98, 99, 100, 101, 102, 103, 104};//a,b,c,d...
	vector<pair<int, int> > coordenadas;
	vector<string> entrada; // vector com as posicoes dos cavalos e rei
  vector<pair<int,int> > minimo;
  vector<int> menor;
  Matriz mat[4];
	string jogada; //posicao de cada cavalo e do rei

public:
	Processamento();
	void recebeEntrada();
	void convertePosicao();
	pair<string,int> invertePosicao(pair<int,int> );
  void inicializaMatriz();
  pair<int,int> getRei();
  void finaliza();
  void finalizaMostra();
};

Processamento::Processamento(){
}

void Processamento::recebeEntrada(){
	for(int i = 0; i < 5; ++i){
		cin >> jogada;
		cin.ignore();
		entrada.push_back(jogada);
	}
	convertePosicao();
}

void Processamento::convertePosicao(){
	pair<int, int> par;
	for (int i = 0; i < 5; ++i){
		par = make_pair(entrada[i][1],entrada[i][0]);
		coordenadas.push_back(par);
	}

	for (int i = 0; i < coordenadas.size(); ++i){
		for (int j = 1; j <= numeros.size(); ++j){
			if(coordenadas[i].first == numeros[j]){
				coordenadas[i].first=j;
			}
		}
	}

	for (int i = 0; i < coordenadas.size(); ++i){
		for (int j = 1; j <= letras.size(); ++j){
			if(coordenadas[i].second == letras[j]){
				coordenadas[i].second=j;
			}
		}
	}

}

pair<string,int> Processamento::invertePosicao(pair<int,int> p){
	pair<string, int> par;
		for (int j = 1; j <= letras.size(); ++j){
			if(p.second == j){
				par = make_pair(letras[j],p.first);
				//saida.push_back(par);
        return par;
			}
		}

}

pair<int,int> Processamento::getRei(){
  return coordenadas[4];
}

void Processamento::inicializaMatriz(){
  pair<int,int> rei = getRei();
  for(int i=0;i<4;i++){
    mat[i].inicializa();
    mat[i].preenche();
    mat[i].mapeaRei(coordenadas[i].first,coordenadas[i].second,rei.first,rei.second);
    minimo.push_back({mat[i].getMenor(),i});
  }
}

void Processamento::finaliza(){

  int aux = minimo[0].first;
  int it;
  for(int i=1;i<=minimo.size()-1;i++ ){
    if(minimo[i].first < aux ){
        aux = minimo[i].first;
        it = i;
    }
  }
  menor.push_back(minimo[it].second);
  for(int j=0;j<minimo.size();j++){
    if(j != it){
      if(aux == minimo[j].first){
        menor.push_back(minimo[j].second);
      }
    }
  }
}

void Processamento::finalizaMostra(){
  for(int i =0;i<menor.size();i++){
     cout << mat[menor[i]].getMenor() << '\t';
     for(int j=mat[menor[i]].getExt().size()-1; j>=0 ; j--){
      pair<int,int> p = mat[menor[i]].getGrafoTabuleiro(mat[menor[i]].getExt()[j]);
      pair<string,int> q = invertePosicao(p);
      cout << q.first << q.second << '\t';
     }
     cout << endl;
  }
}

/* corpo principal */
int main(int argc, char const *argv[]) {

  Processamento xadrez;
  xadrez.recebeEntrada();
  xadrez.inicializaMatriz();
  xadrez.finaliza();
  xadrez.finalizaMostra();

  return 0;
}

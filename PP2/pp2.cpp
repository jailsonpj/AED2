#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <map>
#include <iomanip>
#define NIL -1
#define INFINITO 1111;

enum Cores {BRANCO,CINZA,PRETO};
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

//classe Ordenação
class Ordenacao{
public:
  Ordenacao();
  int particao(vector<pair<pair<int,int>,float>> &v, int p, int r);
  void quicksort(vector<pair<pair<int,int>,float>> &v, int p, int r);
};
Ordenacao::Ordenacao(){}
int Ordenacao::particao(vector<pair<pair<int,int>,float>> &v, int p, int r){
	pair<pair<int,int>,float> x = v[p], tmp = v[r+1];
	v[r+1] = x;

	int i = p, j = r+1;

	while(true){
		do{
			i = i+1;
		}while(v[i].second < x.second);

		do{
			j = j-1;
		}while(v[j].second > x.second);

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

void Ordenacao::quicksort(vector<pair<pair<int,int>,float>> &v, int p, int r){
	int q;
	if(p < r){
		q = particao(v, p, r);
		quicksort(v, p, q-1);
		quicksort(v, q+1, r);
	}
}

//Classe Grafo
class Neuronio{
private:
  float **adjNeuronio;
  int ordemNeuronio,tamanhoNeuronio;
  vector <pair< pair<int,int>,float > > verticesPesoNeuronio;
  Cores *cor;
public:
  Neuronio();
  Neuronio(int,int);
  void inicializaNeuronio(int,int);
  void insereVerticeNeuronio(int,int,float);
  void imprimeNeuronio();
  int getOrdemNeuronio();
  int getTamanhoNeuronio();
  float getPesoNeuronio(int,int);
  vector<pair< pair<int,int>,float>> getverticesPesoNeuronio();
  void ordena();
  void mostraVerticePeso();
};

Neuronio::Neuronio(){}

void Neuronio::inicializaNeuronio(int ordem,int tamanho){
 this->ordemNeuronio = ordem;
 this->tamanhoNeuronio = tamanho;

 adjNeuronio = new float*[ordem+1]; //cria matriz
 for(int i=1;i<=ordem;i++){
   adjNeuronio[i] = new float[ordem+1];
 }

 for(int i=1;i<=ordem;i++){ // inicializa matriz com 0
   for(int j=1;j<=ordem;j++){
     adjNeuronio[i][j] = 0;
   }
 }
}

void Neuronio::insereVerticeNeuronio(int u, int v,float peso){
 adjNeuronio[u][v] = peso;
 adjNeuronio[v][u] = peso;

 verticesPesoNeuronio.push_back({{u,v},peso});
}

void Neuronio::imprimeNeuronio(){
  int k = 5;
    cout << "   ";
    for (int j = 1; j <= this->ordemNeuronio; j++){
        cout << setw(k) << j;
    }
    cout << endl;
    for (int j = 1; j <= (this->ordemNeuronio*k+3); j++){
        cout << "-";
    }
    cout << endl;
    for (int i = 1; i <= this->ordemNeuronio; i++){
        cout << setw(1) << i;
        cout << " |";
        for (int j = 1; j <= this->ordemNeuronio; j++){
            cout << setw(k) << adjNeuronio[i][j];
        }
        cout << endl;
    }
}

int Neuronio::getOrdemNeuronio(){
 return ordemNeuronio;
}

int Neuronio::getTamanhoNeuronio(){
 return tamanhoNeuronio;
}

float Neuronio::getPesoNeuronio(int vertice1,int vertice2){
  return adjNeuronio[vertice1][vertice2];
}

vector<pair< pair<int,int>,float >> Neuronio::getverticesPesoNeuronio(){
  return verticesPesoNeuronio;
}

void Neuronio::ordena(){
  Ordenacao orde;
  orde.quicksort(verticesPesoNeuronio,0,(int) verticesPesoNeuronio.size()-1);
}


void Neuronio::mostraVerticePeso(){
  for(int i=0;i<verticesPesoNeuronio.size();i++){
    cout << verticesPesoNeuronio[i].first.first << " " << verticesPesoNeuronio[i].first.second << " " << verticesPesoNeuronio[i].second << endl;
  }
}

class Uniao{
private:
  int *paiVertice;
public:
  Uniao();
  void iniciaUniao(int);
  int encontraPai(int);
  void uniaoVertices(int,int);
  int *getPaiVertice();
};

Uniao::Uniao(){ //construtor

}

void Uniao::iniciaUniao(int ordem){
  paiVertice = new int[ordem+1];
  for(int i=1;i<=ordem;i++){
    paiVertice[i] = -1;
  }
}

int Uniao::encontraPai(int vertice){
  if(paiVertice[vertice] == -1){
    return vertice;
  }
  return encontraPai(paiVertice[vertice]);
}

void Uniao::uniaoVertices(int vertice1,int vertice2){ //faz a uniao entre dois conjuntos
  vertice1 = encontraPai(vertice1);
  vertice2 = encontraPai(vertice2);

  paiVertice[vertice1] =  vertice2;
}

int * Uniao::getPaiVertice(){
  return paiVertice;
}

class Kruskal{
private:
  vector<pair<pair<int,int>,float>> arvore;
  void kruskal(Neuronio &);
  Uniao uniao;
public:
  Kruskal();
  void run(Neuronio &);
  //void iniciaKruskal(int);
  //int encontraPai(int);
  //void uniaoVertices(int,int);
};
Kruskal::Kruskal(){}
void Kruskal::run(Neuronio &neuronio){
  kruskal(neuronio);
}

void Kruskal::kruskal(Neuronio &neuronio){
    int ordem = neuronio.getOrdemNeuronio();
    //iniciaKruskal(ordem);
    uniao.iniciaUniao(ordem); // inicia a Union-Find
    neuronio.ordena(); //Tá funcionando, está ordenando

    vector<pair<pair<int,int>,float>> arestas;
    arestas = neuronio.getverticesPesoNeuronio();

    for(int i=0;i<arestas.size();i++){
      int vertice1 = uniao.encontraPai(arestas[i].first.first); //método que busca o pai do conjunto
      int vertice2 = uniao.encontraPai(arestas[i].first.second);

      if(vertice1 != vertice2){
        arvore.push_back(arestas[i]);
        uniao.uniaoVertices(vertice1,vertice2);
      }
    }
    //imprime Arvore gerada pelo
    /*for(int i=0;i<arvore.size();i++){
      cout << arvore[i].first.first << " " << arvore[i].first.second << " " << arvore[i].second << endl;
    }*/

}

class Dijkstra{
private:
  int *d;
  int *pred;
  int *vertex;
  void dijkstra(Cerebro &,int );
public:
  Dijkstra();
  void run(Cerebro &,int,int);
  int getD(int);
  void inicializaDijkstra(Cerebro &,int);
  void relaxa(Vertice<Vertex> &u,Vertice<Vertex> &v);
};
Dijkstra::Dijkstra(){
}

void Dijkstra::run(Cerebro &g,int origem,int destino){
  dijkstra(g,origem,destino);
}

int Dijkstra::getD(int vertex){
  return d[vertex];
}

void Dijkstra::inicializaDijkstra(Cerebro &g,int s){ // Inicializa predecessor,distancia
  int ordem = g.getOrdemCerebro()
  vertex = new int[ordem];
  pred = new int[ordem];
  d = new int[ordem];

  for(int i=0;i<N;i++){
    vertex[i] = i;
    pred[i] = NIL;
    d[i] = INFINITO;
  }
  d[s] = 0;
}

/*int DKJ::somaDist(Grafo &g,int u,int v){
  return g.getPeso(u,v) + d[u];
}*/

void Dijkstra::relaxa(int u,int v,int w){
  if(d[v] > (d[u] + w)){
    d[v] = d[u] + w;
    pred[v] = u;
  }
}

void Dijkstra::dijkstra(Cerebro &g,int s){
  InicializaDKJ(g,s);
  //Q = G.V -> fila de prioridade minima;
  /*
    while( Q!= vazio ){
      u = extract-min(Q);
      S = S U {u};
      para cada v E G.Adj[u]
        float = Cerebro.getPesoCerebro(u,v);
        relaxa(u,v,w);
    }
   */
}

class Cerebro{
private:
  float **vertices;
  int ordemCerebro,tamanhoCerebro;
  Neuronio *neuronio;
  Cores *cor;
public:
  Cerebro(int,int);
  void inicializaCerebro(int,int);
  void insereVerticeCerebro(int,int,float);
  void imprimeCerebro();
  int getOrdemCerebro();
  int getTamanhoCerebro();
  int getPesoCerebro(int,int);
  void inicializaCerebroNeuronio(int,int, int);
  void insereCerebroNeuronio(int,int,int,float);
  void imprimeCerebroNeuronio(int);

};
Cerebro::Cerebro(int ordem,int tamanho){
  inicializaCerebro(ordem,tamanho);
}

void Cerebro::inicializaCerebro(int ordem,int tamanho){
  this->ordemCerebro = ordem;
  this->tamanhoCerebro = tamanho;
  vertices = new float*[ordem+1]; //cria matriz
  for(int i=1;i<=ordem;i++){
    vertices[i] = new float[ordem+1];
  }

  for(int i=1;i<=ordem;i++){ // inicializa matriz com 0
    for(int j=1;j<=ordem;j++){
      vertices[i][j] = 0;
    }
  }

  neuronio = new Neuronio[ordem+1];
}

void Cerebro::insereVerticeCerebro(int u, int v,float peso){
 vertices[u][v] = peso;
 //vertices[v][u] = peso;
}

void Cerebro::imprimeCerebro(){
  int k = 5;
    cout << "   ";
    for (int j = 1; j <= this->ordemCerebro; j++){
        cout << setw(k) << j;
    }
    cout << endl;
    for (int j = 1; j <= (this->ordemCerebro*k+3); j++){
        cout << "-";
    }
    cout << endl;
    for (int i = 1; i <= this->ordemCerebro; i++){
        cout << setw(1) << i;
        cout << " |";
        for (int j = 1; j <= this->ordemCerebro; j++){
            cout << setw(k) << vertices[i][j];
        }
        cout << endl;
    }
}

int Cerebro::getTamanhoCerebro(){
 return tamanhoCerebro;
}

int Cerebro::getOrdemCerebro(){
 return ordemCerebro;
}

int Cerebro::getPesoCerebro(int u,int v){
 return vertices[u][v];
}

void Cerebro::inicializaCerebroNeuronio(int indice,int ordem,int tamanho){
    neuronio[indice].inicializaNeuronio(ordem,tamanho);
}

void Cerebro::insereCerebroNeuronio(int indice,int u,int v,float peso){
    neuronio[indice].insereVerticeNeuronio(u,v,peso);
}

void Cerebro::imprimeCerebroNeuronio(int indice){
  cout << endl;
  cout << "Bloco Neuronio["<< indice <<"]" <<endl;
  neuronio[indice].imprimeNeuronio();
  //neuronio[indice].mostraVerticePeso(); está pegando
  Kruskal k;
  k.run(neuronio[indice]);
}



int main(int argc, char const *argv[]) {
  /* code */
  Cerebro cerebro(5,6);
  cerebro.insereVerticeCerebro(1,2,3.5);
  cerebro.insereVerticeCerebro(1,3,2.6);
  cerebro.insereVerticeCerebro(1,4,3.2);
  cerebro.insereVerticeCerebro(1,5,2.1);
  cerebro.insereVerticeCerebro(2,5,1.0);
  cerebro.insereVerticeCerebro(3,4,1.1);

  cerebro.imprimeCerebro();

  cerebro.inicializaCerebroNeuronio(1,3,3); //passo a qual vertice o neuronio pertence , a ordem desse bloco e o tamanho
  cerebro.insereCerebroNeuronio(1,1,2,2.5);
  cerebro.insereCerebroNeuronio(1,1,3,3.5);
  cerebro.insereCerebroNeuronio(1,2,3,1.0);
  cerebro.imprimeCerebroNeuronio(1);

  return 0;
}

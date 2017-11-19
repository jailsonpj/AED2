#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <cfloat>
#include <iomanip>
#define NIL -1
#define INFINITO 1111;

enum Cores {BRANCO,CINZA,PRETO};
using namespace std;

//classe Union-Find - falta colocar template
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

//Classe Fila de Prioridade usada no Dijkstra
class FilaPrioridade{
private:
  int heapTamanho;
  pair <int,float> *v;
public:
  FilaPrioridade();
  void filaInicializa(int tamanho);
  void minHeapifica(int );
  pair<int,float> minHeap();
  void diminuirValor (int i, pair<int,float>);
  void enfileira(pair<int,float> );
  pair<int,float> desenfileira();
  void imprimirFilaPrioridade();
  bool vazia();
};
FilaPrioridade::FilaPrioridade(){

}

void FilaPrioridade::filaInicializa(int tamanho){
  this->heapTamanho = 0;
  v = new pair<int,float>[tamanho+1];
}

void FilaPrioridade::minHeapifica(int i){ //heapfica
  int esquerda = 2*i;
  int direita = 2*i+1;
  int menor;

  if(esquerda <= heapTamanho and v[esquerda].second < v[i].second){
    menor = esquerda;
  }else{
    menor = i;
  }

  if(direita <= heapTamanho and v[direita].second < v[menor].second){
    menor = direita;
  }

  if(menor != i){
    swap(v[i],v[menor]);
    minHeapifica(menor);
  }
}

pair<int,float> FilaPrioridade::minHeap(){ //retorna o valor do nó minimo
  return v[0];
}

void FilaPrioridade::diminuirValor (int i, pair<int,float> val)
{
    if(val.second > v[i].second)
    {
        cout<< "Novos valores são inferiores ao valor atual, não podem ser inseridos" <<endl;
        return;
    }
    v[i].first = val.first;
    v[i].second = val.second;
    while( i > 0 and v[i/2].second > v[i].second)
    {
        swap(v[i/2], v[i]);
        i = i/2;
    }
}

void FilaPrioridade::enfileira(pair<int,float> n){
    ++heapTamanho;
    v[heapTamanho-1].first = INT_MAX;
    v[heapTamanho-1].second = FLT_MAX;
    diminuirValor(heapTamanho - 1,n);
}

pair<int,float> FilaPrioridade::desenfileira(){
  if(heapTamanho < 0){
    cout << "heap vazio" << endl;
  }
  pair<int,float> min = v[0];
  v[0] = v[heapTamanho-1];
  --heapTamanho;
  minHeapifica(0);
  return min;
}

bool FilaPrioridade::vazia(){
  if(heapTamanho < 0){
      return true;
  }
}

void FilaPrioridade::imprimirFilaPrioridade(){
    cout << "saida" << endl;
    while(heapTamanho){ // enquanto tamanho da fila for diferente do tamanho da heapsize faça
        pair<int,float> ext = desenfileira();
        cout << ext.first <<" "<< ext.second << endl;
    }
}

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

class Kruskal{
private:
  vector<pair<pair<int,int>,float>> arvore;
  void kruskal(Neuronio &);
  Uniao uniao; //atributo para a classe Union-Find
public:
  Kruskal();
  void run(Neuronio &);
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
//Classe Grafo-Cérebro
class Cerebro{
private:
  float **adjVertices;
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
  adjVertices = new float*[ordem+1]; //cria matriz
  for(int i=1;i<=ordem;i++){
    adjVertices[i] = new float[ordem+1];
  }

  for(int i=1;i<=ordem;i++){ // inicializa matriz com 0
    for(int j=1;j<=ordem;j++){
      adjVertices[i][j] = NIL;
    }
  }

  neuronio = new Neuronio[ordem+1];
}

void Cerebro::insereVerticeCerebro(int u, int v,float peso){
 adjVertices[u][v] = peso;
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
            cout << setw(k) << adjVertices[i][j];
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
 return adjVertices[u][v];
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
  /*Kruskal k;
  k.run(neuronio[indice]);*/ //Kruskal está pegando
}

//classe Dijkstra
class Dijkstra{
private:
  int *distancia;
  int *pred;
  int *vertice;
  void dijkstra(Cerebro &,int,int);
  FilaPrioridade fila;
public:
  Dijkstra(){};
  void run(Cerebro &,int,int);
  int getDistancia(int);
  void inicializaDijkstra(Cerebro &,int);
  void relaxa(int u, int v, int w);
  int *getPred();
};

void Dijkstra::run(Cerebro &g,int origem,int destino){
  dijkstra(g,origem,destino);
}

int Dijkstra::getDistancia(int vertice){
  return distancia[vertice];
}

void Dijkstra::inicializaDijkstra(Cerebro &g, int origem){ // Inicializa predecessor,distancia
  int ordem = g.getOrdemCerebro();
  vertice = new int[ordem+1];
  pred = new int[ordem+1];
  distancia = new int[ordem+1];

  for(int i=1;i<=ordem;i++){ //inicia os vetores conforme os vertices,mesmo funcionamento da BFS
    vertice[i] = i;
    pred[i] = NIL;
    distancia[i] = INFINITO;
  }
  distancia[origem] = 0;
  fila.filaInicializa(ordem); //Inicializa a Fila de Prioridade
  fila.enfileira({origem,distancia[origem]}); //passa o vertice inicial e seu pred e a sua distancia
}

void Dijkstra::relaxa(int u, int v, int w){
  if(distancia[v] > (distancia[u] + w)){
    distancia[v] = distancia[u] + w;
    pred[v] = u;
    fila.enfileira({v,distancia[v]});
  }
}

void Dijkstra::dijkstra(Cerebro &g, int origem, int destino){
  inicializaDijkstra(g,origem);
  while(fila.vazia()){
      pair<int,float> u = fila.desenfileira();
      for(int v=1;v<=g.getOrdemCerebro();v++){
          float w = g.getPesoCerebro(u.first,v);
          if(w != NIL){
            relaxa(u.first,v,w);
          }
      }
    }
}

int *Dijkstra::getPred(){
  return pred;
}

int main(int argc, char const *argv[]) {
  /* code */
  Cerebro cerebro(6,8);
  cerebro.insereVerticeCerebro(1,2,2);
  cerebro.insereVerticeCerebro(1,3,1);
  cerebro.insereVerticeCerebro(2,5,4);
  cerebro.insereVerticeCerebro(2,4,3);
  cerebro.insereVerticeCerebro(3,4,2);
  cerebro.insereVerticeCerebro(3,5,6);
  cerebro.insereVerticeCerebro(4,6,7);
  cerebro.insereVerticeCerebro(5,6,8);

  cerebro.imprimeCerebro();

  Dijkstra dk;
  dk.run(cerebro,1,6);
  cout << dk.getDistancia(6) << endl;

  /*cerebro.inicializaCerebroNeuronio(1,3,3); //passo a qual vertice o neuronio pertence , a ordem desse bloco e o tamanho
  cerebro.insereCerebroNeuronio(1,1,2,2.5);
  cerebro.insereCerebroNeuronio(1,1,3,3.5);
  cerebro.insereCerebroNeuronio(1,2,3,1.0);
  cerebro.imprimeCerebroNeuronio(1);*/

  /*FilaPrioridade fp; //está super pegando a fila de prioridade
  //pair<pair<int,int>,float> v = {{1,2},99};
  fp.filaInicializa(9);
  fp.enfileira({1,99});
  fp.enfileira({3,9});
  fp.enfileira({4,3});
  fp.enfileira({5,19});
  fp.enfileira({2,4});
  fp.enfileira({10,1});
  fp.enfileira({8,5});
  fp.enfileira({9,2});

  fp.imprimirFilaPrioridade();*/

  return 0;
}

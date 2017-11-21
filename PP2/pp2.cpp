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

template <class T>
class Uniao{
private:
  T *paiVertice;
public:
  Uniao();
  void iniciaUniao(T);
  T encontraPai(T);
  void uniaoVertices(T,T);
  T *getPaiVertice();
};
template <class T>
Uniao<T>::Uniao(){ //construtor
}
template <class T>
void Uniao<T>::iniciaUniao(T ordem){
  paiVertice = new T[ordem+1];
  for(int i=1;i<=ordem;i++){
    paiVertice[i] = -1;
  }
}
template <class T>
T Uniao<T>::encontraPai(T vertice){
  if(paiVertice[vertice] == -1){
    return vertice;
  }
  return encontraPai(paiVertice[vertice]);
}
template <class T>
void Uniao<T>::uniaoVertices(T vertice1,T vertice2){ //faz a uniao entre dois conjuntos
  vertice1 = encontraPai(vertice1);
  vertice2 = encontraPai(vertice2);

  paiVertice[vertice1] =  vertice2;
}
template <class T>
T * Uniao<T>::getPaiVertice(){
  return paiVertice;
}
//Classe Fila de Prioridade usada no Dijkstra
template <class T>
class FilaPrioridade{
private:
  int heapTamanho;
  pair <int,T> *v;
public:
  FilaPrioridade();
  void filaInicializa(int tamanho);
  void minHeapifica(int );
  pair<int,T> minHeap();
  void diminuirValor (int i, pair<int,T>);
  void enfileira(pair<int,T> );
  pair<int,T> desenfileira();
  void imprimirFilaPrioridade();
  bool vazia();
};
template <class T>
FilaPrioridade<T>::FilaPrioridade(){
}
template <class T>
void FilaPrioridade<T>::filaInicializa(int tamanho){
  this->heapTamanho = 0;
  v = new pair<int,T>[tamanho+1];
}
template <class T>
void FilaPrioridade<T>::minHeapifica(int i){ //heapfica
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
template <class T>
pair<int,T> FilaPrioridade<T>::minHeap(){ //retorna o valor do nó minimo
  return v[0];
}
template <class T>
void FilaPrioridade<T>::diminuirValor (int i, pair<int,T> val)
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
template <class T>
void FilaPrioridade<T>::enfileira(pair<int,T> n){
    ++heapTamanho;
    v[heapTamanho-1].first = INT_MAX;
    v[heapTamanho-1].second = FLT_MAX;
    diminuirValor(heapTamanho - 1,n);
}
template <class T>
pair<int,T> FilaPrioridade<T>::desenfileira(){
  if(heapTamanho < 0){
    cout << "heap vazio" << endl;
  }
  pair<int,T> min = v[0];
  v[0] = v[heapTamanho-1];
  --heapTamanho;
  minHeapifica(0);
  return min;
}
template <class T>
bool FilaPrioridade<T>::vazia(){
  if(heapTamanho < 0){
      return true;
  }
}
template <class T>
void FilaPrioridade<T>::imprimirFilaPrioridade(){
    cout << "saida" << endl;
    while(heapTamanho){ // enquanto tamanho da fila for diferente do tamanho da heapsize faça
        pair<int,T> ext = desenfileira();
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
  void setNeuronioCor(int);
  Cores *getNeuronioCor();
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

 for(int i=1;i<=ordem;i++){ // inicializa matriz com NIL
   for(int j=1;j<=ordem;j++){
     adjNeuronio[i][j] = NIL;
   }
 }
 cor = new Cores[ordem+1];
 for(int i=1;i<=ordem;i++){//inicializa o vetor de cores tudo com branco
   cor[i] = BRANCO;
 }
}

void Neuronio::insereVerticeNeuronio(int u, int v,float peso){
 adjNeuronio[u][v] = peso;
 //adjNeuronio[v][u] = peso;

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

void Neuronio::setNeuronioCor(int indice){
  cor[indice] = PRETO;
}

Cores *Neuronio::getNeuronioCor(){
  return cor;
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
  Uniao<int> uniao; //atributo para a classe Union-Find
  float somaCusto;
public:
  Kruskal();
  void run(Neuronio &);
  float getSomaCusto();
};
Kruskal::Kruskal(){}
void Kruskal::run(Neuronio &neuronio){
  this->somaCusto = 0;
  kruskal(neuronio);
}

void Kruskal::kruskal(Neuronio &neuronio){
    int ordem = neuronio.getOrdemNeuronio();
    //float somaCusto = 0;//inicia soma custo com 0;
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
        somaCusto = somaCusto + arestas[i].second;
      }
    }
    //imprime Arvore gerada pelo
    /*for(int i=0;i<arvore.size();i++){
      cout << arvore[i].first.first << " " << arvore[i].first.second << " " << arvore[i].second << endl;
    }*/

}
float Kruskal::getSomaCusto(){
  return somaCusto;
}

//Classe Grafo-Cérebro
class Cerebro{
private:
  float **adjVertices;
  int ordemCerebro,tamanhoCerebro;
  Neuronio *neuronio;
  Cores *cor;
public:
  Cerebro();
  void inicializaCerebro(int,int);
  void insereVerticeCerebro(int,int,float);
  void imprimeCerebro();
  int getOrdemCerebro();
  int getTamanhoCerebro();
  int getPesoCerebro(int,int);
  void setCerebroCor(int);
  Cores getCerebroCor(int);
  void inicializaCerebroNeuronio(int,int, int);
  void insereCerebroNeuronio(int,int,int,float);
  void imprimeCerebroNeuronio(int);
  float executaCerebroNeuronio(int);

};
Cerebro::Cerebro(){}
/*Cerebro::Cerebro(int ordem,int tamanho){
  inicializaCerebro(ordem,tamanho);
}*/

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
  cor = new Cores[ordem+1];

  for(int i=1;i<=ordem;i++){//inicializa vetor de cores com todos os vertices na cor branca
    cor[i] = BRANCO;
  }

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

void Cerebro::setCerebroCor(int indice){
  cor[indice] = CINZA;
}

Cores Cerebro::getCerebroCor(int indice){
  return cor[indice];
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
}

float Cerebro::executaCerebroNeuronio(int indice){
  Kruskal kr;
  kr.run(neuronio[indice]);//executa o algotimo de Kruskal para o neuronio na posição indice
  return kr.getSomaCusto();//vai retornar a soma os pesos pelo caminho gereado pelo Kruskal
}

//classe Dijkstra
class Dijkstra{
private:
  int *distancia;
  int *pred;
  int *vertice;
  void dijkstra(Cerebro &,int,int);
  vector<int> caminhoMin;
  FilaPrioridade<float> fila;
public:
  Dijkstra(){};
  void run(Cerebro &,int,int);
  int getDistancia(int);
  void inicializaDijkstra(Cerebro &,int);
  void relaxa(int u, int v, int w);
  int *getPred();
  vector<int> getCaminhoMin(int);
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
          float w = g.getPesoCerebro(u.first,v); //me retorna o peso da aresta entre os vertices u e v
          if(w != NIL){ //se for diferente de NIL significa que existe um peso e uma ligacao entre os vértices
            relaxa(u.first,v,w);
          }
      }
    }
}

int *Dijkstra::getPred(){
  return pred;
}

vector<int>Dijkstra::getCaminhoMin(int destino){ //gera um vector com o caminho de custo minimo gerado pelo Dijkstra a parti do vertice de destino
    caminhoMin.push_back(destino);
    int min = pred[destino];
    while(min != NIL){
      caminhoMin.push_back(min);
      min = pred[min];
    }
    return caminhoMin;
}

class Processamento{
private:
  Dijkstra dk;
  vector<int> v;
  float somaCustoSaida;
public:
  Processamento();
  void executaDk(Cerebro &,int,int);
  void executaKr(Cerebro &);
  float getSomaCustoSaida();

};
Processamento::Processamento(){
}
void Processamento::executaDk(Cerebro &cerebro,int origem,int destino){
  dk.run(cerebro,origem,destino);
  v = dk.getCaminhoMin(destino);
  //cout << dk.getDistancia(destino) << endl;

}
void Processamento::executaKr(Cerebro &cerebro){
  this->somaCustoSaida = 0;
  for(int i=0;(int)i<v.size();i++){
    if(cerebro.getCerebroCor(v[i]) == CINZA){//verifica se o vertice é doente ou seja que tem no grafo de dentro nodulos doentes
      somaCustoSaida = somaCustoSaida + cerebro.executaCerebroNeuronio(v[i]);
    }
  }
}

float Processamento::getSomaCustoSaida(){
  return somaCustoSaida;
}

class Entrada{
private:
  Cerebro cerebro;
  Processamento processa;
  int n;
  int m;
  int entrada;
  int saida;
public:
  Entrada();
  void inicia();
  void termina();
  void entradaCerebro();
  void entradaInicioFim();
  void entradaNeuronio();
  void entradaProcessa();
  void entradaFinaliza();

};
Entrada::Entrada(){
}

void Entrada::inicia(){
  string ordem,tamanho; //ordem e tamanho que será passado para a criação do grafo
  //int n,m; //vai receber os valores quando forem convertido para int

  cin >> ordem;
  cin >> tamanho;

  this->n = atoi(ordem.c_str()); //converte a string ordem para int
  this->m = atoi(tamanho.c_str()); //converte a string tamanho para int


}
void Entrada::entradaInicioFim(){ //método para receber as entradas do inicio e fim do Dijkstra
  string inicio,fim;

  cin >> inicio;
  cin >> fim;

  this->entrada = atoi(inicio.c_str());
  this->saida = atoi(fim.c_str());
}

void Entrada::entradaCerebro(){
  cerebro.inicializaCerebro(n,m);//inicia Grafo-Cerebro com ordem n e tamanho m;

  for(int i=1;i<=m;i++){ //laço que recebe as entradas do Grafo-Cerebro
    string vertice1,vertice2,peso; //variaveis que recebe os vertices e peso
    int v1,v2; //variaveis que recebem os vertices depois da conversão
    float p;

    cin >> vertice1;
    cin >> vertice2;
    cin >> peso;

    v1 = atoi(vertice1.c_str());
    v2 = atoi(vertice2.c_str());
    p = atoi(peso.c_str());

    cerebro.insereVerticeCerebro(v1,v2,p); //insere os vertices do Grafo-Cerebro
  }
  entradaInicioFim();
  cerebro.imprimeCerebro();
}

void Entrada::entradaNeuronio(){ //método que recebe as entrdas dos blocos de Neurônios

  for(int i=1;i<=n;i++){

    string ordem,tamanho,doentes,vertice1,vertice2,peso;
    int n1,m1,ndoentes,v1,v2,p;

    cin >> ordem;
    cin >> tamanho;

    n1 = atoi(ordem.c_str());
    m1 = atoi(tamanho.c_str());

    cerebro.inicializaCerebroNeuronio(i,n1,m1);

    cin >> doentes;
    ndoentes = atoi(doentes.c_str());

    if(ndoentes == 0){

      for(int k=0;k<m1;k++){ //recebe as entradas ate o tamanho do tamanho do Grafo-Neuronio
        cin >> vertice1;
        cin >> vertice2;
        cin >> peso;

        v1 = atoi(vertice1.c_str());
        v2 = atoi(vertice2.c_str());
        p = atoi(peso.c_str());

        cerebro.insereCerebroNeuronio(i,v1,v2,p);
      }

    }else{
      cerebro.setCerebroCor(i);//marca no vetor de cores na posição i, o vertice como doente
      for(int j=1;j<=ndoentes;j++){ //for que recebe as entrdas de qnts nós estão doentes
        //cout << "entrou 1" << endl;
        string doentes1;
        int ndoentes1;
        cin >> doentes1;
        ndoentes1 = atoi(doentes1.c_str());
        //AQUI! - para cada nó doente preencher de preto no vetor de cores
        //AQUI! - e fazer com que o vector de cores do cerebro para um tal vertice seja como doente
      }

      for(int k=0;k<m1;k++){//recebe as entradas ate o tamanho do tamanho do Grafo-Neuronio
        cin >> vertice1;
        cin >> vertice2;
        cin >> peso;

        v1 = atoi(vertice1.c_str());
        v2 = atoi(vertice2.c_str());
        p = atoi(peso.c_str());

        cerebro.insereCerebroNeuronio(i,v1,v2,p);
      }

    }

  }

  /*for(int i=1;i<=n;i++){
    cerebro.imprimeCerebroNeuronio(i);
  }*/

}

void Entrada::entradaProcessa(){
  processa.executaDk(cerebro,entrada,saida);
  processa.executaKr(cerebro);
}
void Entrada::entradaFinaliza(){
  cout << processa.getSomaCustoSaida() << endl;
}

int main(int argc, char const *argv[]) {

  Entrada ent;
  ent.inicia();
  ent.entradaCerebro();
  ent.entradaNeuronio();
  ent.entradaProcessa();
  ent.entradaFinaliza();

  return 0;
}

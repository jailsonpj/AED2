#include <iostream>
#include <vector>
#define NIL -1
using namespace std;

class Processamento{
private:
	vector<int> numeros {NIL, 49, 50, 51, 52, 53, 54, 55, 56}; //1,2,3...
	vector<int> letras {NIL, 97, 98, 99, 100, 101, 102, 103, 104};//a,b,c,d...
	vector<pair<int, int> > coordenadas;
	vector<pair<string,int> > saida;
	vector<string> entrada; // vector com as posicoes dos cavalos e rei
	string jogada; //posicao de cada cavalo e do rei

public:
	Processamento();
	void mostra();
	void recebeEntrada();
	void mostraEntrada(vector<pair<int,int> >);
	void mostraSaida(vector< pair<string,int> >);
	void convertePosicao();
	void invertePosicao();
};

Processamento::Processamento(){
	recebeEntrada();
}

void Processamento::mostra(){
	for (int i = 0; i < entrada.size(); ++i){
		cout << entrada[i] << " ";
	}
	cout << endl;
}

void Processamento::recebeEntrada(){
	for(int i = 0; i < 5; ++i){
		cin >> jogada;
		cin.ignore();
		entrada.push_back(jogada);
	}
	mostra();
	convertePosicao();
	cout << "------------\n";
	invertePosicao();
}

void Processamento::mostraEntrada(vector<pair<int,int> > vec){
	for ( vector <pair<int,int> >::const_iterator it = vec.begin(); it != vec.end (); it++){
		cout << it->first << it->second << endl;
	}
}

void Processamento::mostraSaida(vector< pair<string,int> > vec){
	for ( vector <pair<string,int> >::const_iterator it = vec.begin(); it != vec.end (); it++){
		cout << it->first << it->second << endl;
	}
}

void Processamento::convertePosicao(){
	pair<int, int> par; 

	for (int i = 0; i < entrada.size(); ++i){
		par = make_pair(entrada[i][1], entrada[i][0]);
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
	mostraEntrada(coordenadas);
}

void Processamento::invertePosicao(){
	pair<string, int> par;
	for (int i = 0; i < coordenadas.size(); ++i){
		for (int j = 1; j <= letras.size(); ++j){
			if(coordenadas[i].second == j){
				par = make_pair(letras[j],coordenadas[i].first);
				saida.push_back(par);
			}
		}
	}
	mostraSaida(saida);
}


int main(int argc, char const *argv[]){
	Processamento();
	return 0;
}
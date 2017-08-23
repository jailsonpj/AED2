#include<iostream>
#include<cstdlib>
#include<ctime>
#include "Lista.h"

using namespace std;

//Dado
class Dado{
public:
  int valor;
public:
  Dado();
  void sorteia();
  void setValor(int);
  int getValor();
};
Dado::Dado(){
    this->valor = 0;
}
void Dado::sorteia(){
//  srand((unsigned) time(0));//gera somente aleatorio
  short inferior = 1;
  short superior = 6;
  this->valor = rand()%(superior - inferior + 1) + inferior;
}
void Dado::setValor(int valor){
  this->valor = valor;
}
int Dado::getValor(){
  return valor;
}

//Caneca
class Caneca {
public:
  int valor;
  Lista<Dado> *dado;
  //Caneca();
public:
  Caneca();
  void lancaDados();
  void setValor(int);
  int getValor();
};
Caneca::Caneca(){
  this->valor = 0;
  dado = new Lista<Dado>(4);

  Dado *a = new Dado();
  Dado *b = new Dado();
  Dado *c = new Dado();

  dado->insere(a);
  dado->insere(b);
  dado->insere(c);
}
void Caneca::lancaDados(){
  for(int i =1;i<=dado->getN();i++){
    dado->getItem(i)->sorteia();
    valor += dado->getItem(i)->getValor();
  }
}
void Caneca::setValor(int valor){
  this->valor = valor;
}
int Caneca::getValor(){
  return valor;
}

class Jogador{
public:
  string nome;
  int pontos;
  Caneca *caneca;
public:
  Jogador();
  void joga();
  void setNome(string nome);
  string getNome();
  int getPontos();
};
Jogador::Jogador(){
  //this->nome = nome;
  this->pontos = 0;
  caneca = new Caneca();
}
void Jogador::joga(){
  caneca->lancaDados();
  pontos = caneca->getValor();
}
void Jogador::setNome(string nome){
  this->nome = nome;
}
string Jogador::getNome(){
  return nome;
}
int Jogador::getPontos(){
  return pontos;
}

int main(int argc, char const *argv[]) {

  srand((unsigned) time(0));//gera somente aleatorio

  Lista<Jogador> *l;
  l = new Lista<Jogador>(3); //Lista de Jogadores

  Jogador *j1 = new Jogador(); //instancia do Jogador 1
  Jogador *j2 = new Jogador(); //instancia do jogador 2

  j1->setNome("Maquina");
  j2->setNome("Homem");

  l->insere(j1);
  l->insere(j2);

  cout << "foi" << '\n';
  cout << "foi" << '\n';


  //int valor = 50;
  bool termina = false;
  int cont = 1;
  int soma1 = 0;
  int soma2 = 0;
  int ganhador;

  /*short inferior = 1;
  short superior = 6;*/

  while (termina == false) { //funciona de Boas!!
    l->getItem(cont)->joga();
    soma1 += l->getItem(cont)->getPontos();
    if(soma1 >= 53){
      //ganhador = cont;
      cout << "Ganhador: " << l->getItem(cont)->getNome() << endl;
      termina = true;
    }else{
      l->getItem(cont+1)->joga();
      soma2 += l->getItem(cont+1)->getPontos();
      //soma2 = rand()%(superior) + inferior;
      if (soma2 >= 53) {
        //ganhador = cont;
        cout << "Ganhador: " << l->getItem(cont+1)->getNome() << endl;
        termina = true;
      }
    }
  }

  /*l->getItem(cont)->joga();
  soma1 += l->getItem(cont)->getPontos();

  l->getItem(cont+1)->joga();
  soma2 += l->getItem(cont+1)->getPontos();
  soma2 = rand()%(18 - 3 + 1) + inferior;

  cout << "nome: " << l->getItem(cont)->getNome() << endl;
  cout << "Pontos: " << soma1 << endl;

  cout << "nome: " << l->getItem(cont+1)->getNome() << endl;
  cout << "Pontos: " << soma2 << endl;*/

  return 0;
}

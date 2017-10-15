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

void Matriz::mapeaCavalo(int l,int c){
  vector<int> di = {-1,+1,-2,+2,-2,-2,+2,-1,+1};
  vector<int> dj = {-2,-2,-1,-1,-1,+1,+1,+2,+2};
  int l1,c1;
  for(int i=0;i<=8;i++){
    l1 = l+ di[i];
    c1 = c+dj[i];
    if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
        mat[l1][c1] = 3;
      }
  }
}

void Matriz::mapeaRei(int l,int c){
  vector<int> di = {-1,+1,-2,+2,-2,-2,+2,-1,+1};
  vector<int> dj = {-2,-2,-1,-1,-1,+1,+1,+2,+2};

  int l1,c1;
  int cont = 0;

  for(int i=0;i<8;i++){
    l1 = l+ di[i];
    c1 = c+dj[i];
    if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
      cont++;
    }
  }

  //Grafo g(cont);
  for(int i=0;i<=8;i++){
    l1 = l+ di[i];
    c1 = c+dj[i];
    if((l1>=1 && l1<=8) && (c1>=1 && c1<=8)){
      mat[l1][c1] = 3;
      //g.insertEdge(1,i+2);
    }
  }

  //g.print();
}

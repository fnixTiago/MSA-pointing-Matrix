#include "Pointing.h"
#include "NW.h"
#include "PointingN.h"
#include "NW_N.h"
#include <fstream>

typedef vector<string> V;
typedef vector<V> M_X;
class TPS
{
public:
  int mat;
  int mis;
  int gap;
  V data;
  multimap<double, pair<int, int> > agrupados;
  vector<pair<int,int>> positions;
  V respuesta;
  V m_fila;
  V m_col;
  bool tipo; //NW o Pointing
  //pointing
  vector<vector<int> > point_mat;//puntuacion de la matrix de (n+1)x(m+1)
  vector<vector<int> > score_mat;//puntuacion de la matrix de 2x(m+1)
  vector<string > v_result;
public:
  TPS();
  void insert_data(V &v);
  void metodo(bool opcion);
  void agrupar();
  void eliminar_pos(vector<pair<int,int>> &v,pair<int,int>&pos);//elimina posiciones a agrupados
  void penaltys(int m, int mi, int g);
  bool existe(vector<pair<int,int>> &v,pair<int,int>&pos);
  void unir_Pointing();
  void algoritmo1_Pointing();
  void algoritmo2_Pointing();
  int distancia_gaps_izq(vector<string> &v, int pos, int gaps_t );
  int distancia_gaps_sup(vector<string> &v, int pos, int gaps_t );
  int distancia_nucleotidos(vector<string>&data_f, vector<string>&data_c,int position_i,int position_j);
  
  int unir_gaps_izq(vector<string> &v,vector<string> &resp, int pos, int gaps_t );
  int unir_gaps_sup(vector<string> &v,vector<string> &resp, int pos, int gaps_t );
  void unir_nucleotidos(vector<string> &v1,vector<string> &v2,vector<string> &resp, int pos1,int pos2);
  void add_gap_inicio(vector<string> &v);
  //int get_maximo(vector<int> &v)
  int res(char c1, char c2){
    if(c2==c1 && c1!='-')
      return mat;
    else if(c2==c1 && c1=='-')
      return 0;
    else{
      if(c1!=c2 && c1!='-' || c2!='-')
        return mis;
      else return gap;
    }
  }
  ~TPS();
  
};

TPS::TPS(){


}
TPS::~TPS(){
  positions.clear();
  agrupados.clear();
}
void TPS::insert_data(V &vec){
  data=vec;
}
void TPS:: add_gap_inicio(vector<string> &v){
  for (int i = 0; i < v.size(); ++i){
    v[i] ="-"+v[i];
  }
}


void TPS::agrupar(){
  vector<pair<int,int>> tmp;
  V par_alineados;//respuesta de alineamiento
  double dist=0.0;//distancia
  for (int i = 0; i < data.size(); ++i){
    for (int j = i+1; j < data.size(); ++j){
      if(tipo==0){
        NW n(data[i],data[j],mat,mis,gap);
        n.ejecutar(par_alineados);
        dist =n.pair_wise()*1.0/par_alineados[0].size();
        agrupados.insert(make_pair(dist,make_pair(i,j)));
      }
      else{
        Pointing po(data[i],data[j],mat,mis,gap);
        po.ejecutar(par_alineados);
        dist =po.pair_wise()*1.0/par_alineados[0].size();
        agrupados.insert(make_pair(dist,make_pair(i,j)));
      }
    }
  }

  multimap<double,pair<int,int> >::reverse_iterator rit;
  for (rit=agrupados.rbegin(); rit!=agrupados.rend(); ++rit){
    tmp.push_back(make_pair((rit->second).first, (rit->second).second));
    //cout <<(rit->first)<<": "<< (rit->second).first << " => " << (rit->second).second << '\n';
  }
  for (int i = 0; i < data.size(); ++i){
    tmp.push_back(make_pair(i,i));
  }

  int tam=tmp.size();
  for (int i = 0; i < tam; ++i){
    if(existe(positions,tmp[i])==false)//si no esta;
      positions.push_back(tmp[i]);
  }
  tmp.clear();
  
}
void TPS::metodo(bool opcion){
  tipo=opcion;
  
}

bool TPS::existe(vector<pair<int,int>> &v, pair<int,int>&pos){
  if(v.size()==0)
    return false;

  for (int i = 0; i < v.size(); ++i){
    if((pos.first==(v[i]).first || pos.first==(v[i]).second)
    || (pos.second==(v[i]).first || pos.second==(v[i]).second) ){
        return true;
    }
  }
  return false;
}

void TPS::eliminar_pos(vector<pair<int,int>> &v, pair<int,int>&pos){
  int k=0;
  int tmp =v.size();
  while(k < tmp){
    for (int i = k; i < v.size(); ++i){
      if((pos.first==(v[i]).first || pos.first==(v[i]).second)
      || (pos.second==(v[i]).first || pos.second==(v[i]).second) ){
          v.erase(v.begin()+i);
      }
    }
    k++;
    tmp =v.size();
  }

}
void TPS::penaltys(int m, int mi, int g){
  mat =m;
  mis =mi;
  gap =g;
}
int TPS:: distancia_gaps_izq(vector<string> &v, int pos, int gaps_t ){
  int tmp=0;
  for (int i = 0; i < v.size(); ++i){
    for (int j = 0; j < gaps_t; ++j){
      if(v[i][pos]!='-')
        tmp +=gap;
     
    }
  }
  return tmp;
}

int TPS:: distancia_gaps_sup(vector<string> &v, int pos, int gaps_t ){
  int tmp=0;
  for (int i = 0; i < gaps_t; ++i){
    for (int j = 0; j < v.size(); ++j){
      if(v[i][pos]!='-')
        tmp +=gap;
     
    }
  }
  return tmp;
}

int TPS::distancia_nucleotidos(vector<string>&data_f, vector<string>&data_c,int position_i,int position_j){
  int tmp=0;
  for (int i = 0; i < data_c.size(); ++i){
    for (int j = 0; j < data_f.size() ; ++j){
      //cout<<"("<<data_c[i][position_j]<<" , "<<data_f[j][position_i]<<")\t";
      tmp +=res(data_c[i][position_i],data_f[j][position_j]);
    }
  }
  return tmp;
}



void TPS:: unir_Pointing(){
  vector<string> v1;
  vector<string> v2;
/*
  v1.push_back("ATGTC");
  v2.push_back("ATGTGGC");
  m_fila =v1;
  m_col =v2;
  algoritmo1_Pointing();
  algoritmo2_Pointing();
  */
/*
  v1.push_back("TGTAAC");
  v2.push_back("TGTAC");
  m_fila =v1;
  m_col =v2;
  algoritmo1_Pointing();
  algoritmo2_Pointing();
*/
  /*
  v1.push_back("ATGTGGC");
  v1.push_back("ATGT--C");
  v2.push_back("TGT-AC");
  v2.push_back("TGTAAC");
  m_fila =v1;
  m_col =v2;
  algoritmo1_Pointing();
  algoritmo2_Pointing();
  */

  v1.push_back("-TGT-AC");
  v1.push_back("-TGTAAC");
  v1.push_back("ATGT--C");
  v1.push_back("ATGTGGC");

  v2.push_back("TGTTAAC");
  m_fila =v1;
  m_col =v2;
  algoritmo1_Pointing();
  algoritmo2_Pointing();
  
}
void TPS::algoritmo1_Pointing(){
  //agregamos los gaps
  add_gap_inicio(m_fila);
  add_gap_inicio(m_col);

  //separamos memoria
  this->score_mat.resize(2);
  for (int i = 0; i < this->score_mat.size(); ++i){
    this->score_mat[i].resize(m_col[0].size() );
  }

  this->point_mat.resize(m_fila[0].size());//fila
  for (int i = 0; i < this->point_mat.size(); ++i)
  {
    this->point_mat[i].resize(m_col[0].size());//columna
  }

  int OR=0;//fila antigua
  int CR=1;//fila actual 
  int pointer; //direccion del puntero de una celda en this->point_mat
  int Max;
  int CS;//Score value of a Matrix Cell.
  int tmp=0;

  score_mat[CR][0] =distancia_gaps_sup(m_fila,1,m_fila.size());
  
  for (int i = 0; i < score_mat[0].size(); ++i){
    score_mat[0][i] =distancia_gaps_izq(m_col,i,m_fila.size());
    //score_mat[1][i+1] =3;
  }
  
  for (int i = 1; i < this->point_mat[0].size(); ++i){
    this->point_mat[0][i] =3; //movimiento horizontal
  }
  for (int i = 1; i < this->point_mat.size(); ++i){
    this->point_mat[i][0] =1; //movimiento vertical
  }

 
  int diagonal=0;
  int superior=0;
  int izquierdo=0;

  vector<int> pointers;

  CR =1;//fila actual
  for (int i = 1; i < this->point_mat.size(); ++i){
    OR =1-CR;//fila antigua
    score_mat[CR][0] =distancia_gaps_izq(m_col,i,m_fila.size());;
    for (int j = 1; j < this->point_mat[0].size(); ++j){
      diagonal =distancia_nucleotidos(m_col,m_fila,i,j);
      superior =distancia_gaps_sup(m_fila, i, m_col.size());
      izquierdo =distancia_gaps_izq(m_col, i, m_fila.size());
      CS =diagonal;
      Max =this->score_mat[OR][j-1] + CS;
      pointer=2;
      
      if (Max < this->score_mat[OR][j] + superior){//superior
        Max =this->score_mat[OR][j] + superior;
        pointer =1;
      }
      if (Max < this->score_mat[CR][j-1] + izquierdo){//horizontal
        Max =this->score_mat[CR][j-1] + izquierdo;
        pointer =3;
      }

      this->score_mat[CR][j] =Max;//scores
      this->point_mat[i][j] =pointer;//matriz


    }
    CR = OR;

      /*
      //cout<<"\t(i,j): "<<i<<","<<j<<endl;
      for (int i = 0; i < score_mat.size(); ++i){
        for (int j = 0; j < score_mat[0].size(); ++j){
          cout<<score_mat[i][j]<<" ";
        }
        cout<<endl;
      }
      cout<<"\n__________________________\n";*/
  }/*
   cout<<"\nSore Mat\n";
  for (int i = 0; i < score_mat.size(); ++i){
    for (int j = 0; j < score_mat[0].size(); ++j){
      cout<<score_mat[i][j]<<"\t";
    }
    cout<<endl;
  }
*/
  cout<<"\nPOINT MAT\n";
  for (int i = 0; i < point_mat.size(); ++i){
    //cout<<s1[i]<<"\t";
    for (int j = 0; j < point_mat[0].size(); ++j){
      cout<<point_mat[i][j]<<"\t";
    }
    cout<<endl;
  }
}
void TPS::unir_nucleotidos(vector<string> &v1,vector<string> &v2,vector<string> &resp, int pos1,int pos2){
  int ubica=0;
  for (int i = 0; i < v2.size(); ++i){
    resp[ubica] =v2[i][pos2] + resp[ubica];
    ubica++;
  }
  for (int i = 0; i <v1.size() ; ++i){
    resp[ubica] =v1[i][pos1] + resp[ubica];
    ubica++;
  }
}

int TPS::unir_gaps_izq(vector<string> &v,vector<string> &resp, int pos, int gaps_t ){
  int ubica=0;
  for (int i = 0; i < v.size(); ++i){
    resp[ubica] =v[i][pos] + resp[ubica];
    ubica++;
  }
  for (int i = 0; i <gaps_t ; ++i){
    resp[ubica] ="-" + resp[ubica];
    ubica++;
  }
}

int TPS::unir_gaps_sup(vector<string> &v,vector<string> &resp, int pos, int gaps_t ){
  int ubica=0;
  for (int i = 0; i < gaps_t; ++i){
    resp[ubica] ="-" + resp[ubica];
    ubica++;
  }
  for (int i = 0; i < v.size(); ++i){
    resp[ubica] =v[i][pos] + resp[ubica];
    ubica++;
  }
}



void TPS::algoritmo2_Pointing(){
  
  //int score =0;
  cout<<"fila\n";
  for (int i = 0; i < m_fila.size(); ++i){
    cout<<m_fila[i]<<endl;
  }
  cout<<"col\n";
  for (int i = 0; i < m_col.size(); ++i){
    cout<<m_col[i]<<endl;
  }

  vector<string> M_resp;
  M_resp.resize(m_fila.size() + m_col.size());
  int Row =(this->point_mat.size()-1);//fila 
  int Col =(this->point_mat[0].size()-1);//columna  
  int i=0;
  while(this->point_mat[Row][Col] > 0){//final
    
    if(this->point_mat[Row][Col]==2){//diagonal
        unir_nucleotidos(m_fila,m_col,M_resp,Row,Col);
      --Row;
      --Col;
    }
    else if (this->point_mat[Row][Col]==1){//vertical
      unir_gaps_sup(m_fila,M_resp, Row,m_col.size());
      //score +=-1;
      --Row;
      //Col = Col;
      

    }
    else if (this->point_mat[Row][Col]==3){//horizontal
      unir_gaps_izq(m_col,M_resp,Col,m_fila.size());
      //score +=-1;
      --Col;
      //Row =Row;

    }
  }
  cout<<"\nResultado\n";
  for (int i = 0; i < M_resp.size(); ++i){
    cout<<M_resp[i]<<endl;
  }


}
/*
void TPS::
void TPS::
void TPS::
void TPS::
void TPS::*/

void leer_data(vector<string> &data, string archivo){
  ifstream file(archivo.c_str());
  string cad="";
  while(!file.eof()){
    file>>cad;
    if(cad.size()!= 0)
      data.push_back(cad);
    cad="";
  }
  file.close();
}
int main(int argc, char const *argv[])
{

  vector<string> data;
  leer_data(data,"16.txt");
  TPS tp;
  tp.metodo(0);
  tp.insert_data(data);
  tp.penaltys(1,-1,-1);
  tp.agrupar();
  tp.unir_Pointing();
  cout<<"\nGood\n";
  return 0;
}
/*
*/
// int main(int argc, char const *argv[])
// {
  /*
  v1.push_back("ATGTC");
  v2.push_back("ATGTGGC");
  m_fila =v1;
  m_col =v2;
  algoritmo1_Pointing();
  algoritmo2_Pointing();
  */
/*
  v1.push_back("TGTAAC");
  v2.push_back("TGTAC");
  m_fila =v1;
  m_col =v2;
  algoritmo1_Pointing();
  algoritmo2_Pointing();
*/
  /*
  v1.push_back("ATGTGGC");
  v1.push_back("ATGT--C");
  v2.push_back("TGT-AC");
  v2.push_back("TGTAAC");
  m_fila =v1;
  m_col =v2;
  algoritmo1_Pointing();
  algoritmo2_Pointing();
  */
  // std::vector<string> v1,v2,v3;
  // v1.push_back("-TGT-AC");
  // v1.push_back("-TGTAAC");
  // v1.push_back("ATGT--C");
  // v1.push_back("ATGTGGC");
  // v2.push_back("TGTTAAC");
 /* v1.push_back("TGTAAC");
  v1.push_back("TGT-AC");
  v2.push_back("ATGT--C");
  v2.push_back("ATGTGGC");*/
  
  
  // cout<<"\nNW N\n";
  // NW_N nwN;
  // nwN.penaltys(1,-1,-1);
  // nwN.unir_NW_N(v2,v1);
  // nwN.get_respuesta(v3);
  // for (int i = 0; i < v3.size(); ++i)
  //   cout<<v3[i]<<endl;
  
  
  // cout<<"\nPOINTING N\n";
  // PointingN poN;
  // poN.penaltys(1,-1,-1);
  // poN.unir_Pointing(v2,v1);
  // //poN.mostrar();
  // poN.get_respuesta(v3);
  // for (int i = 0; i < v3.size(); ++i){
  //   cout<<v3[i]<<endl;
  // }

//   return 0;
// }

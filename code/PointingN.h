#ifndef PointingN_H
#define PointingN_H
#include <iostream>
#include <vector>


using namespace std;
class PointingN{
public:
	  int mat;
  	int mis;
  	int gap;
  	vector<string> respuesta;
  	vector<string> m_fila;
  	vector<string> m_col;
  	vector<vector<int> > point_mat;//puntuacion de la matrix de (n+1)x(m+1)
  	vector<vector<int> > score_mat;//puntuacion de la matrix de 2x(m+1)
public:
	PointingN();
	~PointingN();
	void penaltys(int m, int mi, int g);
	void ejecutar(std::vector<string> &v1,std::vector<string> &v2);
  void insert_data(std::vector<string> &v1,std::vector<string> &v2);
	void algoritmo1_Pointing();
	void algoritmo2_Pointing();
	
	int distancia_gaps_izq(vector<string> &v, int pos, int gaps_t );
	int distancia_gaps_sup(vector<string> &v, int pos, int gaps_t );
	int distancia_nucleotidos(vector<string>&data_f, vector<string>&data_c,int position_i,int position_j);
	  
	void unir_gaps_izq(vector<string> &v, int pos, int gaps_t );
	void unir_gaps_sup(vector<string> &v, int pos, int gaps_t );
	void unir_nucleotidos(vector<string> &v1,vector<string> &v2, int pos1,int pos2);
  void add_gap_inicio(vector<string> &v);
	int res(char c1, char c2);
  void get_respuesta(std::vector<string> &v);
 	void mostrar();
  int aptitud();
};

int PointingN::aptitud(){
  int tmp=0;
  for (int i = 0; i < respuesta.size(); ++i){
    for (int j = i+1; j <respuesta.size() ; ++j){
      for (int k = 0; k <respuesta[0].size() ; ++k){
        tmp += res(respuesta[i][k], respuesta[j][k]);
      }
    }
  }
  return tmp;
}

void PointingN::mostrar(){




	cout<<"\nMOSTRAR SCORE MAT\n";
  for (int i = 0; i <m_col.size(); ++i){
     for (int k = 0; k < m_fila.size(); ++k)
    {
      cout<<"\t";
    }

    for (int j = 0; j < m_col[0].size(); ++j){
        cout<<m_col[i][j]<<"\t";
    }   
    cout<<endl;
  }

  cout<<endl;

	for (int i = 0; i < score_mat.size(); ++i){
		for (int k = 0; k < m_fila.size(); ++k)
    {
      cout<<m_fila[k][i]<<"\t";
    }
    for (int j = 0; j < score_mat[0].size(); ++j){
			cout<<score_mat[i][j]<<"\t";
		}
		cout<<endl;
	}

 // cout<<"\nMOSTRAR M\n";  
  cout<<"\nMOSTRAR POINT MAT\n";
  //this->M.resize(m_fila[0].size());//fila
  for (int i = 0; i <m_col.size(); ++i){
     for (int k = 0; k < m_fila.size(); ++k)
    {
      cout<<"\t";
    }

    for (int j = 0; j < m_col[0].size(); ++j){
        cout<<m_col[i][j]<<"\t";
    }   
    cout<<endl;
  }

  cout<<endl;

  for (int i = 0; i < point_mat.size(); ++i){
    for (int k = 0; k < m_fila.size(); ++k)
    {
      cout<<m_fila[k][i]<<"\t";
    }
    for (int j = 0; j < point_mat[0].size(); ++j){
			cout<<point_mat[i][j]<<"\t";
		}
		cout<<endl;
	}
  cout<<"\nRESPUESTA: \n";
  for (int i = 0; i < respuesta.size(); ++i){
    for (int j = 0; j < respuesta[0].size(); ++j){
      cout<<respuesta[i][j];
    }
    cout<<endl;
  }

}
void PointingN::get_respuesta(std::vector<string> &v){
	v =respuesta;
}
 	
PointingN::PointingN(){
	this->mat =0;
  	this->mis =0;
  	this->gap =0;
}
PointingN::~PointingN(){
	for (int i = 0; i < point_mat.size(); ++i){
		point_mat[i].clear();
	}
	point_mat.clear();

	for (int i = 0; i < score_mat.size(); ++i){
		score_mat[i].clear();
	}
	score_mat.clear();
}
int PointingN:: res(char c1, char c2){
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
void PointingN::penaltys(int m, int mi, int g){
  mat =m;
  mis =mi;
  gap =g;
}

void PointingN:: ejecutar(std::vector<string> &v1,std::vector<string> &v2){
   m_fila =v1;
   m_col =v2;
   algoritmo1_Pointing();
   algoritmo2_Pointing();

}
void PointingN::insert_data(std::vector<string> &v1,std::vector<string> &v2){
   m_fila =v1;
   m_col =v2;
}
void PointingN:: algoritmo1_Pointing(){
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
  
  // score_mat[CR][0] =distancia_gaps_sup(m_fila,CR,m_col.size());
  
  //  cout<<"\n***********\n";
  for (int i = 0; i < score_mat[0].size(); ++i){
    score_mat[0][i] =distancia_gaps_izq(m_col,i,m_fila.size());
    //cout<<distancia_gaps_izq(m_col,i,m_fila.size())<<"\t";
  }
  //cout<<"\n***********\n";
  
  for (int i = 1; i < this->point_mat[0].size(); ++i){
    this->point_mat[0][i] =3; //movimiento horizontal
  }
  for (int i = 1; i < this->point_mat.size(); ++i){
    this->point_mat[i][0] =1; //movimiento vertical
  }

 
  int diagonal=0;
  int superior=0;
  int izquierdo=0;

  //vector<int> pointers;
  //mostrar();
  CR =1;//fila actual
  for (int i = 1; i < this->point_mat.size(); ++i){
    OR =1-CR;//fila antigua
    score_mat[CR][0] =distancia_gaps_sup(m_fila,i,m_col.size());;
    for (int j = 1; j < this->point_mat[0].size(); ++j){
      diagonal =distancia_nucleotidos(m_col,m_fila,i,j);
      superior =distancia_gaps_sup(m_fila, i, m_col.size());
   	  izquierdo =distancia_gaps_izq(m_col, j, m_fila.size());
      
      CS =diagonal;

      Max =this->score_mat[OR][j-1] + CS;
      pointer = 2;
      
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

        // cout<<"\n***********\n";
        // for (int l = 0; l < 2; ++l){
        //   for (int k = 0; k < score_mat[0].size(); ++k){
        //       cout<<score_mat[l][k]<<"\t";
        //   }
        //   cout<<endl;
        // }
        // cout<<"\n***********\n";

    }
    //cout<<"\n---------------------------------\n";
    CR = OR;
   }


}
void PointingN:: algoritmo2_Pointing(){

  respuesta.resize(m_fila.size() + m_col.size());
  int Row =(this->point_mat.size()-1);//fila 
  int Col =(this->point_mat[0].size()-1);//columna  
  int i=0;
  while(this->point_mat[Row][Col] > 0){//final
      
      if(this->point_mat[Row][Col] == 2){//diagonal
          unir_nucleotidos(m_fila,m_col,Row,Col);
          --Row;
          --Col;
      }
      else if (this->point_mat[Row][Col] == 1){//vertical
          unir_gaps_sup(m_fila, Row,m_col.size());
          --Row;
        

      }
      else if (this->point_mat[Row][Col] == 3){//horizontal
          unir_gaps_izq(m_col,Col,m_fila.size());
          --Col;
      }
  }
/*
  cout<<"\nResultado\n";
  for (int i = 0; i < respuesta.size(); ++i){
    cout<<respuesta[i]<<endl;
  }*/

}

int PointingN:: distancia_gaps_izq(vector<string> &v, int pos, int gaps_t ){
  int tmp=0;
  for (int i = 0; i < v.size(); ++i){
    for (int j = 0; j < gaps_t; ++j){
      if(v[i][pos]!='-')
        tmp +=gap;
     
    }
  }
  return tmp;
}
int PointingN:: distancia_gaps_sup(vector<string> &v, int pos, int gaps_t ){
  int tmp=0;
  for (int i = 0; i < gaps_t; ++i){
    for (int j = 0; j < v.size(); ++j){
      if(v[j][pos] != '-')
        tmp +=gap;
     
    }
  }
  return tmp;
}

int PointingN:: distancia_nucleotidos(vector<string>&data_f, vector<string>&data_c,int position_i,int position_j){
  int tmp=0;
  for (int i = 0; i < data_c.size(); ++i){
    for (int j = 0; j < data_f.size() ; ++j){
      //cout<<"("<<data_c[i][position_j]<<" , "<<data_f[j][position_i]<<")\t";
      tmp += res(data_c[i][position_i],data_f[j][position_j]);
    }
  }
  return tmp;
}

  
void PointingN::unir_gaps_izq(vector<string> &v, int pos, int gaps_t ){
  int ubica=0;
  for (int i = 0; i < v.size(); ++i){
    respuesta[ubica] =v[i][pos] + respuesta[ubica];
    ubica++;
  }
  for (int i = 0; i <gaps_t ; ++i){
    respuesta[ubica] ="-" + respuesta[ubica];
    ubica++;
  }
}

void PointingN::unir_gaps_sup(vector<string> &v, int pos, int gaps_t ){
  int ubica=0;
  for (int i = 0; i < gaps_t; ++i){
    respuesta[ubica] ="-" + respuesta[ubica];
    ubica++;
  }
  for (int i = 0; i < v.size(); ++i){
    respuesta[ubica] =v[i][pos] + respuesta[ubica];
    ubica++;
  }
}

void PointingN:: unir_nucleotidos(vector<string> &v1,vector<string> &v2, int pos1,int pos2){
  int ubica=0;
  for (int i = 0; i < v2.size(); ++i){
    respuesta[ubica] =v2[i][pos2] + respuesta[ubica];
    ubica++;
  }
  for (int i = 0; i <v1.size() ; ++i){
    respuesta[ubica] =v1[i][pos1] + respuesta[ubica];
    ubica++;
  }
}



void PointingN:: add_gap_inicio(vector<string> &v){
  for (int i = 0; i < v.size(); ++i){
    v[i] ="-"+v[i];
  }
}

#endif // PointingN_H
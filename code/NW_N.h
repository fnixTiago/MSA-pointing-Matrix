#ifndef NW_N_H
#define NW_N_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class NW_N{
public:
	int mat;
	int mis;
	int gap;
	std::vector<std::vector<int> > M;
	std::vector<string> m_fila;
	std::vector<string> m_col;
	std::vector<string> respuesta;
public:
	NW_N();
	~NW_N(); 
	void penaltys(int m, int mi, int g);

	void ejecutar(std::vector<string> &v1,std::vector<string> &v2);
  	void insert_data(std::vector<string> &v1,std::vector<string> &v2);
	void algoritmo1_NW_N();
	void algoritmo2_NW_N();
	
	int distancia_gaps_izq(vector<string> &v, int pos, int gaps_t );
	int distancia_gaps_sup(vector<string> &v, int pos, int gaps_t );
	int distancia_nucleotidos(vector<string>&data_f, vector<string>&data_c,int position_i,int position_j);
	  
	void unir_gaps_izq(vector<string> &v, int pos, int gaps_t );
	void unir_gaps_sup(vector<string> &v, int pos, int gaps_t );
	void unir_nucleotidos(vector<string> &v1,vector<string> &v2, int pos1,int pos2);
  	void add_gap_inicio(vector<string> &v);
	int res(char c1, char c2);
	int aptitud();
    void get_respuesta(std::vector<string> &v);
 	void mostrar();
	
};

NW_N::NW_N(){
	mat=0;
	mis=0;
	gap=0;
}
NW_N::~NW_N(){
	for (int i = 0; i < M.size(); ++i){
		M[i].clear();
	}
	M.clear();
	m_fila.clear();
	m_col.clear();
	respuesta.clear();

}

int NW_N::aptitud(){
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


void NW_N::penaltys(int m, int mi, int g){
  mat =m;
  mis =mi;
  gap =g;
}
int NW_N:: res(char c1, char c2){
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

void NW_N::get_respuesta(std::vector<string> &v){
	v =respuesta;
}

void NW_N::mostrar(){
	cout<<"\nMOSTRAR M\n";	
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
	for (int i = 0; i < M.size(); ++i){
		for (int k = 0; k < m_fila.size(); ++k)
		{
			cout<<m_fila[k][i]<<"\t";
		}
		for (int j = 0; j < M[0].size(); ++j){
			cout<<M[i][j]<<"\t";
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

void NW_N:: add_gap_inicio(vector<string> &v){
  for (int i = 0; i < v.size(); ++i){
    v[i] ="-"+v[i];
  }
}


void NW_N:: ejecutar(std::vector<string> &v1,std::vector<string> &v2){
   m_fila =v1;
   m_col =v2;
   algoritmo1_NW_N();
   algoritmo2_NW_N();

}
void NW_N:: insert_data(std::vector<string> &v1,std::vector<string> &v2){
   m_fila =v1;
   m_col =v2;

}

void NW_N::algoritmo1_NW_N(){
	//agregamos los gaps
	add_gap_inicio(m_fila);
	add_gap_inicio(m_col);

  	this->M.resize(m_fila[0].size());//fila
	for (int i = 0; i < this->M.size(); ++i){
	   this->M[i].resize(m_col[0].size());//columna
	}

	for (int i = 0; i < M.size(); ++i){
		M[i][0] =distancia_gaps_sup(m_fila,i,m_col.size());
	}
	for (int j = 0; j <M[0].size() ; ++j){
		M[0][j] =distancia_gaps_izq(m_col,j,m_fila.size());
		
	}
	int diagonal=0;
	int superior=0;
	int izquierdo=0;
	std::vector<int> valores;
	for (int i = 1; i < M.size(); ++i){
		for (int j = 1; j < M[0].size(); ++j){
			diagonal =distancia_nucleotidos(m_col,m_fila,i,j);
		    superior =distancia_gaps_sup(m_fila, i, m_col.size());
		   	izquierdo =distancia_gaps_izq(m_col, j, m_fila.size());
		    
		    valores.push_back(diagonal + M[i-1][j-1]);//diagonal
			valores.push_back(M[i-1][j] + superior);//superior
			valores.push_back(M[i][j-1] + izquierdo);//horizontal
			sort(valores.begin(),valores.end());
			M[i][j] =valores[2];//mayor
			valores.clear();
		}
	}
	//mostrar();

}

void NW_N::algoritmo2_NW_N(){
  	respuesta.resize(m_fila.size() + m_col.size());
	int Row =(this->M.size()-1);//fila 
	int Col =(this->M[0].size()-1);//columna  
	int i=0;
	int diagonal=0;
	int superior=0;
	int izquierdo=0;
	//cout<<"\nHELLOOO\n";
	while(Row > 0 && Col > 0){//final
		diagonal =M[Row-1][Col-1] + distancia_nucleotidos(m_col,m_fila,Row,Col);
		superior =M[Row-1][Col] + distancia_gaps_sup(m_fila, Row, m_col.size());
		izquierdo =M[Row][Col-1] + distancia_gaps_izq(m_col, Col, m_fila.size());
		    
	    if(this->M[Row][Col]==diagonal){//diagonal
	      unir_nucleotidos(m_fila,m_col,Row,Col);
	     // cout<<"diagonal";
	      --Row;
	      --Col;
	    }
	    else if (this->M[Row][Col]==superior){//vertical
	      unir_gaps_sup(m_fila, Row,m_col.size());
	      //cout<<"superior";
	      --Row;
	      

	    }
	    else if (this->M[Row][Col]==izquierdo){//izquierdo
	      unir_gaps_izq(m_col,Col,m_fila.size());
	      //cout<<"izquierdo";
	      --Col;
	    }
	    else break;
	}
	if (Row>0){
		for (int k1 =Row; k1 > 0; --k1){
			unir_gaps_sup(m_fila, k1,m_col.size());
		}
	}
	if(Col>0){
		for (int k1 =Col; k1 > 0; --k1){
			unir_gaps_izq(m_col,k1,m_fila.size());
		}
	}

	/*
	  cout<<"\nResultado\n";
	  for (int i = 0; i < respuesta.size(); ++i){
	    cout<<respuesta[i]<<endl;
	  }*/

}

int NW_N:: distancia_gaps_izq(vector<string> &v, int pos, int gaps_t ){
  int tmp=0;
  for (int i = 0; i < v.size(); ++i){
    for (int j = 0; j < gaps_t; ++j){
      if(v[i][pos]!='-')
        tmp +=gap;
     
    }
  }
  return tmp;
}
int NW_N:: distancia_gaps_sup(vector<string> &v, int pos, int gaps_t ){
  int tmp=0;
  for (int i = 0; i < gaps_t; ++i){
    for (int j = 0; j < v.size(); ++j){
      if(v[j][pos] != '-')
        tmp +=gap;
     
    }
  }
  return tmp;
}

int NW_N:: distancia_nucleotidos(vector<string>&data_f, vector<string>&data_c,int position_i,int position_j){
  int tmp=0;
  for (int i = 0; i < data_c.size(); ++i){
    for (int j = 0; j < data_f.size() ; ++j){
      //cout<<"("<<data_c[i][position_j]<<" , "<<data_f[j][position_i]<<")\t";
      tmp +=res(data_c[i][position_i],data_f[j][position_j]);
    }
  }
  return tmp;
}


void NW_N::unir_gaps_izq(vector<string> &v, int pos, int gaps_t ){
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

void NW_N::unir_gaps_sup(vector<string> &v, int pos, int gaps_t ){
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

void NW_N:: unir_nucleotidos(vector<string> &v1,vector<string> &v2, int pos1,int pos2){
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



#endif // NW_N_H
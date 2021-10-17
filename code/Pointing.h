#ifndef POINTING_H
#define POINTING_H
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

class Pointing
{
public:
	int MR;// =3 ;//match 5
	int MP;// =1;//mismatch -5
	int GP;// =0;//gap -2	
	string s1;
	string s2;
	vector <vector <int> > point_mat;//puntuacion de la matrix de (n+1)x(m+1)
	vector <vector <int> > score_mat;//puntuacion de la matrix de 2x(m+1)
	vector <string > v_result;
	int score;
public:
	Pointing(string s1, string s2,int mat,int mis,int gap);
	void algoritmo1();//llenado de la matriz
	void algoritmo2();
	void get_result(vector <string> &v);
	int get_score();
	void ejecutar(vector <string> &v);
	int pair_wise();
	int res(char c1, char c2){
		if(c2==c1 && c1!='-')
			return MR;
		else if(c2==c1 && c1=='-')
			return 0;
		else{
			if(c1!=c2 && c1!='-' || c2!='-')
				return MP;
			else return GP;
		}
	}
	void mostrar();
	~Pointing(){
		this->MR =0;
		this->MP =0;
		this->GP =0;
		this->s1 ="";
		this->s2 ="";
		this->score =0;
		for (int i = 0; i < this->score_mat.size(); ++i){
			this->score_mat[i].clear();
		}
		this->score_mat.clear();

		for (int i = 0; i < this->point_mat.size(); ++i)
		{
			this->point_mat[i].clear();//columna
		}
		this->point_mat.clear();//fila

		this->v_result.clear();
	}

	
};
void Pointing::mostrar(){
	cout<<"\t";
	for (int i = 0; i < s2.size(); ++i){
		cout<<s2[i]<<"\t";
	}cout<<endl;
	for (int i = 0; i < point_mat.size(); ++i){
		cout<<s1[i]<<"\t";
		for (int j = 0; j < point_mat[0].size(); ++j){
			cout<<point_mat[i][j]<<"\t";
		}
		cout<<endl;
	}
}
int Pointing:: pair_wise(){
	int tmp=0;
	if(v_result[0].size() != v_result[1].size()){
		cout<<"\nERROR pair_wise_Pointing() size diferentes\n";
		return 0;
	}
	
	for (int i = 0; i < v_result[0].size(); ++i){
		if (v_result[0][i]==v_result[1][i] && v_result[0][i]=='-'){
			tmp +=0;
		}
		else if(v_result[0][i]==v_result[1][i]){
			tmp +=MR;
		}
		else{
			if(v_result[0][i]=='-' || v_result[1][i]=='-')
				tmp +=GP;
			else
				tmp +=MP;
		}
	}
	return tmp;
}


Pointing::Pointing(string cad1, string cad2,int mat,int mis,int gap){
	this->MR =mat;
	this->MP =mis;
	this->GP =gap;
	this->s1 ="-" + cad1;
	this->s2 ="-" + cad2;
	this->score =0;
	this->score_mat.resize(2);
	for (int i = 0; i < this->score_mat.size(); ++i){
		this->score_mat[i].resize(s2.size() );
	}

	this->point_mat.resize(s1.size());//fila
	for (int i = 0; i < this->point_mat.size(); ++i)
	{
		this->point_mat[i].resize(s2.size());//columna
	}
/*
	this->v_result.resize(2);
	for (int i = 0; i < this->v_result.size(); ++i){
		this->v_result[i]="";
	}*/
}

void Pointing :: algoritmo1(){

	int OR=0;//fila antigua
	int CR=1;//fila actual 
	int pointer; //direccion del puntero de una celda en this->point_mat
	int Max;
	int CS;//Score value of a Matrix Cell.
	score_mat[CR][0] =GP;
	
	for (int i = 0; i < score_mat[0].size(); ++i){
		score_mat[0][i] =GP*i;
		//score_mat[1][i+1] =3;
	}
	
	for (int i = 1; i < this->point_mat[0].size(); ++i){
		this->point_mat[0][i] =3;	//movimiento horizontal
	}

	for (int i = 1; i < this->point_mat.size(); ++i){
		this->point_mat[i][0] =1;	//movimiento vertical
	}

	CR =1;//fila actual
	for (int i = 1; i < this->point_mat.size(); ++i){
		OR =1-CR;//fila antigua
		score_mat[CR][0] =(i)*GP;
		for (int j = 1; j < this->point_mat[0].size(); ++j){
			
			if (s1[i]==s2[j]&& s1[i] != '-'){
				CS =MR;//match
			}
			else if(s1[i]!=s2[j] && s1[i] != '-' && '-' == s2[j])
			{
				CS =MP;//mismatch
			}
			else{
				CS =GP;//gap
			}

			Max =this->score_mat[OR][j-1] + CS;
			pointer=2;
			//cout<<"(Max,pointer) ("<<Max<<","<<pointer<<endl;
			//cout<<"\tmax: "<<Max<<endl;
			
			if (Max < this->score_mat[OR][j] + GP){//superior
				Max =this->score_mat[OR][j] + GP;
				pointer =1;
			}
			if (Max < this->score_mat[CR][j-1] + GP){//horizontal
				Max =this->score_mat[CR][j-1] + GP;
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
	}
}

void Pointing :: algoritmo2(){
	string s1_AS ="";
	string s2_AS ="";
	int Row =(this->point_mat.size()-1);//fila s2
	int Col =(this->point_mat[0].size()-1);//columna s1 
	int i=0;
	while(this->point_mat[Row][Col]>0){//final
		
		if(this->point_mat[Row][Col]==2){//diagonal
			s1_AS =s1[Row] + s1_AS;
			s2_AS =s2[Col] + s2_AS;
			/// ** *  score
			/*if (s2[Row]==s1[Col]){
				score += 1;
			}
			else
				score += -1;
			*/
			--Row;
			--Col;
		}
		else if (this->point_mat[Row][Col]==1){//vertical
			s1_AS =s1[Row] + s1_AS;
			s2_AS ="-" + s2_AS;
			/// ** *  score
			// score +=-1;
			--Row;
			

		}
		else if (this->point_mat[Row][Col]==3){//horizontal
			s1_AS ="-" + s1_AS;
			s2_AS =s2[Col] + s2_AS;
			/// ** *  score
			// score +=-1;
			--Col;

		}
	}
	this->v_result.push_back(s1_AS);
	this->v_result.push_back(s2_AS);
/*
	for (int i = 0; i < score_mat.size(); ++i){
		cout<<"\t";
		for (int j = 0; j < score_mat[0].size(); ++j){
			cout<<score_mat[i][j]<<"\t";
		}
		cout<<endl;
	}*/
}
void Pointing::get_result(vector <string> &v){
	v.clear();
	v =this->v_result;
}

int Pointing::get_score(){return score;}

void Pointing::ejecutar(vector <string> &v){
	algoritmo1();
	algoritmo2();
	get_result(v);
	
}
/*

int main(int argc, char const *argv[])
{	
	vector <vector <int> > this->point_mat;
	string s1,s2;
	//s1 ="-GTTGC";
	//s2 ="-GTAC";
	//s1 ="-TCGGTAGAA";
	//s2 ="-CGAACGC";
	//s1 ="-TACACGCCTCTTCGCC";
	//s2 ="-CTGTGAGG";
	s1 ="-AAAA";
	s2 ="-CCAAA";
	algoritmo1(s1,s2,this->point_mat);
	vector <string> v;
	algoritmo2(this->point_mat,v, s1,s2);


	cout<<"\nGOOD\n";
	return 0;
}
*/
/*
TCTGC---CT-A--AGATGGCT
-C-GCAGGCTTATCA-A-G-C-

TCGGTA-GAATCCGTC-T
-C-GAACTATTCGGACGC
*/
#endif // POINTING_H

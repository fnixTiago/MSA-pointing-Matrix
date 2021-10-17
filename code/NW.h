#ifndef NW_H
#define NW_H
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;


class NW
{
public:
	int mat;
	int mis;
	int gap;
	int gap_penalty;
	string s1;
	string s2;
	vector<vector<int> > M;// 
	//map<char,map<char, int> > datos;
	vector<string > v_result;
public:
	NW(string s1, string s2,int mat,int mis,int gap);
	void algoritmo1();//llenado de la matriz
	void algoritmo2();
	void get_result(vector<string> &v);
	//void llenar_datos();
	void ejecutar(vector<string> &v);
	int pair_wise();
	int res(char c1, char c2){
		if(c2==c1 && c1!='-')
			return mat;
		else if(c2==c1 && c1=='-')
			return 0;
		else{
			if(c1!=c2 && c1!='-' && c2!='-')
				return mis;
			else return gap;
		}
	}
	void mostrar();

	//void mostrar(){cout<<v_result[0]<endl<<v_result[1]<<endl;}
	~NW(){
		this->s1 = "";
		this->s2 = "-";
		this->mat =0;
		this->mis =0;
		this->gap =0;
		this->gap_penalty = 0;
		for (int i = 0; i < this->M.size(); ++i)
		{
			this->M[i].clear();//columna
		}
		this->M.clear();//fila

		this->v_result.clear();
	}
};

void NW::mostrar(){
	cout<<"\t";
	for (int i = 0; i < s2.size(); ++i){
		cout<<s2[i]<<"\t";
	}cout<<endl;
	for (int i = 0; i < M.size(); ++i){
		cout<<s1[i]<<"\t";
		for (int j = 0; j < M[0].size(); ++j){
			cout<<M[i][j]<<"\t";
		}
		cout<<endl;
	}
}
int NW:: pair_wise(){
	int tmp=0;
	if(v_result[0].size() != v_result[1].size()){
		cout<<"\nERROR pair_wise_NW() size diferentes\n";
		return 0;
	}
	
	for (int i = 0; i < v_result[0].size(); ++i){
		if (v_result[0][i]==v_result[1][i] && v_result[0][i]=='-'){
			tmp +=0;
		}
		else if(v_result[0][i]==v_result[1][i]){
			tmp +=mat;
		}
		else{
			if(v_result[0][i]=='-' || v_result[1][i]=='-')
				tmp +=gap;
			else
				tmp +=mis;
		}
	}
	return tmp;
}

NW::NW(string cad1, string cad2,int ma,int mi,int g){
	this->s1 = "-" + cad1;
	this->s2 = "-" + cad2;
	this->mat =ma;
	this->mis =mi;
	this->gap =g;
	this->gap_penalty = g;
	//this->score_mat.resize(2);

	this->M.resize(s1.size());//fila
	for (int i = 0; i < this->M.size(); ++i)
	{
		this->M[i].resize(s2.size());//columna
	}

}
/*
void NW::llenar_datos(){
	datos['A']['A'] =10;	datos['A']['G'] =-1;	datos['A']['C'] =-3;	datos['A']['T'] =-4;
	datos['G']['A'] =-1;	datos['G']['G'] = 7;	datos['G']['C'] =-5;	datos['G']['T'] =-3;
	datos['C']['A'] =-3;	datos['C']['G'] =-5;	datos['C']['C'] = 9;	datos['C']['T'] = 0;
	datos['T']['A'] =-4;	datos['T']['G'] =-3;	datos['T']['C'] = 0;	datos['T']['T'] = 8;
}*/
void NW::algoritmo1(){
	//llenar_datos();
	//llenado de vacios fila
	for (int i = 0; i < M.size(); ++i){
		M[i][0] = (gap_penalty)*i;
	}
	//llenamos de vacios las columnas
	for (int i = 0; i < M[0].size(); ++i){
		M[0][i] = (gap_penalty)*i;
	}
	//llenado de la matriz
	std::vector<int> valores;
	int tmp=0;
	for (int i = 1; i < M.size(); ++i){
		for (int j = 1; j <M[0].size() ; ++j){
			tmp =res(s1[i],s2[j]);
			valores.push_back(tmp + M[i-1][j-1]);//diagonal
			valores.push_back(M[i-1][j] + gap_penalty);//superior
			valores.push_back(M[i][j-1] + gap_penalty);//horizontal
			sort(valores.begin(),valores.end());
			M[i][j] =valores[2];//mayor
			valores.clear(); 
		}
	}
	
	// for (int i = 0; i < M.size(); ++i){
	// 	for (int j = 0; j < M[0].size(); ++j){
	// 		cout<<M[i][j]<<"\t";
	// 	}
	// 	cout<<endl;
	// }
}


void NW::algoritmo2(){
	string s1_AS ="";
	string s2_AS ="";
	this->v_result.resize(2);
	for (int i = 0; i < this->v_result.size(); ++i){
		this->v_result[i]="";
	}
	bool diagonal,horizontal,superior;
	int Row =M.size()-1;
	int Col =M[0].size()-1;
	int tmp =0;
	while(Row > 0 && Col > 0){
		//cout<<i<<","<<j<<endl;
		tmp =res(s1[Row],s2[Col]);

		diagonal =M[Row][Col] == (tmp +M[Row-1][Col-1]);
		superior =M[Row][Col] ==(M[Row-1][Col] + gap_penalty);
		horizontal =M[Row][Col] == (M[Row][Col-1] + gap_penalty);
		
		if((diagonal /*!=superior) && (diagonal != horizontal*/)){//diagonal
			s1_AS =s1[Row] + s1_AS;
			s2_AS =s2[Col] + s2_AS;
			Row--;
			Col--;
		}
		else if(superior){//superior
			s1_AS =s1[Row] + s1_AS;
			s2_AS ="-" + s2_AS;
			Row--;
		}
		else if(horizontal){//izquierda
			s1_AS ="-" + s1_AS;
			s2_AS =s2[Col] + s2_AS;
			Col--;
		}
		else break;
	}

	if (Row > 0){
		for (int k1 = Row; k1 > 0; --k1)
		{
			s1_AS =s1[k1] + s1_AS;
			s2_AS ="-" + s2_AS;
		}
	}
	if(Col > 0){
		for (int k1 = Col; k1 > 0; --k1)
		{
			s1_AS ="-" + s1_AS;
			s2_AS =s2[k1] + s2_AS;
		}
	}
	// cout<<"\n **** REsultado  *** \n";
	// cout<<s1_AS<<endl;
	// cout<<s2_AS<<endl;
	v_result[0] =s1_AS;
	v_result[1] =s2_AS;

}
void NW::get_result(vector<string> &v){
	v.clear();
	v =this->v_result;
}

void NW::ejecutar(vector<string> &v){
	algoritmo1();
	algoritmo2();
	get_result(v);
	
}
#endif // NW_H
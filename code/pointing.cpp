#include <iostream>
#include <vector>
using namespace std;

void algoritmo1(string s1, string s2,vector<vector<int> > &point_mat){
	vector<vector<int> > score_mat;//puntuacion de la matrix de 2x(m+1)
	score_mat.resize(2);
	for (int i = 0; i < score_mat.size(); ++i){
		score_mat[i].resize(s1.size() );
	}
	//vector<vector<int> > point_mat;//puntuacion de la matrix de (n+1)x(m+1)
	point_mat.resize(s2.size());//fila
	for (int i = 0; i < point_mat.size(); ++i)
	{
		point_mat[i].resize(s1.size());//columna
	}
	int OR=0;//fila antigua
	int CR=1;//fila actual 
	int pointer; //direccion del puntero de una celda en point_mat
	
	int MR =3 ;//match 3
	int MP =1;//mismatch 1
	int GP =0;//gap 0
	int Max;
	int CS;//Score value of a Matrix Cell.
	for (int i = 0; i < score_mat[0].size(); ++i){
	//	score_mat[0][i] =-i;	
	//	score_mat[1][i] =-1;	
	}
	//score_mat[1][0]=-1;	score_mat[1][1]=1;	score_mat[1][2]=0;	score_mat[1][3]=-1;	score_mat[1][4]=-2;	score_mat[1][5]=-3;			
	for (int i = 1; i < point_mat[0].size(); ++i){
		point_mat[0][i] =3;	
	}
	for (int i = 1; i < point_mat.size(); ++i){
		point_mat[i][0] =1;	
	}

	CR =1;//fila actual
	for (int i = 1; i < point_mat.size(); ++i){
		OR =1-CR;//fila antigua
		for (int j = 1; j < point_mat[0].size(); ++j){
			
			if (s2[i]==s1[j]){
				CS =MR;//match
				//cout<<"\nmatch: "<<CS<<endl;
			}
			else{ 
				CS =MP;//mismatch
				//cout<<"\nmismatch: "<<CS<<endl;
			}

			Max =score_mat[OR][j-1] + CS;
			pointer=2;
			//cout<<"\tmax: "<<Max<<endl;
			if (Max < score_mat[OR][j] + GP){
				Max =score_mat[OR][j] + GP;
				pointer =1;
			}
			if (Max < score_mat[CR][j-1] + GP){
				Max =score_mat[CR][j-1] + GP;
				pointer =3;
			}
			score_mat[CR][j] =Max;//scores
			point_mat[i][j] =pointer;//matriz
		}
		// if (i==1)break;
		CR = OR;
	}
/*	cout<<"\nSOCORE MATRIX\n";
	for (int i = 0; i < score_mat.size(); ++i){
		for (int j = 0; j < score_mat[0].size(); ++j){
			cout<<score_mat[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<"\nMATRIX\n\t";
	for (int i = 0; i < point_mat[0].size(); ++i){
		cout<<s1[i]<<"\t";
	}cout<<endl;
	for (int i = 0; i < point_mat.size(); ++i){
		cout<<s2[i]<<"\t";
		for (int j = 0; j < point_mat[0].size(); ++j){
			cout<<point_mat[i][j]<<"\t";
		}
		cout<<endl;
	}
*/
}

void algoritmo2(vector<vector<int> > &point_mat, vector<string > &v_result,string s1,string s2){
	v_result.resize(2);
	for (int i = 0; i < v_result.size(); ++i){
		v_result[i]="";
	}
	//cout<<"\nERROR1\n";
	string s1_AS ="";
	string s2_AS ="";
	int score =0;
	int Row =(point_mat.size()-1);//fila s2
	int Col =(point_mat[0].size()-1);//columna s1 
	int i=0;
	while(point_mat[Row][Col]>0){//final
		
		if (point_mat[Row][Col]==3){//horizontal
			s1_AS =s1[Col] + s1_AS;
			s2_AS ="-" + s2_AS;

			score +=-1;
			//cout<<"\nHorizontal\n";
			//cout<<"\tS1: "<<s1_AS<<endl;
			//cout<<"\tS2: "<<s2_AS<<endl;
			Col = Col -1;
			Row =Row;

		}
		else if (point_mat[Row][Col]==1){//vertical
			//s2_AS +=s2[Row];
			//s1_AS +="-";
			s1_AS ="-" + s1_AS;
			s2_AS =s2[Row] + s2_AS;

			score +=-1;
			//cout<<"\nVertical\n";
			//cout<<"\tS1: "<<s1_AS<<endl;
			//cout<<"\tS2: "<<s2_AS<<endl;
			Row =Row -1;
			//Col = Col;
			

		}
		else if(point_mat[Row][Col]==2){//diagonal
			s2_AS =s2[Row] + s2_AS;
			s1_AS =s1[Col] + s1_AS;
			//cout<<"\nDiagonal\n";
			//cout<<"\tS1: "<<s1_AS<<endl;
			//cout<<"\tS2: "<<s2_AS<<endl;
			if (s2[Row]==s1[Col]){
				score += 1;
			}
			else
				score += -1;
			Row =Row -1;
			Col = Col -1;
		}
	}
	cout<<"\nResultado de Secuencias: \n";
	cout<<"\tS1: "<<s1_AS<<endl;
	cout<<"\tS2: "<<s2_AS<<endl;
	cout<<"\tScore: "<<score<<endl;
}



int main(int argc, char const *argv[])
{	
	vector<vector<int> > point_mat;
	string s1,s2;
	//s1 ="-GTTGC";
	//s2 ="-GTAC";
	//s1 ="-TCGGTAGAA";
	//s2 ="-CGAACGC";
	//s1 ="-TACACGCCTCTTCGCC";
	//s2 ="-CTGTGAGG";
	s1 ="-CTATAATCAGA";
	s2 ="-CCAACCCTGTGGA";
	algoritmo1(s1,s2,point_mat);
	vector<string> v;
	algoritmo2(point_mat,v, s1,s2);


	cout<<"\nGOOD\n";
	return 0;
}
/*
TCTGC---CT-A--AGATGGCT
-C-GCAGGCTTATCA-A-G-C-

TCGGTA-GAATCCGTC-T
-C-GAACTATTCGGACGC
*/
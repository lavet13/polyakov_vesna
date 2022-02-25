// lb_1_s2_v13.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "conio.h"
#include <iostream>
#include "string"
#include "stdio.h"
#include "ctime"
#include "windows.h"

using namespace std;

#define A -10
#define B 10

template <typename T> class Vector{
private:
	int n;
	T *x;
public:
	Vector(){ n=0; x=NULL;}

	Vector(int n1){ 
		if (n1>0){
			n=n1; x=new T[n];
		}
		else{ n=0; x=NULL;}
	}

	Vector(Vector &obj){ n=obj.n; x=new T[n]; for(int i=0; i<n; i++) x[i]=obj[i]; }

	~Vector(){
		if(n>0) delete []x;
	}

	void SetRand(int m){
		if (n>0) delete []x;
		n=m;
		x=new T[n];
		for(int i=0; i<n; i++) x[i]=(B-A)*(float)rand()/RAND_MAX+A;
	}

	void SetFormula(int m, float a, float b, int I){
		if (n>0) delete []x;
		n=m;
		x=new T[n];
		for(int i=0; i<n; i++) x[i]=a*I*sin( (i+1)+b );
	}

	void SetKlava(int m, int I){
		if (n>0) delete []x;
		n=m;
		x=new T[n];
		T p;
		for(int i=0; i<n; i++) {
			cout<<"M["<<I<<"]["<<i+1<<"]= ";
			cin>>p; x[i]=p;
		}
	}

	void print(){
		if(n>0){
			for(int i=0; i<n; i++) printf("%8.2f ",x[i]);
			printf("\n");
		}
		else cout<<"Vector empty"<<endl;
	}

	int GetN(){return n;}

	T & operator [] (int i) {if((i>=0)&&(i<n)) return x[i]; else {cout<<"Выход за границы массива"; getch(); exit(0);}}

	Vector & operator = (Vector & v){ if(n>0) delete []x; n=v.n; x=new T[n]; for(int i=0; i<n; i++) x[i]=v[i]; return *this; }

	void operator <<(Vector & v){ print();}

};

template <typename T> class Matr{
private:
	int n;
	Vector<T> *x;
public:
	Matr(){n=0; x=NULL;}

	Matr(int n1, int m1){
		if(n1>0){
			n=n1;
			x=new Vector<T>[n];
			if (m1>0){
				for(int i=0; i<n; i++) x[i].SetRand(m1);
			}
		}
		else{n=0; x=NULL;}
	}

	Matr(int n1, int m1, float a, float b){
		if(n1>0){
			n=n1;
			x=new Vector<T>[n];
			if (m1>0){
				for(int i=0; i<n; i++) x[i].SetFormula(m1,a,b,i+1);
			}
		}
		else{n=0; x=NULL;}
	}

	Matr(int n1, int m1, bool f){
		if(n1>0){
			n=n1;
			x=new Vector<T>[n];
			if (m1>0){
				for(int i=0; i<n; i++) x[i].SetKlava(m1,i+1);
			}
		}
		else{n=0; x=NULL;}
	}

	Matr(Matr &obj){ n=obj.n; x=new Vector<T>[n]; for(int i=0; i<n; i++) x[i]=obj[i];}

	~Matr(){
		if (n>0) delete []x;
	}


	void print(){
		if(n>0){
			for(int i=0; i<n; i++) x[i].print();
		}
		else cout<<"Matr empty"<<endl;
	}

	T opredP(){
		T P=1;
		int i, j, f=0;
		for(i=0; i<n; i++){
			for(j=0; j<x[i].GetN(); j++)
				if (x[i][j]<=3 && x[i][j]>=-3 ){
					if(x[i][j]!=0) {P*=x[i][j]; f=1;}
				}
		}
		if (f==0) P=0;
		return P;
	}

	void preobr(){
		int i, j;
		T p;
		for (i=0; i<n; i++){
			if(x[i][0]>0){
				p=x[i][0];
				for(j=0; j<x[i].GetN(); j++) x[i][j]*=p;
			}
		}
	}

	int GetN(){ return n;}

	Vector<T> & operator [] (int i) {if((i>=0)&&(i<n)) return x[i]; else {cout<<"Выход за границы массива"; getch(); exit(0);}}
};

template <typename T> Vector<T> form_vec(Matr<T> &o){
	Vector<T> V(o.GetN());
	int i, j;
	float sr;
	T min; 
	for(i=0; i<o.GetN(); i++){
		min=o[i][0]; sr=o[i][0];
		for(j=1; j<o[i].GetN(); j++){
			sr+=o[i][j];
			if (min>o[i][j]) min=o[i][j];
		}
		sr/=o[i].GetN();
		V[i]=sr-min;
	}
	return V;
}

template <typename T> ostream& operator<<(ostream& out, Vector<T> &obj){
	out<<"\nVector:\n";
	for(int i=0; i<obj.GetN(); i++){out<<obj[i]<<"  ";} out<<endl;
	return out;
}

template <typename T> ostream& operator<<(ostream& out, Matr<T> &obj){
	out<<"\nMatrix:\n";
	for(int i=0; i<obj.GetN(); i++){
		for(int j=0; j<obj[i].GetN(); j++){
			out<<obj[i][j]<<"  ";}
		out<<endl;
	}
	return out;
}



int _tmain(int argc, _TCHAR* argv[])
{
	Matr<float> a(7,5,4.8,-2.7);
	cout<<"Matr A:"<<endl;
	cout<<a;
	cout<<"PA="<<a.opredP()<<endl;
	if (a.opredP()>0){
		a.preobr();
		cout<<a;
	}
	Vector<float> VA=form_vec(a);
	cout<<"Vector A:"<<endl;
	cout<<VA;

	Matr<int> d(5,5);
	cout<<"Matr D:"<<endl;
	cout<<d;
	cout<<"PD="<<d.opredP()<<endl;
	if (d.opredP()>0){
		d.preobr();
		cout<<d;
	}
	Vector<int> VD=form_vec(d);
	cout<<"Vector D:"<<endl;
	cout<<VD;

	Matr<char> e(2,3,true);
	cout<<"Matr E:"<<endl;
	cout<<e;
	cout<<"PE="<<e.opredP()<<endl;
	if (e.opredP()>0){
		e.preobr();
		cout<<e;
	}
	Vector<char> VE=form_vec(e);
	cout<<"Vector E:"<<endl;
	cout<<VE;

	getch();
	return 0;
}


// lb2_s2_v13.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "string"
#include "conio.h"
#include "stdio.h"
#include "ctime"

using namespace std;

class Material{
private:
	string nazv;
	float rash;
	float ost;
public:
	Material(){nazv="Noname"; rash=0; ost=0;}
	
	Material(string p1, float p2, float p3){ nazv=p1; 
		if (p2>0) rash=p2; else rash=0;
		if (p3>0) ost=p3; else ost=0;
	}

	Material(Material &o){ nazv=o.nazv; rash=o.rash; ost=o.ost;}

	~Material(){}

	void SetNazv(string p){ nazv=p;}
	void SetR(float p){ rash=p;}
	void SetO(float p){ ost=p;}
	string GetNazv(){return nazv;}
	float GetR(){return rash;}
	float GetO(){return ost;}

	void print(){cout<<nazv<<"  "<<ost<<"  "<<rash<<endl;}
};

class Elem{
private:
	int kod;
	Material *d;
public:
	Elem(){ kod=0; d=NULL;}

	Elem(int p, Material &o){
		kod=p; d=new Material(o);
	}

	Elem(Elem &o){
		kod=o.kod; //d=new Material(o.d->GetNazv(),o.d->GetR(),o.d->GetO());
		d=new Material(o.getD());
	}

	~Elem(){
		if (d!=NULL) delete d;
	}

	void print(){
		cout<<kod<<"  "; d->print();
	}

	Material & getD(){ return *d;}

	int GetKod(){return kod;}
};

class AssMas{
private:
	int n;
	int Nmax;
	Elem **Me;
public:
	AssMas(){ n=0; Nmax=1024; Me=new Elem*[Nmax];}

	AssMas(AssMas &o){
		n=o.n; Nmax=o.Nmax; Me=new Elem*[Nmax];
		if (n>0){
			for (int i=0; i<n; i++) Me[i]=new Elem(o.GetE(i));
		}
	}

	~AssMas(){
		if (n>0) for(int i=0; i<n; i++) delete Me[i];
		delete []Me;
	}

	Elem & GetE(int nom){ if(nom>=0 && nom<Nmax) return *Me[nom];}

	void print(){
		cout<<n<<"/"<<Nmax<<endl;
		if (n>0) for(int i=0; i<n; i++) Me[i]->print();
	}

	void operator[](Elem kd){
		int p_kod=kd.GetKod();
		if (n>0){
			if (n<Nmax){
				int ind=-1;
				for(int i=0; i<n; i++){
					if(p_kod==Me[i]->GetKod()) { ind=i; break;}
				}
				if (ind==-1){
					int f=0;
					for(int i=n-1; i>=0; i--){
						if(p_kod>Me[i]->GetKod()) {Me[i+1]=Me[i]; Me[i]=NULL; Me[i]=new Elem(kd); f=1; break;}
						else Me[i+1]=Me[i];
					}
					if (f==0) { Me[0]=NULL; Me[0]=new Elem(kd);}
					n++;
				}
				else{
					delete Me[ind]; Me[ind]=new Elem(kd);
				}
			}
			else {cout<<"Overfloat.."; getch();}
		}
		else{Me[n]=new Elem(kd); n++; }
		//return kd;
	}

	void close(){
		if (n>0) for(int i=0; i<n; i++) delete Me[i];
		n=0;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	AssMas a;
	a.print();
	Material x("Stall",2,10); Elem e(234,x);
	a[e];
	x.SetNazv("Ugol"); Elem e1(12,x);
	a[e1];
	a.print();
	x.SetNazv("PC AT"); Elem e2(12,x);
	a[e2];
	a.print();

	a.close();
	a.print();
	getch();
	return 0;
}


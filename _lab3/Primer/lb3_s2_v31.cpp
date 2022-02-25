// lb3_s2_v31.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "string"
#include "conio.h"
#include "stdio.h"
#include "ctime"

using namespace std;

string parseMes(string p){
	return "01";
}

class oplata{
private:
	string per;
	float s1;
	float s2;
	float s3;
	float s4;
	float s5;
	float s6;
	float s7;
public:
	oplata(){per="    "; s1=s2=s3=s4=s5=s6=s7=0;}

	oplata(string p, string perO){
		string t;
		t=p.substr(0,4);
		if (t=="    ") per=perO;
		else per=t;
		
		t=p.substr(5,10);
		s1=atof(t.c_str());

		t=p.substr(5,10);
		s1=atof(t.c_str());
		
		t=p.substr(16,10);
		s2=atof(t.c_str());
		
		t=p.substr(27,10);
		s3=atof(t.c_str());
		
		t=p.substr(38,10);
		s4=atof(t.c_str());
		
		t=p.substr(49,10);
		s5=atof(t.c_str());
		
		t=p.substr(60,10);
		s6=atof(t.c_str());
		
		t=p.substr(71,10);
		s7=atof(t.c_str());

	}

	oplata(oplata &o){
		per=o.per; s1=o.s1; s2=o.s2; s3=o.s3; s4=o.s4; s5=o.s5; s6=o.s6; s7=o.s7; 
	}

	~oplata(){}

	void print(){
		cout<<per<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<" "<<s5<<" "<<s6<<" "<<s7<<endl;
	}

	void SetPer(string p){per=p;}
	void SetS1(float p){s1=p;}
	void SetS2(float p){s2=p;}
	void SetS3(float p){s3=p;}
	void SetS4(float p){s4=p;}
	void SetS5(float p){s5=p;}
	void SetS6(float p){s6=p;}
	void SetS7(float p){s7=p;}

	string GetPer(){return per;}
	float GetS1(){return s1;}
	float GetS2(){return s2;}
	float GetS3(){return s3;}
	float GetS4(){return s4;}
	float GetS5(){return s5;}
	float GetS6(){return s6;}
	float GetS7(){return s7;}

	oplata &getOb(){return *this;}

};

class Rab{
private:
	int tn;
	string FIO;
	int t;
	int Nmax;
	oplata **MO;
public:
	Rab(){tn=0; FIO="Noname"; t=0; Nmax=10; MO=new oplata*[Nmax]; }

	Rab(string p){
		string a;
		a=p.substr(1,6);
		tn=atoi(a.c_str());

		FIO=p.substr(8,20);
		
		t=0; Nmax=10; MO=new oplata*[Nmax];
	}
	
	Rab(Rab &o){
		tn=o.tn; FIO=o.FIO; t=o.t; Nmax=o.Nmax; MO=new oplata*[Nmax]; 
		if (t>0){
			for(int i=0; i<t; i++) MO[i]=new oplata(o.MO[i]->getOb());
		}
	}
	
	~Rab(){
		if(t>0) for(int i=0; i<t; i++) delete MO[i];
		delete []MO;
	}

	bool add(oplata &o){
		bool vz=false;
		if (t<Nmax) { MO[t]=new oplata(o); t++; vz=true; }
		return vz;
	}

	//oplata & getOpl(int ind){ if(ind>=0 && ind<t) return (MO[ind]->getOb()); else {cout<<"Range error"; getch(); exit(0);} }

	void print(){
		cout<< tn <<"  "<<FIO<<"  ";
		if (t>0){
			for(int i=0; i<t; i++){
				if (i>0) cout<<"                            ";
				MO[i]->print();
			}
		}
	}

	Rab &getOb(){return *this;}
};

class Dok{
private:
	string per;
	string Nper;
	int t;
	int Nmax;
	Rab **Mr;
public:
	Dok(){per="    "; Nper="No period"; t=0; Nmax=1000; Mr=new Rab*[Nmax];}

	Dok(string pf){
		t=0; Nmax=1000; Mr=new Rab*[Nmax];
		FILE *f;
		if ((f=fopen(pf.c_str(),"r")) != NULL){
			char p_buf[255], s;
			string tmp, prov;
			int i1, i2, pos, n_pred=-1;
			while (!feof(f)){
				fgets(p_buf,254,f);
				tmp=p_buf;
				if (tmp.length()>35){
					//prov=tmp.substr(30,1);
					if(tmp[30]=='§'){
						tmp=tmp.substr(33);
						pos=tmp.find("Ј®¤ ");
						Nper=tmp.substr(0,pos-1);
						string Nmes, mes;
						Nmes= Nper.substr(0,Nper.length()-5);
						mes=parseMes(Nmes);
						per=mes+Nper.substr(Nper.length()-2);
					}
					else{
						s=p_buf[6];
						if ( (int(s)>=48) && (int(s)<58) ){
							Mr[t]=new Rab(tmp);
							tmp=tmp.substr(29);
							oplata o(tmp,per);
							Mr[t]->add(o);
							n_pred=t;
							t++;
						}
						else{
							s=p_buf[41];
							if(s=='.'&&n_pred>=0){
								tmp=tmp.substr(29);
								oplata o(tmp,per);
								Mr[n_pred]->add(o);
							}
							else{ n_pred=-1;}
						}
					}
				}
			}
		}
		else{per="    "; Nper="noPeriod";}

	}

	Dok(Dok &o){
		per=o.per; Nper=o.Nper; t=o.t; Nmax=o.Nmax; Mr=new Rab*[Nmax];
		if (t>0){
			for(int i=0; i<t; i++) Mr[i]=new Rab(o.Mr[i]->getOb());
		}
	}
	
	~Dok(){
		if(t>0) for (int i=0; i<t; i++) delete Mr[i];
		delete []Mr;
	}

	void print(){
		cout<<Nper<<"  "<<per<<endl;
		if(t>0){
			for(int i=0; i<t; i++) Mr[i]->print();
		}
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"866");
	Dok a("d:\\var31_1.txt");
	a.print();
	getch();

	return 0;
}


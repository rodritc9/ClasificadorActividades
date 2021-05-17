#include "Neurona.h"
#include <cmath>

Neurona::Neurona() {

}

Neurona::Neurona(int size,int o) {
	cluster=0;
	srand(time(NULL)+o);
	double a;
	for (int i=0;i<size;i++){
	a=((rand()%(70)));
	a=a/100;
	a=0;
	w.push_back(a);
	}
	
	for(int i=0;i<7;i++){
		ganancias[i]=0;
	}
}

vector<double> Neurona::getW(){
	return w;
}

void Neurona::setactualizar_w(double alfa, double R,double d,vector<int> x, double ctte){
	double h=((R-d))/R;

	for (size_t t=0;t<w.size();t++){
		w[t]=w[t]+alfa*h*(x[t]-w[t])*ctte;
	}

}

int Neurona::getCluster(){
	return cluster;
}

void Neurona::setactualizar_wLVQ(double alfa, vector<int> x,int ctte){
	for (size_t t=0;t<w.size();t++){
		w[t]=w[t]+alfa*(x[t]-w[t])*ctte;
	}
}

void Neurona::setCluster(){
	int max= ganancias[0];
	int indice=1;
	for(int i=1;i<7;i++){
		if (ganancias[i]>max){
			max=ganancias[i];
			indice=i+1;
		}
	}
	cluster=indice;
}

void Neurona::setGanancia(int c, int cte){

	ganancias[c-1]=ganancias[c-1]+cte;
}


Neurona::~Neurona() {
	
}


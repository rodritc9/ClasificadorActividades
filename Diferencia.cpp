#include "Diferencia.h"

Diferencia::Diferencia(){
	
}

Diferencia::~Diferencia(){
	
}


double Diferencia::calcular_diferencia(vector<double> w, vector<int> entrada, int metodo){
	
	double dif_aux=0;
	
	switch(metodo){
		
	case 1:	//corelacion
		for (size_t k=0;k<w.size();k++){
			dif_aux=dif_aux+w[k]*entrada[k];
		}
		break;
		
	case 2: //dist euclidea
		for (size_t k=0;k<w.size();k++){
			dif_aux=dif_aux+(w[k]-entrada[k])*(w[k]-entrada[k]);
		}
		
		break;
		
	}
	
	return dif_aux/10000;	
}

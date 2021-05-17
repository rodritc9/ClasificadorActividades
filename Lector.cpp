#include "Lector.h"
using namespace std;

Lector::Lector() {

}

Lector::~Lector() {
	
}

void Lector::setnombre_de_archivo(string nombre,int clustering,int dato_inicial){
	nombre_del_texto=nombre;
	cantidad_datos=0;
	leerArchivo(clustering,dato_inicial);
}

void Lector::leerArchivo(int clustering,int dato_inicial){
	
	fstream archivo;
	archivo.open(nombre_del_texto.c_str());
	
	if(archivo.fail()){
		cerr<<"archivo no encontrado"<<endl;
	}
	else{
		string linea;
		string word;
		string dato;
		int aux2;
		vector <int> lecturas;
		int flag1=dato_inicial, flag2=dato_inicial, flag3=dato_inicial, flag4=dato_inicial, flag5=dato_inicial, flag6=dato_inicial, flag7=dato_inicial;
		int aux_cantidad=dato_inicial+1000;
		int flag1_cluster=0, flag2_cluster=0, flag3_cluster=0, flag4_cluster=0, flag5_cluster=0, flag6_cluster=0, flag7_cluster=0;
		while(!archivo.eof()){
			cantidad_datos++;
			getline(archivo,linea);
			stringstream ss;
			ss << linea;
			int indice=0;
			while( getline(ss, word, ',') ){
				if (indice>0){
				stringstream ss1;
				ss1<<word;
				dato=ss1.str();
				aux2 = atoi (dato.c_str());
				lecturas.push_back(aux2);}
				indice++;
			}
			indice=0;
			if(lecturas[3]==1 && flag1<aux_cantidad && cantidad_datos>dato_inicial){
				almacenamiento_por_archivo.push_back(lecturas);
				flag1++;
			}
			else if(lecturas[3]==2 && flag2<aux_cantidad && cantidad_datos>dato_inicial){
				almacenamiento_por_archivo.push_back(lecturas);
				flag2++;
			}
			else if(lecturas[3]==3 && flag3<aux_cantidad  && cantidad_datos>dato_inicial){
				almacenamiento_por_archivo.push_back(lecturas);
				flag3++;
			}
			else if(lecturas[3]==4 && flag4<aux_cantidad && cantidad_datos>dato_inicial){
				almacenamiento_por_archivo.push_back(lecturas);
				flag4++;
			}
			else if(lecturas[3]==5 && flag5<aux_cantidad && cantidad_datos>dato_inicial){
				almacenamiento_por_archivo.push_back(lecturas);
				flag5++;
			}
			else if(lecturas[3]==6 && flag6<aux_cantidad && cantidad_datos>dato_inicial){
				almacenamiento_por_archivo.push_back(lecturas);
				flag6++;
			}
			else if(lecturas[3]==7 && flag7<aux_cantidad && cantidad_datos>dato_inicial){
				almacenamiento_por_archivo.push_back(lecturas);
				flag7++;
			}
			else if(lecturas[3]==1 && flag1>=aux_cantidad && flag1_cluster<clustering){
				cluster.push_back(lecturas);
				flag1_cluster++;
			}
			else if(lecturas[3]==2 && flag2>=aux_cantidad && flag2_cluster<clustering){
				cluster.push_back(lecturas);
				flag2_cluster++;
			}
			else if(lecturas[3]==3 && flag3>=aux_cantidad && flag3_cluster<clustering){
				cluster.push_back(lecturas);
				flag3_cluster++;
			}
			else if(lecturas[3]==4 && flag4>=aux_cantidad && flag4_cluster<clustering){
				cluster.push_back(lecturas);
				flag4_cluster++;
			}
			else if(lecturas[3]==5 && flag5>=aux_cantidad && flag5_cluster<clustering){
				cluster.push_back(lecturas);
				flag5_cluster++;
			}
			else if(lecturas[3]==6 && flag6>=aux_cantidad && flag6_cluster<clustering){
				cluster.push_back(lecturas);
				flag6_cluster++;
			}
			else if(lecturas[3]==7 && flag7>=aux_cantidad && flag7_cluster<clustering){
				cluster.push_back(lecturas);
				flag7_cluster++;
			}
			lecturas.clear();
		}

	}
	archivo.close();
}

vector <vector<int> > Lector::getTodo(){	
	return almacenamiento_por_archivo;
}

void Lector::setlimpiar(){
	
	almacenamiento_por_archivo.clear();
	cluster.clear();
}

vector <vector<int> > Lector::getCluster(){
	return cluster;
}

#include "Neurona.h"
#include "Lector.h"
#include "Diferencia.h"
#include "Mezclar.h"

#include<iomanip>
using namespace std;

#define imapa 20
#define jmapa 20

#define epoc_kohonen 10
#define epoc_LVQ 10

#define porcentaje_entrenamiento 0.1
#define porcentaje_LVQ 0.3
#define porcentaje_test 0.2

#define clustering 8
#define metodo 2

int main (){

double R0=17;
double R=R0;
double Rf=1;
double alfa0=0.2;
double alfa=alfa0;
double alfaf=0.01;
double d=0;
int size=3;
double factor;
vector<int> indices;


vector<vector<Neurona*> > mapa;
vector<Neurona*> auxil;

	for(int i=0;i<imapa;i++){
		for(int j=0;j<jmapa;j++){

			Neurona *neurona;
			neurona= new Neurona(size,j*i);
			auxil.push_back(neurona);
		}
		mapa.push_back(auxil);
		auxil.clear();
	}


	int cant_archivos;
	string nombre_archivo;
	//cout<<"ingrese cantidad de archivo a leer"<<endl;
	cant_archivos=7;
	
	
	Lector *lector;
	lector= new Lector();
	string nombres[7]={"6","3","4","5","7","8","9"};
	
	for(int i=0;i<cant_archivos;i++){

		cout<<"archivo "<<(i+1)<<endl;
		
		nombre_archivo=nombres[i];
		
		
		nombre_archivo=nombre_archivo+".txt";
		lector->setnombre_de_archivo(nombre_archivo,clustering,0);
	}
	
	vector <vector<int> > almacenamiento_por_archivo;
	almacenamiento_por_archivo=lector->getTodo();
	int total_de_datos=almacenamiento_por_archivo.size();
	
	vector <vector<int> > cluster;
	cluster=lector->getCluster();

	
	Mezclar *mezclar;
	mezclar= new Mezclar();
	
	indices=mezclar->mezclar_vector(almacenamiento_por_archivo.size(),1);

	int cantidad_entrenamiento=porcentaje_entrenamiento*total_de_datos;
	int cantidad_validacion=porcentaje_LVQ*total_de_datos;
	int cantidad_test=porcentaje_test*total_de_datos;
	
	vector<vector<int> >entrenamiento;
	vector<vector<int> >LVQ;
	vector<vector<int> >Vtest;

	for (int i=0;i<cantidad_entrenamiento;i++){
		entrenamiento.push_back(almacenamiento_por_archivo[indices[i]]);
	}
	for (int i=cantidad_entrenamiento;i<cantidad_entrenamiento+cantidad_validacion;i++){
		LVQ.push_back(almacenamiento_por_archivo[indices[i]]);
	}
	for (int i=cantidad_entrenamiento+cantidad_validacion;i<total_de_datos;i++){
		Vtest.push_back(almacenamiento_por_archivo[indices[i]]);
	}
	indices.clear();
	
	Diferencia *dif;
	dif= new Diferencia();
	
	vector <int> posicionW;
	posicionW.push_back(1);
	vector <double> w;
	double ctte;
	double diferencia=500000000000;
	double aux=0;

	
	for(int p=0;p<epoc_kohonen;p++){
		
		indices=mezclar->mezclar_vector(entrenamiento.size(),p);
			

		for(int k=0;k<entrenamiento.size();k++){
			
			diferencia=500000000000;
			aux=0;
			
			for(int i=0;i<imapa;i++){
				for(int j=0;j<jmapa;j++){
			
					w=mapa[i][j]->getW();
					aux= dif->calcular_diferencia(w,entrenamiento[indices[k]],metodo);
					if(aux<diferencia){
						diferencia=aux;
						posicionW.clear();
						posicionW.push_back(i);
						posicionW.push_back(j);
					}
				}
			}
			d=0;
			for(int i=0;i<imapa;i++){
				for(int j=0;j<jmapa;j++){
					
					d=sqrt(((posicionW[0]-i)*(posicionW[0]-i))+((posicionW[1]-j)*(posicionW[1]-j)));
					
					if(d<=R){
						if((i<R) || (j<R) || (i>(imapa-R)) || (j>(jmapa-R))){
							ctte=5;
						}
						else ctte=1;	
						mapa[i][j]->setactualizar_w(alfa,R,d,entrenamiento[indices[k]],ctte);
					}
				}
			}
		

		factor=((double)(k+(entrenamiento.size()*p))/(double)(entrenamiento.size()*epoc_kohonen));
		R=R0+((Rf-R0)*factor);
		alfa=alfa0+((alfaf-alfa0)*factor);
		}
		indices.clear();
	}
	
int cte_cluster;
	
	for(int c=0;c<cluster.size();c++){
		diferencia=500000000000;
		aux=0;
		for(int i=0;i<imapa;i++){
			for(int j=0;j<jmapa;j++){
				
				w=mapa[i][j]->getW();
				aux= dif->calcular_diferencia(w,cluster[c],metodo);
				if(aux<diferencia){
					diferencia=aux;
					posicionW.clear();
					posicionW.push_back(i);
					posicionW.push_back(j);
				}
				
			}
		}

		
		
		for(int i=posicionW[0]-1;i<=posicionW[0]+1;i++){
			for(int j=posicionW[1]-1;j<=posicionW[1]+1;j++){
				
				if((i==posicionW[0]) && (j==posicionW[1])){
					cte_cluster=5;
				}
				else cte_cluster=1;
				   
				if((i>=0) && (j>=0) && (i<imapa) && (j<jmapa)){
				   mapa[i][j]->setGanancia(cluster[c][3],cte_cluster);
				}
			}
		}

	}

	for(int i=0;i<imapa;i++){
		for(int j=0;j<jmapa;j++){
			mapa[i][j]->setCluster();
		}				
	}
	
	alfa0=0.1;
	alfa=alfa0;
	alfaf=0.01;
	
	for(int p=0;p<epoc_LVQ;p++){

		indices=mezclar->mezclar_vector(LVQ.size(),p);

		for(int k=0;k<LVQ.size();k++){
			
			diferencia=500000000000;
			aux=0;
			
			for(int i=0;i<imapa;i++){
				for(int j=0;j<jmapa;j++){
					
					w=mapa[i][j]->getW();
					aux= dif->calcular_diferencia(w,LVQ[indices[k]],metodo);
					if(aux<diferencia){
						diferencia=aux;
						posicionW.clear();
						posicionW.push_back(i);
						posicionW.push_back(j);
					}
				}
			}

			if(mapa[posicionW[0]][posicionW[1]]->getCluster()==LVQ[indices[k]][3])
			   ctte=1;
			else ctte=-1;
			
			mapa[posicionW[0]][posicionW[1]]->setactualizar_wLVQ(alfa,LVQ[indices[k]],ctte);
			
			factor=((double)(k+(LVQ.size()*p))/((double)(LVQ.size()*epoc_LVQ)));
			alfa=alfa0+((alfaf-alfa0)*factor);

		}
		
		indices.clear();
	}
	
	for (int i=0;i<imapa;i++)
	{
		for(int j=0;j<jmapa;j++){
			cout<<setw(5)<<mapa[i][j]->getCluster();
		}
		cout<<endl;
	}
	int aciertos=0;
	double rendimiento=0;
	
	for(int k=0;k<Vtest.size();k++){
		
		diferencia=500000000000;
		aux=0;
		
		for(int i=0;i<imapa;i++){
			for(int j=0;j<jmapa;j++){
				
				w=mapa[i][j]->getW();
				aux= dif->calcular_diferencia(w,Vtest[k],metodo);
				if(aux<diferencia){
					diferencia=aux;
					posicionW.clear();
					posicionW.push_back(i);
					posicionW.push_back(j);
				}
			}
		}
		
		if(mapa[posicionW[0]][posicionW[1]]->getCluster()==Vtest[k][3]){
			aciertos++;
		}
		
	}
	
	rendimiento=((double)aciertos/(double)Vtest.size());
	rendimiento=rendimiento*100;
	cout<<rendimiento;


	return 0;
}

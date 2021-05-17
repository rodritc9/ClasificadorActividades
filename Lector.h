#ifndef LECTOR_H
#define LECTOR_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

class Lector {
private:
	string nombre_del_texto;
	vector <vector<int> > almacenamiento_por_archivo;
	vector <vector<int> > cluster;
	int cantidad_datos;

public:
	Lector();
	~Lector();
	void setnombre_de_archivo(string,int,int);
	void leerArchivo(int,int);
	vector <vector<int> > getTodo();
	vector <vector<int> > getCluster();
	void setlimpiar();
};

#endif


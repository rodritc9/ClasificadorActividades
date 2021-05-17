#include "Mezclar.h"

Mezclar::Mezclar(){
	
}

Mezclar::~Mezclar(){
	
}

vector<int> Mezclar::mezclar_vector(int dimensionV,int j){
	srand (unsigned ( time(0)+j ) );
	
	vector<int> indices;
	for(int i=0;i<dimensionV;i++){
		indices.push_back(i);
	}
	
	random_shuffle(indices.begin(),indices.end());
	
	return indices;
	
}

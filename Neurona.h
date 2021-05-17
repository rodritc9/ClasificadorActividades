#ifndef NEURONA_H
#define NEURONA_H
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
class Neurona {
private:
	vector <double> w;
	int cluster;
	int ganancias[7];
public:
	Neurona();
	Neurona(int,int);
	vector<double> getW();
	void setactualizar_w(double, double, double, vector<int>, double);
	void setactualizar_wLVQ(double,vector<int>,int);
	int getCluster();
	void setCluster();
	void setGanancia(int,int);
	~Neurona();
};

#endif


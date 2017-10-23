#include "neurone.cpp"
#include <fstream>

int main() {	
	
	ofstream sortie;
	sortie.open("pot.txt");
	
	//we can use 1.01 for Iext and 400.0 for time 
	
	double i, time;
	cout<<"External current Iext : ";
	cin>>i;
	cout<<"Time interval : ";
	cin>>time;
	Neurone n;
	n.update(time, i,sortie);
	
	sortie.close();
}

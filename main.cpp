#include "neurone.h"
#include "reseau.h"
#include <fstream>
using namespace std;

int main() {	
	
	
	ofstream sortie;
	sortie.open("sortie2.txt");

	
	
	Reseau res;
	
	res.update(0, 1000, 0, sortie);
	
	sortie.close();
	
	return 0;
}


#include "reseau.h"

using namespace std;


//_______________________CONSTRUCTOR/DESTRUCTOR_______________________//


Reseau::Reseau() {
	
	initialiseRes();
	
	//afficheReseau();													//Uncomment to display which number corresponds to  an excitatory or inhibitory neuron
	
	initialiseLinks();
	
	establishLinks();
	
	cout<<"Construction réseau terminée"<<endl;
	
	//afficheLinks();													//Uncomment to display the table of links, the line n respresents the neuron n, and every case of the line corrseponds to the number of a neuron connected to the n-th neuron
	
}

Reseau::~Reseau() {														//Prevent datas from being destroyed by desallocating memory space used by the neurons pointers and by destroying links between the pointer and the associated variable
	
	reset();
	
}


//__________________________OTHER FUNCTIONS___________________________//


void Reseau::update(int step, int tot, double i) {
	
	bool spike(false);													//No spikes by default
	int startStep(step);												//Memories the initial step to calculate the difference of steps (used to calculate the average of spikes per step)
	
	unsigned int simulationSpikSum(0);									//Sums the total of simulation spikes
	
	while(step < tot) {													//Loop that increments the steps
		
		unsigned int spikSum(0);										//Sums the spikes related to the actual step
	
		for(int m(0); m < links.size(); ++m) {							//Crosses the whole of the neurons and updates the state of each of them
			
			assert(res[m] != nullptr);
			spike = res[m]->update(step, i);
			
			if(spike) {													//Tests if a spike occured and in case it did, crosses the neurons connected to the spiking neuron and sends a signal to each of them
				double courant(0.0);

				assert((res[m]->getMode() == EX) or (res[m]->getMode() == IN));
				
				if(res[m]->getMode() == EX) {						//The current of the sent signal depends on the type of the neuron
					courant = J_EX;									//If excitatory neuron, the constant related to excitatory current J_EX is sent
				} else {
					courant = J_IN;									//Else, inhibitory current is sent
				}
				++spikSum;
				
				for(int n(0); n < links[0].size(); ++n) {
					res[(links[n][m])]->receive(courant);
				}	
			}
		}
		simulationSpikSum += spikSum;
		step += H;														//Increments the steps
	}
	//cout<<endl<<endl<<"Total number of spikes for "<<Nbneurones<<"with "<<tot-startStep<<" steps : "<<simulationSpikSum<<endl;
}

void Reseau::update(int step, int tot, double i, std::ofstream& sortie) {
	
	bool spike(false);													
	int startStep(step);												
	
	unsigned int simulationSpikSum(0);									
	
	while(step < tot) {													
		
		unsigned int spikSum(0);										
		tab.push_back(0);
		for(int m(0); m < links.size(); ++m) {							
			
			assert(res[m] != nullptr);
			spike = res[m]->update(step, i);
			if(spike) {													
				tab[step]+=1 ;
				//if(step > 500) {
					sortie<<step<<'\t'<<m<<'\n';
				//}
				++spikSum;
				double courant(0.0);

				assert((res[m]->getMode() == EX) or (res[m]->getMode() == IN));
				
				if(res[m]->getMode() == EX) {						
					courant = J_EX;									
				} else {
					courant = J_IN;									
				}
				for(int n(0); n < links[0].size(); ++n) {	
					res[(links[n][m])]->receive(courant);
				}	
			}
		}
		
		
		simulationSpikSum += spikSum;
		step += H;														
	}
	//cout<<endl<<endl<<"Total number of spikes for "<<Nbneurones<<"with "<<tot-startStep<<" steps : "<<simulationSpikSum<<endl;
	for (auto j : tab) {
		std::cout << j << std::endl;
	}
}

void Reseau::afficheReseau() const {
	
	cout<<"Affichage du réseau : "<<endl<<endl;							//Displays the number of the line related to a neuron in the table and either EX if it's an excitatory, either IN if it's an inhibitory neuron
	for(int i(1); i <= res.size(); ++i) {
		switch (res[i-1]->getMode()) {
			case EX :
				cout<<i<<".	EX"<<endl;
				break;
			case IN :
				cout<<i<<".	IN"<<endl;
				break;
		}
	}
	
	cout<<endl;
}

void Reseau::afficheLinks() const {
	
	cout<<"Affichage des connexions : "<<endl<<endl;					//Goes all over the table and displays each case
	for(auto line : links) {
		for(auto cell : line) {
			
			cout<<"     "<<cell;
			
		}
		
		cout<<endl;
	}
	
	cout<<endl;
}


//_____________________________GETTERS________________________________//


std::vector<std::array<int, (ExLinks + InLinks)>> Reseau::getLinks() const {
	return links;
}


//_____________________________SETTERS________________________________//


void Reseau::reset() {
	
	for(int i(0); i < res.size(); ++i) {								//Goes all over the neuron pointers table and releases each memory space occupied by a neuron and put the related pointer to nullptr 
		delete res[i];
		res[i] = nullptr;
	}
}

void Reseau::initialiseRes() {
	
	for(int i(0); i < res.size(); ++i) {
		
		if(i < nbE)
			res[i] = (new Neurone(EX));									//Put new pointers on excitatory neurons for the first n case of the table, n corresponding to the number of excitatory neurons
		else
			res[i] = (new Neurone(IN));									//Put new pointers on inhibitory neurons till the end of the table
	}
}

void Reseau::initialiseLinks() {
	
	for(int i(0); i < Nbneurones; ++i) {
		
		array<int, (ExLinks + InLinks)> tab;							//An array of array led to a seg fault with above 5000 neurons that's why a vector of array is used
		
		links.push_back(tab);											//A vector of Nbneurones lines is built, that's why an array number-of-connexions-sized is pushed back for each line
	}
}

void Reseau::establishLinks() {
	
	random_device rd;
	mt19937 gen(rd());
	
	uniform_int_distribution<> Ex_distribution (0, nbE-1);				//The first distribution used to fill the first part of the links table,related to excitatory connexions

	uniform_int_distribution<> In_distribution (nbE, Nbneurones-1);		//The second distribution used to fill the second part of the links table,related to inhibitory connexions
	
	for(auto& line : links) {
		
		for(unsigned int m(0); m < ExLinks; ++m) {						//Crosses the excitatory links part of the connexion table
			unsigned int random_neuron(Ex_distribution(gen));			//Randomly chooses a neuron's number between 0 and the last excitatory neuron's number
			line[m] = random_neuron;									//Put this neuron's number in the current loop case, representing a neuron
		}
		
		for(unsigned int n(ExLinks); n < links[0].size(); ++n) {		//Crosses the inhibitory links part of the connexion table (after the excitatory part)
			unsigned int random_neuron(In_distribution(gen));			//Randomly chooses a neuron's number between the first inhibitory neuron's number and the last neuron
			line[n] = random_neuron;									//Put this neuron's number in the current loop case, representing a neuron
		}
		
	}
}





#include <vector>
#include <iostream>
#include <fstream>
#include "neurone.h"
#include "constants.h"
#include <cassert>
#include <random>

#ifndef RESEAU_H
#define RESEAU_H

/*! 
 * @class Reseau
 * @brief Models a group of neurons and the resulting connexions between neurons
*/

class Reseau {
	
	public :
	
//_______________________CONSTRUCTOR/DESTRUCTOR_______________________//	

	/*! 
	* @brief Constructor that initialises the network table and the links table
	*/
	Reseau();
	
	/*! 
	* @brief Destructor that calls reset() function
	*/

	~Reseau();
	
//_____________________________GETTERS________________________________//	

	/*! 
	* @brief Getter for the connexions table
	* @return Links attribute
	*/
	std::vector<std::array<int, (ExLinks + InLinks)>> getLinks() const;
	
//_____________________________SETTERS________________________________//
	
	/*! 
	* @brief Desallocates memory space previously used by all the neurons of the network
	*/
	void reset();
	
	/*! 
	* @brief Initialises the "res" attribute in relation with the number of neurons. The first part of the table corresponds to excitatory neurons and the second part to inhibitory ones.
	*/
	void initialiseRes();
	
	/*! 
	* @brief Builds the connexions table with empty arrays in order to have a table size corresponding to network's number of neurons
	*/
	void initialiseLinks();
	
	/*! 
	* @brief Randomly allocates a neuron to each of the x connexions a neuron has (x established in constants.h)
	*/
	void establishLinks();
	
//__________________________OTHER FUNCTIONS___________________________//

	/*! 
	* @brief Display the network table
	*/
	void afficheReseau() const;
	
	/*! 
	* @brief Display the links table
	*/
	void afficheLinks() const;

	/*! 
	* @brief Updates the network by calling each neuron's update method, and if a neuron produces a spike, calls receive method on every neuron appearing in the connexions of the spiking neuron
	* @param Two int for the start and final numbers of steps, and one double for the current
	*/
	void update(int step, int tot, double i);
	
	/*! 
	* @brief Surcharge of the other update function used if writting in files is wanted
	* @param The same previously explained plus an ofstream to make an inventory of the total number of spikes of the network per step
	*/
	void update(int step, int tot, double i, std::ofstream& sortie);	
	
	private :
	
//____________________________ATTRIBUTES______________________________//
	
	std::array<Neurone*, Nbneurones> res;								///< Table of pointers containing every neuron of the network
	std::vector<std::array<int, (ExLinks + InLinks)>> links;			///< Table representing the links between neurons, a mxn matrix, with m neurons and n, the total of both excitatory and inhibitory connexions. Each case represents a link between one neuron (relative to the line) and the int of the case designates the line number of the connected post-synaptic neuron in the network table
	std::vector<int> tab;
	
};



#endif

#include <vector>
#include <array>
#include <fstream>
#include "constants.h"
#include <iostream>
#include <cmath>
#include <random>

#ifndef NEURONE_H
#define NEURONE_H

enum Mode {EX, IN};														///< Type of the neuron, EX = excitatory, IN = inhibitory

/*!
 * @class Neurone
 * @brief Models a simplified neuron represented by its potential and its type, either excitatory, either inhibitory
*/

class Neurone {
	
	public :
	
//_______________________CONSTRUCTOR/DESTRUCTOR_______________________//

	/*!
	* @brief Constructor
	* @param Enum for the type of the neuron, either excitatory, either inhibitory, and boolean : true will add the background noise element in the calculus of the potential
	*/
	Neurone(Mode m = EX, bool background = true);
	
	/*!
	* @brief Destructor
	*/
	~Neurone();
	
//_____________________________GETTERS________________________________//	
	
	/*!
	* @brief Getter for the membrane potential
	* @return Membrane potential
	*/
	double getV() const;
	
	/*!
	* @brief Getter for the number of spikes
	* @return spik_ attribute
	*/
	unsigned int getSpik() const;
	
	/*!
	* @brief Getter for the whole of spike times
	* @return Table with every time corresponding with a spike, the n-th element of the table returns the time of the n-th spike
	*/
	std::vector<double> getSpikTimes() const;
	
	/*!
	* @brief Tells if the neuron is in refractory state
	* @return True if the neuron is in refractory state
	*/
	bool isRefractory() const;
	
	/*!
	* @brief Getter for the buffer attribute
	* @return Array modelling the delay of signal transmission
	*/
	std::array<double, int(DELAY + 1)> getBuffer() const;
	
	/*!
	* @brief Getter for the enum representing the type of the neuron
	* @return EX for excitatory and IN for inhibitory
	*/
	Mode getMode() const;

//_____________________________SETTERS________________________________//

	/*!
	* @brief Setter for the membrane potential, modify the potential attribute with the value given in parameter
	* @param A double used to modify the value of the membrane potential value
	*/
	void setV(double v);
	
	/*!
	* @brief Allows to modify the number of spikes that the neuron has had
	* @param An unsigned int to replace the previous number of spikes
	*/
	void setSpik(unsigned int s);
	
	/*!
	* @brief Add the time of a new spike in the table of spike times
	* @param A double representing the new time to add in the table
	*/
	void addTime(double t);
	
	/*!
	* @brief Allows to modify the refractory state of the neuron
	* @param A boolean that replaces the previous value of the refractory state
	*/
	void setRefractory(bool b);
	
//__________________________OTHER FUNCTIONS___________________________//	

	/*!
	* @brief Modify potential value taking into consideration : type of the post-neuron, time, current, if the neuron is refractory and  background noise (using a specific equation)
	* @param An int representing the current step, and a double that represents the external current, necessary for the potential calculus
	* @return True if a the value of membrane potential goes over threshold potential value (v_th in constants.h)
	*/
	bool update(int t, double i);
	
	/*!
	* @brief Models the reception of a post-synaptic signal, add a current to the last case of the buffer
	* @param A double representing the current transmitted by the post-synaptic neuron (varies if excitatory or inhibitory post-neuron)
	*/
	void receive(double i);
	
	/*!
	* @brief Moves backward each value of the table to the previous case, so as to move values near the first case of the table
	* @return The very first case of the table, that models the final case a post-synaptic signal reaches after a certain delay
	*/
	double updateBuffer();
	
	private :
	
//____________________________ATTRIBUTES______________________________//
	
	double v_;															///< Membrane potential
	unsigned int spik_;													///< Number of times the neuron has had a spike
	std::vector<double> spikTimes;										///< Table with times when spikes occured
	bool refractory;													///< True if the neuron is in refractory state
	std::array<double, (DELAY + 1)> buffer_;							///< Way to model the delay between sending of the signal by post-synaptic neuron and reception of it by the neuron
	Mode mode;															///< Enum whether it is an excitatory or inhibitory neuron
	bool noise;															///< If false, suppresses the background element taken into account in the calculus of the membrane potential
};


#endif

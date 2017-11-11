#include <cmath>

#ifndef CONSTANTS_H
#define CONSTANTS_H


constexpr int H(1);														///< Variable for the size of a step
constexpr double R = 20.0;												///< Resistance
constexpr double C = 1.0;												///< Capacitance
constexpr double tau = R*C;												///< Resistance * Capacitance
constexpr double v_th = 20.0;											///< Threshold potential, once passed, induces a spike
constexpr double refractory_t = 2.0;									///< Time a neuron stays in refractory phase
constexpr double C1(exp(-((H/tau)/10.0)));								///< Constant necessary for the equation of potential calculus
constexpr int DELAY (15);												///< Defines the size of the buffer and determines how much time a signal takes between sending and receiving
constexpr double J_EX(0.1);												///< Positive current sent by an excitatory neuron
constexpr double G(5);													///< Relation between inhibitory and excitatory current
constexpr double J_IN(- G*J_EX);										///< Negative current sent by an inhibitory neuron
constexpr unsigned int nbE(10000);										///< Number of excitatory neurons
constexpr unsigned int nbI(0.25*nbE);									///< Number of inhibitory neurons
constexpr unsigned int Nbneurones(nbE + nbI);							///< Total number of network's neurons, equals to the sum of both excitatory and inhibitory neurons
constexpr unsigned int ExLinks(0.1*nbE);								///< Number of excitatory connexions
constexpr unsigned int InLinks(0.1*nbI);								///< Number of inhibitory connexions
constexpr double NU_THR(v_th/(J_EX*tau));								///< 
constexpr double eta(2.0);												///< 
constexpr double NU_EXT(eta*NU_THR);									///< 
constexpr double POISSON_VARIABLE(NU_EXT/10.0);							///< Variable necessary to generate a poisson distributed value needed in the background noise calculus


#endif

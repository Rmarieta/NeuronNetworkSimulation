# Neuron network simulation

This repository contains the code necessary to simulate un network of 12'500 neurons. It deals with the interactions between those neurons, which continually send electrical signals to each other during the duration of the simulation.
The code is composed of two classes, a <code>main</code> and a file containing the constants.

### Classes

#### Class <code>Neurone</code>

It takes care of modeling a neuron. It is characterised by a value representing the membrane potential and by peaks occurring at specific times (when the potential reaches a threshold value). 
This class enables for monitoring the evolution of a neuron over time, by calculating with a specific equation the value of that membrane potential on each simulation time step.

#### Class <code>Reseau</code>

It takes care of building the network of neurons, which means first initialising the network (as a function of the number of desired neurons and connections, to be modified in the file <code>constants.h</code>), by filling an array of neurons with some excitatory and some inhibitory neurons. It then takes care of allocating all the excitatory and inhibitory connections of the neurons part of the network (in a random manner at the start of the simulation). This array of connections will be used during the simulation when a neuron produces a peak in order to transmit the signal to the appropriate downstream connected neurons.

### Informations to use the program

Commands to run :

```
cmake ..
make
./neuron
```

To run the google tests (make sure you don't run it with more than 4000 neurons for the last test, which is in charge of checking the connection array, to avoid large computing times :

```
cmake ..
make
./neuronunittest
```

To create the <it>Doxygen</it> documentation (make sure you empty the <code>/build</code> before) :

```
cmake ..
make
make document
```

### Build the graphs

To build the 4 graphs, it is required to modify the appropriate parameters, the time steps in the <code>main</code>, and the constants in <code>constants.h</code>. The constants to modify are always <code>G</code> and <code>eta</code> to produce the desired graph :

- Graph A : 6000 steps, G = 3, eta = 2, measure between 5000 and 6000
- Graph B : 12000 steps, G = 6, eta = 4, measure between 10000 and 12000
- Graph C : 12000 steps, G = 5, eta = 2, measure between 10000 and 12000
- Graph D : 12000 steps, G = 4.5, eta = 0.9, measure between 10000 and 12000

Make sure you leave the current to 0.0 in the <code>update</code> of the <code>main</code>. In the <code>update</code> method of <code>reseau.cpp</code>, you can change the number of steps from which to start writing in the <code>ofstream</code>, which is in charge of collecting the numerical data necessary to plot the graphs in <it>Jupyter</it>.



#include "reseau.h"
#include "gtest/include/gtest/gtest.h"
#include <iostream>
#include <cmath>
using namespace std;

/*
 * Test 1 : tests the value of membrane potential after one step, 
 * the false in neuron parameter ensures that no background noise is taken into account
*/
TEST (NeuronTest, membranePotential) 
{
	Neurone n1(EX,false);
	n1.update(0, 1.0);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)),n1.getV());
}

/*
 * Test 2 : tests if spikes happens after the right number of steps for one neuron,
 * and that potential is directly reset the step after a spike
*/
TEST (NeuronTest, nbSpikes)
{
	double I(1.01);
	Neurone n2(EX,false);
	int temp(0);
	for(int a(0); a <= 923; ++a) {
		n2.update(a,I);
		temp = a;
	}
	
	EXPECT_EQ(0,n2.getSpik());
	++temp;
	n2.update(temp,I);
	EXPECT_EQ(1,n2.getSpik());
	EXPECT_EQ(0, n2.getV());
	++temp;
	for(int b(temp); b <= 1849; ++b) {
		n2.update(b,I);
		temp = b;
	}
	EXPECT_EQ(1,n2.getSpik());
	++temp;
	n2.update(temp,I);
	EXPECT_EQ(2,n2.getSpik());
	EXPECT_EQ(0, n2.getV());
}

/*
 * Test 3 : tests if a step related to a spike is correctly stored and if the spike arrives at the right step
*/
TEST (NeuronTest, SpikeTimes)
{
	Neurone n3(EX,false);
	for(int a(0); a <1000; ++a) {
		n3.update(a,1.01);
	}
	int spikeTime((n3.getSpikTimes())[n3.getSpik()]);					//First case of getSpikTimes is a 0 by default, and the n-th case of getSpikTimes returns the time of the n-th spike
	
	EXPECT_EQ(924,spikeTime);
}

/*
 * Test 4 : firstly verifies that a neuron stimulated with a current of 1.0 never reaches the threshold potential value,
 * and secondly verifies that when a neuron isn't stimulated anymore (i.e. current = 0.0), the potential value
 * tends toward 0.0 after a certain amount of steps
*/
TEST (NeuronTest, noSpiking)
{
	Neurone n4(EX,false);
	double I(1.0);
	for(int a(0); a < 100000; ++a) {
		n4.update(a,I);
	}
	EXPECT_EQ(0,n4.getSpik());
	EXPECT_GT(1E-3, fabs(19.999 - n4.getV()));
	
	I = 0.0;
	for(int b(100000); b < 200000; ++b) {
		n4.update(b,I);
	}
	EXPECT_NEAR(0, n4.getV(), 1E-3);
}

/*
 * Test 5 : verifies if the delay system of the buffer applies correctly, by testing
 * if the spike happens after more steps corresponding to the delay. Giving a current
 * of 1.0 to n6 ensures that the spike is not simply a spike "produced" by n6 itself,
 * but is induced by the sent signal of n5
*/
TEST (TwoNeuronTest, NbSpikeOfPostNeuron)
{
	Neurone n5(EX,false), n6(EX,false);
	for(int a(0); a <= 1849 + DELAY; ++a) {
		if(n5.update(a,1.01)) {
			n6.receive(J_EX);
			EXPECT_EQ(0.0, n5.getV());
		}
		n6.update(a,1.0);
	}
	EXPECT_EQ(0, n6.getSpik());
	n6.update((1850 + DELAY),1.0);
	EXPECT_EQ(0.0, n6.getV());
	EXPECT_EQ(1, n6.getSpik());
}

/*
 * Test 6 : make sure not to try this test with too much neurons, as it crosses
 * and compares links table values and this table becomes rapidly too big to 
 * rapidly analyse it (above 2000 neurons it is quite too long). This test verifies
 * if values of the links table are included in the distribution intervals (both
 * excitatory and inhibitory distribution)
*/
TEST (NetworkTest, ConnexionsDistribution)
{
	Reseau res;
	bool excitatoryDistribution(true);
	bool inhibitoryDistribution(true);
	
	for(auto line : res.getLinks()) {
		for(int exc(0); exc < ExLinks; ++exc) {
			if((line[exc] < 0) and (line[exc] >= nbE))
				excitatoryDistribution = false;
		}
		for(int inh(ExLinks); inh < (res.getLinks()[0].size()); ++inh) {
			if((line[inh] < nbE) and (line[inh] > (Nbneurones-1)))
				inhibitoryDistribution = false;
		}
	}
	EXPECT_EQ(true, excitatoryDistribution);
	EXPECT_EQ(true, inhibitoryDistribution);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}

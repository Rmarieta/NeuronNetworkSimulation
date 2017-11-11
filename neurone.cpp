#include "neurone.h"


using namespace std;


//_______________________CONSTRUCTOR/DESTRUCTOR_______________________//


Neurone::Neurone(Mode m, bool background)
	: v_(0), spik_(0), refractory(false), mode(m), noise(background)
{
	spikTimes = { 0.0 };												//Ensure that a 0 is in the table, a precaution for the comparison made in the update function
	
	for(auto& b : buffer_) {											//Initilises every case of the buffer to 0
		b = 0.0;
	}
}

Neurone::~Neurone() { }


//__________________________OTHER FUNCTIONS___________________________//


bool Neurone::update(int t, double i) {
	
	bool isSpiking(false);

	if(getV() >= v_th) {												//If potential goes over the threshold, adds a spike to the total, sets neuron to refractory and the spiking step to the table of spikes
		setSpik(spik_ + 1);
		addTime(t);
		setRefractory(true);
		isSpiking = true;
	}
	if(isRefractory() and ((t - getSpikTimes()[spik_]) < (refractory_t/H))) {
		setV(0.0);														//Ensure to keep a zero potential as long as the neuron is in refractory state		
	}
	else {
		setRefractory(false);
		double temp;
		if(noise) {														//Test if background noise element is wanted
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::poisson_distribution<> poi_dis(POISSON_VARIABLE);
			temp = poi_dis(gen);										//Calcules of the poisson variable using a poisson distribution
		}
		else {
			temp= 0.0;
		}
		setV(C1*getV() + R*(1.0 - C1)*i + updateBuffer() + temp*J_EX);	//Equation of the membrane potential
	}
	
	//cout<<"t = "<<t<<", V = "<<getV()<<endl;							//Uncomment to display in the terminal the values of membrane potential associated to each step
	
	buffer_[0] = 0.0;													//Cleans the buffer
	
	return isSpiking;													//Return true if a spike occured
}


double Neurone::updateBuffer() {

	int temp(getBuffer()[0]);
	for(int i(1); i <= (getBuffer().size()-1); ++i) {					//Moves backward every case of the buffer
	
		buffer_[i-1] = buffer_[i];
		
	}
	
	buffer_[getBuffer().size()-1] = temp;   							//Changes the value of the last case of the buffer using the temporary variable initialised before the loop
	
	if(getBuffer()[0] > 1e-15)
		return getBuffer()[0];
	else
		return 0;														//Always returns the first case of the buffer, that represents the current to be sent after a delay (if not nonexistent)
}


void Neurone::receive(double i) {
	buffer_[getBuffer().size()-1] += i;									//Adds the new current (passed in parameter) in the last case of the buffer
}


//_____________________________GETTERS________________________________//


double Neurone::getV() const {
	return v_;
}

unsigned int Neurone::getSpik() const {
	return spik_;
}

vector<double> Neurone::getSpikTimes() const {
	return spikTimes;
}

bool Neurone::isRefractory() const {
	return refractory;
}

array<double, int(DELAY + 1)> Neurone::getBuffer() const {
	return buffer_;
}

Mode Neurone::getMode() const {
	return mode;
}


//_____________________________SETTERS________________________________//


void Neurone::setV(double v) {
	v_ = v;
}

void Neurone::setSpik(unsigned int s) {
	spik_ = s;
}

void Neurone::addTime(double t) {										//Put at the end of the table the last value of the step at which a spike occured
	spikTimes.push_back(t);
}

void Neurone::setRefractory(bool b) {
	refractory = b;
}





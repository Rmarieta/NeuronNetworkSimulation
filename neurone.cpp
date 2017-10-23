#include "neurone.h"
#include <iostream>
#include <cmath>

using namespace std;


Neurone::Neurone(double v, unsigned int s)
	: v_(v), spik_(s), timer_(0.0), Iext_(0.0)
{
	spikTimes = { 0.0 };
}

double Neurone::getV() const {
	return v_;
}

unsigned int Neurone::getSpik() const {
	return spik_;
}

vector<double> Neurone::getSpikTimes() const {
	return spikTimes;
}

double Neurone::getTimer() const {
	return timer_;
}

double Neurone::getIext() const {
	return Iext_;
}

void Neurone::setV(double v) {
	v_ = v;
}

void Neurone::setSpik(unsigned int s) {
	spik_ = s;
}

void Neurone::addTime(double t) {
	spikTimes.push_back(t);
}

void Neurone::setTimer(double t) {
	timer_ = t;
}

void Neurone::setIext(double i) {
	Iext_ = i;
}

bool Neurone::update(double T, double i, ofstream& sortie) {
	
	setIext(i);
	
	if(T<= 0.0)
		return false;
		
	else {
		
		bool refractory(false);
		double endTime(timer_ + T);
		
		while(timer_ < endTime) {
			
			//cout<<"t = "<<getTimer()<<", V = "<<getV()<<endl; 
			
			if(getV() > v_th) {
				//cout<<"V > V_th"<<endl;
				setSpik(spik_ + 1);
				addTime(getTimer());
				refractory = true;
			}
			//on teste si 1) refractaire et 2) si le temps de refraction est fini
			if(refractory and ((getTimer() - getSpikTimes()[spik_]) < (refractory_t/h_))) {
				//cout<<"Réfractaire"<<endl;
				setV(0.0);
			}
			else {
				//cout<<"Augmentation de V"<<endl;
				double a(exp(-(h_/tau)));
				setV(a*getV() + R*(1.0 - a)*getIext());
			}
			
			setTimer(timer_ + 1.0);
			sortie<<getV()<<endl;
		}
		
		return refractory;
	}
}

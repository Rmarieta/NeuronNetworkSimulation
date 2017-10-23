#include <vector>
#include <fstream>

#ifndef NEURONE_H
#define NEURONE_H


class Neurone {
	
	public :
	
	Neurone(double v = 0.0, unsigned int s = 0);
	double getV() const;
	unsigned int getSpik() const;
	std::vector<double> getSpikTimes() const;
	double getTimer() const;
	double getIext() const;
	void setV(double v);
	void setSpik(unsigned int s);
	void addTime(double t);
	void setTimer(double t);
	void setIext(double i);
	
	bool update(double T, double i, std::ofstream& sortie);
	
	private :
	
	double v_;
	unsigned int spik_;
	std::vector<double> spikTimes;
	double timer_;
	double Iext_;
	
//constantes
	const double R = 20.0;
	const double tau = 20.0;
	const double v_th = 20.0;
	const double refractory_t = 2.0;
	const double h_ = 1;				//pas d'intégration
	
};


#endif

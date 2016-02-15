#include "Util.h"

// initialize the Util instance
Util* Util::s_instance = NULL;

// use gaussian to generate a random number
double Util::gaussianRN(const double Mean, const double SquareMargin)
{
	std::random_device rd;
	std::mt19937 e2(rd());
	// create the normal distribution
	std::normal_distribution<double> dist(Mean, SquareMargin);
	return dist(e2);
}

double Util::logsum(double loga, double logb)
{
	double diff = loga - logb;
	double logaplusb;
	if (diff>23)
		logaplusb = loga;
	else if (diff<-23)
		logaplusb = logb;
	else
		logaplusb = logb + log(exp(diff) + 1);
	return logaplusb;
}

double Util::Xprobability(double S, int m, double Z)
{
	double x;
	if (m == 0)
		x = (Z - 1); //P(x=0)
	else
		x = (Z + 1); //P(x=1)
	static const double inv_sqrt_2pi = 0.3989422804014327;
	double a = x / std::sqrt(S);
	return inv_sqrt_2pi / std::sqrt(S) * std::exp(-0.5f * a * a);
}
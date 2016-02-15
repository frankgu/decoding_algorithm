#include "util.h"

Util::Util(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator  = new std::default_random_engine(seed);
}

// use gaussian to generate a random number
double Util::gaussianRN(const double Mean, const double SquareMargin)
{
    // create the normal distribution
    std::normal_distribution<double> dist(Mean, SquareMargin);
    return dist(*generator);
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
        logaplusb = logb + std::log(std::exp(diff) + 1);
	return logaplusb;
}

double Util::Xprobability(double S, int m, double Z)
{
    // double x;
    double resultX0 = 1 / (std::exp(-(2 * Z) / S) + 1);

    if (m == 1){
        return 1 - resultX0;
    }
    else {
        return resultX0;
    }

    /*
	double x;
	if (m == 0)
		x = (Z - 1); //P(x=0)
	else
		x = (Z + 1); //P(x=1)
    static const double inv_sqrt_2pi = 0.3989422804014327;
    double a = x / std::sqrt(S);
    return inv_sqrt_2pi / std::sqrt(S) * std::exp(-0.5 * a * a);
    */
}

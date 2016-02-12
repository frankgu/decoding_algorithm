#pragma once


#include<ctime>
#include<cmath>
#include <random>

class Util
{
	const double PI = 3.1415926;
	static Util *s_instance;
	Util(){};
public:
	// get the PI value
	double getPI(){ return PI; }

	// generate a random gaussian number
	double gaussianRN(const double Mean, const double SquareMargin);

	// return the bigger value of two values
	double returnBiggerValue(double value1, double value2){
		if (value1 > value2)
			return value1;
		else
			return value2;
	}

	double logsum(double loga, double logb);
	// get the probability when x is equal to 0 or 1
	double Xprobability(double SquareMargin, int m, double observedZ);

	// get the Util single instance
	static Util *instance()
	{
		if (!s_instance)
			s_instance = new Util();
		return s_instance;
	}
};


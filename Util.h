#pragma once

#include <iostream>
#include <ctime>
#include <cmath>
#include <random>
#include <chrono>

class Util
{
private:
    const double PI = 3.1415926;
    std::default_random_engine *generator;

public:
    Util();

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
};


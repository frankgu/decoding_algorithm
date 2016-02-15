#ifndef DECODING_H
#define DECODING_H

#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<QList>

#include "util.h"

class Decoding
{

private:
    Util *util = new Util();

    // private memeber
    double  _S = 1;       // the gaussian variance value
    double  _BER_Sum,
            _BER_Max;

    // the probability for each transmitted bit code for sum product algorithm
    QList< QList< QList<double> > >			_prob_sum;
    // the probability for each transmitted bit code for max product algorithm
    QList< QList< QList<double> > >			_prob_max;


    // private function
    void applySumProduct(QList<QList<double> > prob_sum_proxy, int otherValues[3], int i, int j);
    void applyMaxProduct(QList<QList<double> > prob_max_proxy, int otherValues[3], int i, int j);


public:
    int     _num, // the total number of simulation
            _cycle; // cyc is the cycle time of sum-product alg.

    Decoding();

    void clear();

    // the initial variance value is 1
    void setVariance(double s) {_S = s;}

    // get the max product BER result after run the algorithm
    double getMaxResult() {return _BER_Max;}

    // get the sum product BER result after run the algorithm
    double getSumResult() {return _BER_Sum;}

    // need to initialize the variance value before you run the program
    void run();
};

#endif // DECODING_H

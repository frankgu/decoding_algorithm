#include<iostream>
#include<cstdlib>
#include<iomanip>

#include "Util.h"

// m is equal to 1 or 0, represent the probability x value when x is equal to 0 or 1
// this function will return the message passing by specific function
void applySumProduct(std::vector<std::vector<double>> prob_proxy,
	std::vector<std::vector<std::vector<double>>> &prob,
	int otherValues[3], int i, int j);
void applyMaxProduct(std::vector<std::vector<double>> prob_max_proxy, 
	std::vector<std::vector<std::vector<double>>> &prob,
	int otherValues[3], int i, int j);

void main()
{
	int const		_num = 5000, _cycle = 100; //cyc is the cycle time of sum-product alg.
	int					_sum_errorCount = 0, _max_errorCount = 0;
	int					_start = 1, _s, _again;
	double			_BER = 0.0, _M = 0.0, _S;	// Gaussian noise parameters
	double			_Y[_num][7], _Z[_num][7];		// Z is observed code
	std::vector<std::vector<std::vector<double>>>			_prob;					// the probability for each transmitted bit code
	std::vector<std::vector<std::vector<double>>>			_prob_max;

	std::cout << "***************************************************************" << std::endl;
	std::cout << "***  The origianl codeword (0,0,0,0,0,0,0) is a " << _num << "*7 array ***" << std::endl;
	std::cout << "***************************************************************" << std::endl << std::endl << std::endl;
	while (_start != 0)
	{
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "---  The parameter of Gaussian noise function are: " << std::endl;
		std::cout << "---  <case1:1> <case2:1/2> <case3:1/4> <case4:1/8>" << std::endl;
		std::cout << "---  please choose a parameters from 1 to 4: ";
		std::cin >> _s;

		// set the gaussian variance value
		switch (_s)
		{
		case 1:
			_S = 1.0;
			break;
		case 2:
			_S = 0.5;
			break;
		case 3:
			_S = 0.25;
			break;
		case 4:
			_S = 0.125;
			break;
		default:
			exit(1);
		}

		/*
		*	encoding process, add the gaussian random vaiable
		*/
		for (int i = 0; i < _num; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				// the initial value for all the X is 0, then all the y is 1
				_Y[i][j] = 1;
				// apply the gaussian noise on the Y and, get the observed codeword z
				_Z[i][j] = _Y[i][j] + Util::instance()->gaussianRN(_M, _S);
			}
		}

		/*
		*	decoding process
		*/
		for (int i = 0; i < _num; i++)
		{
			std::vector<std::vector<double>> Num1;
			for (int j = 0; j < 7; j++)
			{
				std::vector<double> temp1;
				for (int m = 0; m < 2; m++)
				{
					// generate the initial probability value of x=1 or x=0 by observing z.
					// when m=0,x=0   or m=1,x=1
					temp1.push_back(Util::instance()->Xprobability(_S, m, _Z[i][j]));
				}

				// sotre the probability data
				Num1.push_back(temp1);
			}
			_prob.push_back(Num1);
		}
		_prob_max = _prob;

		// decoding procedure
		for (int k = 0; k < _cycle; k++)
		{
			for (int i = 0; i < _num; i++)
			{
				std::vector<std::vector<double>> _prob_proxy;
				std::vector<std::vector<double>> _prob_max_proxy;

				_prob_proxy = _prob[i];
				_prob_max_proxy = _prob_max[i];
				// get the probability for different x
				for (int j = 0; j < 7; j++)
				{
					if (j == 0){
						// update the x1 probability , f1
						int otherValues[3] = { 3, 5, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
					}
					else if (j == 1)
					{
						// update the x2 probability, f2
						int otherValues[3] = { 3, 6, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
					}
					else if (j == 2)
					{
						// update the x3 probability, f1
						int otherValues[3] = { 1, 5, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
						// update the x3 probability, f2
						int otherValues2[3] = { 2, 6, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues2, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
					}
					else if (j == 3)
					{
						// update the x4 probability, f3
						int otherValues[3] = { 5, 6, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
					}
					else if (j == 4)
					{
						// update the x5 probability, f3
						int otherValues[3] = { 4, 6, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
						// update the x5 probability, f1
						int otherValues2[3] = { 1, 3, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues2, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
					}
					else if (j == 5)
					{
						// update the x6 probability, f2
						int otherValues[3] = { 2, 3, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
						// update the x6 probability, f3
						int otherValues2[3] = { 4, 5, 7 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues2, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
					}
					else if (j == 6)
					{
						// update the x7 probability, f1
						int otherValues[3] = { 1, 3, 5 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
						// update the x7 probability, f2
						int otherValues2[3] = { 2, 3, 6 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues2, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
						// update the x7 probability, f3
						int otherValues3[3] = { 4, 5, 6 };
						// sum product algorithm
						applySumProduct(_prob_proxy, _prob, otherValues3, i, j);
						// max product algorithm
						applyMaxProduct(_prob_max_proxy, _prob_max, otherValues, i, j);
					}

					// normalize the all the result in the prob
					for (int j = 0; j < 7; j++)
					{
						double sum = _prob[i][j][0] + _prob[i][j][1];
						_prob[i][j][0] = _prob[i][j][0] / sum;
						_prob[i][j][1] = _prob[i][j][1] / sum;
						sum = _prob_max[i][j][0] + _prob_max[i][j][1];
						_prob_max[i][j][0] = _prob_max[i][j][0] / sum;
						_prob_max[i][j][1] = _prob_max[i][j][1] / sum;
					}
				}
			}
		}

		// sum-product error count
		for (int i = 0; i < _num; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (_prob[i][j][0] <= _prob[i][j][1])
				{
					_sum_errorCount++;
				}
				if (_prob_max[i][j][0] <= _prob_max[i][j][1])
				{
					_max_errorCount++;
				}
			}
		}

		// calculate the bit error rate
		_BER = ((_sum_errorCount / (7.0 * _num)) * 100);
		std::cout << "The sum-product bit error rate is: (" << _BER << "%)" << std::endl;
		_BER = ((_max_errorCount / (7.0 * _num)) * 100);
		std::cout << "The max-product bit error rate is: (" << _BER << "%)" << std::endl;

		// reset the counter
		_sum_errorCount = 0;
		_max_errorCount = 0;
		_BER = 0.0;
		_prob.clear();
		_prob_max.clear();
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "Do you want to do again? (0=yes; 1=no): ";
		std::cin >> _again;
		std::cout << "---------------------------------------------------" << std::endl;
		if (_again == 0)
		{
			_start = 1;
		}
		else
		{
			_start = 0;
			std::cout << "program ends" << std::endl;
		}
		std::cout << std::endl << std::endl << std::endl;
	}
	system("pause");

}

void applySumProduct(std::vector<std::vector<double>> prob_proxy, 
	std::vector<std::vector<std::vector<double>>> &prob,
	int originOtherValues[3], int i, int j){

	int otherValues[3] = { originOtherValues[0] - 1, originOtherValues[1] - 1, originOtherValues[2] - 1 };

	// mesage from the the function node
	double x0, x1;
	x1 = 0.5 + 0.5 * (1 - 2 * prob_proxy[otherValues[0]][0]) * (1 - 2 * prob_proxy[otherValues[1]][0])
		* (1 - 2 * prob_proxy[otherValues[2]][0]);
	x0 = 1 - x1;
	// accumulate the message
	prob[i][j][0] = prob[i][j][0] * x0;
	prob[i][j][1] = prob[i][j][1] * x1;
}

void applyMaxProduct(std::vector<std::vector<double>> _prob_max_proxy, std::vector<std::vector<std::vector<double>>> &prob,
	int originOtherValues[3], int i, int j){

	int otherValues[3] = { originOtherValues[0] - 1, originOtherValues[1] - 1, originOtherValues[2] - 1 };

	double x0, x1;
	// calculate the probability when x is equal to 1
	x1 = Util::instance()->returnBiggerValue(
		Util::instance()->returnBiggerValue(
		_prob_max_proxy[otherValues[0]][1] * _prob_max_proxy[otherValues[1]][1] * _prob_max_proxy[otherValues[2]][1],
		_prob_max_proxy[otherValues[0]][1] * _prob_max_proxy[otherValues[1]][0] * _prob_max_proxy[otherValues[2]][0]),
		Util::instance()->returnBiggerValue(
		_prob_max_proxy[otherValues[0]][0] * _prob_max_proxy[otherValues[1]][1] * _prob_max_proxy[otherValues[2]][0],
		_prob_max_proxy[otherValues[0]][0] * _prob_max_proxy[otherValues[1]][0] * _prob_max_proxy[otherValues[2]][1]));

	// calculate the probability when x is equal to 0
	x0 = Util::instance()->returnBiggerValue(
		Util::instance()->returnBiggerValue(
		_prob_max_proxy[otherValues[0]][1] * _prob_max_proxy[otherValues[1]][0] * _prob_max_proxy[otherValues[2]][1],
		_prob_max_proxy[otherValues[0]][1] * _prob_max_proxy[otherValues[1]][1] * _prob_max_proxy[otherValues[2]][0]),
		Util::instance()->returnBiggerValue(
		_prob_max_proxy[otherValues[0]][0] * _prob_max_proxy[otherValues[1]][1] * _prob_max_proxy[otherValues[2]][1],
		_prob_max_proxy[otherValues[0]][0] * _prob_max_proxy[otherValues[1]][0] * _prob_max_proxy[otherValues[2]][0]));

	//accumulate the result
	prob[i][j][0] = prob[i][j][0] * x0;
	prob[i][j][1] = prob[i][j][1] * x1;
}

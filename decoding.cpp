#include "decoding.h"

Decoding::Decoding()
{
}

void Decoding::clear(){
    _prob_sum.clear();
    _prob_max.clear();
}

void Decoding::run(){

    QList<QList<double> >  Z;		// Z is observed code

    /*
     *	encoding process, add the gaussian random vaiable
     */
    for (int i = 0; i < _num; i++)
    {
        QList<double> temp;
        for (int j = 0; j < 7; j++)
        {
            // all the tranmissted code value is 0, which means Y is 1
            // apply the gaussian noise on the Y and, get the observed codeword z
            temp.push_back(1 + util->gaussianRN(0, _S));
        }
        Z.push_back(temp);
    }

    /*
     *	decoding process
     */
    // calcaulate the probability from gaussian function
    for (int i = 0; i < _num; i++)
    {
        QList<QList<double> > Num1;
        for (int j = 0; j < 7; j++)
        {
            QList<double> temp1;
            for (int m = 0; m < 2; m++)
            {
                // generate the initial probability value of x=1 or x=0 by observing z.
                // when m=0,x=0   or m=1,x=1
                temp1.push_back(util->Xprobability(1, m, Z[i][j]));
            }

            // sotre the probability data
            Num1.push_back(temp1);
        }
        _prob_sum.push_back(Num1);
    }
    _prob_max = _prob_sum;

    // release the Z
    Z.clear();

    // decoding procedure
    for (int k = 0; k < _cycle; k++)
    {
        for (int i = 0; i < _num; i++)
        {
            QList<QList<double> >  prob_sum_proxy;
            QList<QList<double> >  prob_max_proxy;

            prob_sum_proxy = _prob_sum[i];
            prob_max_proxy = _prob_max[i];

            // get the probability for different x
            for (int j = 0; j < 7; j++)
            {
                if (j == 0){
                    // update the x1 probability , f1
                    int otherValues[3] = { 3, 5, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                }
                else if (j == 1)
                {
                    // update the x2 probability, f2
                    int otherValues[3] = { 3, 6, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                }
                else if (j == 2)
                {
                    // update the x3 probability, f1
                    int otherValues[3] = { 1, 5, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                    // update the x3 probability, f2
                    int otherValues2[3] = { 2, 6, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues2, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                }
                else if (j == 3)
                {
                    // update the x4 probability, f3
                    int otherValues[3] = { 5, 6, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                }
                else if (j == 4)
                {
                    // update the x5 probability, f3
                    int otherValues[3] = { 4, 6, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                    // update the x5 probability, f1
                    int otherValues2[3] = { 1, 3, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues2, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                }
                else if (j == 5)
                {
                    // update the x6 probability, f2
                    int otherValues[3] = { 2, 3, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                    // update the x6 probability, f3
                    int otherValues2[3] = { 4, 5, 7 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues2, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                }
                else if (j == 6)
                {
                    // update the x7 probability, f1
                    int otherValues[3] = { 1, 3, 5 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                    // update the x7 probability, f2
                    int otherValues2[3] = { 2, 3, 6 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues2, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                    // update the x7 probability, f3
                    int otherValues3[3] = { 4, 5, 6 };
                    // sum product algorithm
                    applySumProduct(prob_sum_proxy, otherValues3, i, j);
                    // max product algorithm
                    applyMaxProduct(prob_max_proxy, otherValues, i, j);
                }
            }

            // normalize the all the result in the prob
            for (int j = 0; j < 7; j++)
            {
                double sum = _prob_sum[i][j][0] + _prob_sum[i][j][1];
                _prob_sum[i][j][0] = _prob_sum[i][j][0] / sum;
                _prob_sum[i][j][1] = _prob_sum[i][j][1] / sum;
                sum = _prob_max[i][j][0] + _prob_max[i][j][1];
                _prob_max[i][j][0] = _prob_max[i][j][0] / sum;
                _prob_max[i][j][1] = _prob_max[i][j][1] / sum;
            }
        }
    }

    // calculate the BER
    int sum_errorCount = 0,
        max_errorCount = 0;

    // sum-product error count
    for (int i = 0; i < _num; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (_prob_sum[i][j][0] <= _prob_sum[i][j][1])
            {
                sum_errorCount++;
            }
            if (_prob_max[i][j][0] <= _prob_max[i][j][1])
            {
                max_errorCount++;
            }
        }
    }

    // set the result
    _BER_Sum = ((sum_errorCount / (7.0 * _num)) * 100);
    _BER_Max = ((max_errorCount / (7.0 * _num)) * 100);

    // clear the memory
    clear();
}

void Decoding::applySumProduct(QList<QList<double> > prob_sum_proxy, int originOtherValues[3], int i, int j){

    int otherValues[3] = { originOtherValues[0] - 1, originOtherValues[1] - 1, originOtherValues[2] - 1 };

    // mesage from the the function node
    double x0, x1;
    x1 = 0.5 + 0.5 * (1 - 2 * prob_sum_proxy[otherValues[0]][0]) * (1 - 2 * prob_sum_proxy[otherValues[1]][0])
            * (1 - 2 * prob_sum_proxy[otherValues[2]][0]);
    x0 = 1 - x1;

    // accumulate the message
    _prob_sum[i][j][0] = _prob_sum[i][j][0] * x0;
    _prob_sum[i][j][1] = _prob_sum[i][j][1] * x1;
}

void Decoding::applyMaxProduct(QList<QList<double> > _prob_max_proxy, int originOtherValues[3], int i, int j){

    int otherValues[3] = { originOtherValues[0] - 1, originOtherValues[1] - 1, originOtherValues[2] - 1 };

    double x0, x1;
    // calculate the probability when x is equal to 1
    x1 = util->returnBiggerValue(
        util->returnBiggerValue(
        _prob_max_proxy[otherValues[0]][1] * _prob_max_proxy[otherValues[1]][1] * _prob_max_proxy[otherValues[2]][1],
        _prob_max_proxy[otherValues[0]][1] * _prob_max_proxy[otherValues[1]][0] * _prob_max_proxy[otherValues[2]][0]),
        util->returnBiggerValue(
        _prob_max_proxy[otherValues[0]][0] * _prob_max_proxy[otherValues[1]][1] * _prob_max_proxy[otherValues[2]][0],
        _prob_max_proxy[otherValues[0]][0] * _prob_max_proxy[otherValues[1]][0] * _prob_max_proxy[otherValues[2]][1]));

    // calculate the probability when x is equal to 0
    x0 = util->returnBiggerValue(
        util->returnBiggerValue(
        _prob_max_proxy[otherValues[0]][1] * _prob_max_proxy[otherValues[1]][0] * _prob_max_proxy[otherValues[2]][1],
        _prob_max_proxy[otherValues[0]][1] * _prob_max_proxy[otherValues[1]][1] * _prob_max_proxy[otherValues[2]][0]),
        util->returnBiggerValue(
        _prob_max_proxy[otherValues[0]][0] * _prob_max_proxy[otherValues[1]][1] * _prob_max_proxy[otherValues[2]][1],
        _prob_max_proxy[otherValues[0]][0] * _prob_max_proxy[otherValues[1]][0] * _prob_max_proxy[otherValues[2]][0]));

    //accumulate the result
    _prob_max[i][j][0] = _prob_max[i][j][0] * x0;
    _prob_max[i][j][1] = _prob_max[i][j][1] * x1;
}

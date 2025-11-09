#include <iostream>
#include <armadillo>
#include <cmath>
#include "../hdr/trunc.h"

Trunc::Trunc(unsigned int N, double Q) : N(N), Q(Q){}

double Trunc::mu(double i)
{
    return (N + 2)*pow(Q, 2.0/3.0) + 0.5 - i*Q;
}

double Trunc::calc_mMax()
{
    if(Q <= 0){
        throw std::invalid_argument("Cannot compute m_max : Q must be stricly superior to 0.");
    }
    m_max = ((N + 2)*pow(Q, 2.0/3.0) - 0.5)/Q;  
    return m_max;
}

double Trunc::calc_nMax(int m)
{
    if(m_max == NULL){
        calc_mMax();
    }

    return (0.5*(m_max - m - 1) + 1);
}

double Trunc::calc_nzMax(int m, int n)
{
    return mu((double)(m + 2*n + 1));
}

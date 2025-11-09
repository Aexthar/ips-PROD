#include <iostream>
#include "../hdr/polynomials.h"

Polynomials::Polynomials(int n) : n(n), m(0) {} 

Polynomials::Polynomials(int n, int m) : n(n), m(m){}

arma::mat Polynomials::calcHermit(arma::vec zeta_vec)
{
    arma::mat hermit(zeta_vec.n_rows, n + 1);
    hermit.col(0).ones();

    if(n > 0)
    {
        hermit.col(1) = 2*zeta_vec;

        for(int i = 2; i <= n; i++)
        {
            hermit.col(i) = 2*zeta_vec % hermit.col(i - 1) - 2*(i - 1)*hermit.col(i-2);
        }
    }
    return hermit;
}

arma::cube Polynomials::calcGeneralizedLaguerre(arma::vec eta_vec)
{
    arma::cube laguerre(eta_vec.n_rows, n + 1, m + 1);

    for(int m_i = 0; m_i <= m; m_i++)
    {
        arma::mat slice(laguerre.n_rows, laguerre.n_cols);
        slice.col(0).ones();

        if(n > 0)
        {
            slice.col(1) = 1 + m_i - eta_vec;

            for(int n_i = 2; n_i <= n; n_i++)
            {
                double temp = (1+(m_i - 1)/(double)n_i);
                slice.col(n_i) = (2 + (m_i - 1 - eta_vec)/n_i) % slice.col(n_i - 1) - temp*slice.col(n_i - 2);
            }
        }
        laguerre.slice(m_i) = slice;    
    }
    return laguerre;
}


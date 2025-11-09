#ifndef POLYNOMIALS_H
#define POLYNOMIALS_H

#include <armadillo>

class Polynomials
{
    private:
        int n;
        int m;
    
    public:
        Polynomials(int n);

        Polynomials(int n, int m);

        arma::mat calcHermit(arma::vec zeta_vec);

        arma::cube calcGeneralizedLaguerre(arma::vec eta_vec);
};

#endif // POLYNOMIALS_H
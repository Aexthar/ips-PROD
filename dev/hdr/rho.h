#ifndef RHO_H
#define RHO_H

#include <armadillo>
#include "trunc.h"

class Rho{

    private:
        Trunc trunc;
        arma::cube rhoIdx;

    public:
        Rho(uint N, double Q);

        arma::mat calcNaive(arma::vec r, arma::vec z);

        arma::mat calcOpti(arma::vec r, arma::vec z);

        arma::mat calcOptiPlus(arma::vec r, arma::vec z);

        arma::mat calcOptiPlusBis(arma::vec r, arma::vec z);
};

#endif // RHO
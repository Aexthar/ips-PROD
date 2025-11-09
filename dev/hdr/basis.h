#ifndef BASIS_H
#define BASIS_H

#include <armadillo>

class Basis
{
    private:
        int m;
        int n;
        int n_z;
        arma::vec z;
        arma::vec r_ortho;
        arma::mat hermit;
        arma::cube laguerre;

    public:
        Basis(int m, int n, int n_z, arma::vec z, arma::vec r_ortho);

        arma::vec calcZ(int j);

        arma::vec calcR(int k, int j);

};

#endif // BASIS_H
#include "../hdr/basis.h"
#include "../hdr/polynomials.h"
#include "../hdr/constants.h"

Basis::Basis(int m, int n, int n_z, arma::vec z, arma::vec r_ortho) : m(m), n(n), n_z(n_z), z(z), r_ortho(r_ortho){
    Polynomials polyH(n_z);
    hermit = polyH.calcHermit(z/b_z);

    Polynomials polyL(n, m);
    laguerre = polyL.calcGeneralizedLaguerre((r_ortho % r_ortho)/(b_ortho*b_ortho));
}

arma::vec Basis::calcZ(int j)
{
    arma::vec hermit_j = hermit.col(j);

    double sqrtFactJ = 1;
    for(int i = 1; i <= j; i++){
        sqrtFactJ = sqrtFactJ*(1/sqrt(i));
    }

    arma::vec res = (1.0/sqrt(b_z))*(1.0/(sqrt(pow(2, j)*sqrt(arma::datum::pi))))*sqrtFactJ*arma::exp(-1*(z % z)/(2*b_z*b_z)) % hermit_j;
    return res;
}

arma::vec Basis::calcR(int k, int j)
{
    arma::vec laguerre_j_k = laguerre.slice(k).col(j);

    double sqrtFactJ = 1;
    double sqrtFactJ_K = 1;
    for(int i = 1; i <= j; i++){
        sqrtFactJ = sqrtFactJ*sqrt(i);
    }
    for(int i = 1; i <= j + k; i++){
        sqrtFactJ_K = sqrtFactJ_K*(1/sqrt(i));
    }
    
    arma::vec res = (1.0/(b_ortho*sqrt(arma::datum::pi)))*sqrtFactJ*sqrtFactJ_K*exp(-1*(r_ortho % r_ortho)/(2*b_ortho*b_ortho)) % pow(r_ortho/b_ortho, k) % laguerre_j_k;
    return res;
}
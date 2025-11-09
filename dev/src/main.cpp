#include <iostream>
#include <armadillo>
#include "../hdr/polynomials.h"
#include "../hdr/trunc.h"
#include "../hdr/basis.h"
#include "../hdr/constants.h"

int main(int argc, char* argv[]){
    
    std::cout << "Hermit for n = 5 :" << std::endl;
    arma::vec zVals = {-3.1, -2.3, -1.0, -0.3, 0.1, 4.3, 9.2, 13.7};
    Polynomials poly(5);
    std::cout << poly.calcHermit(zVals) << std::endl;

    std::cout << "Generalized Laguerre for n = 3, m = 5 :" << std::endl;
    zVals = {0.1, 0.3, 1.2, 1.8, 2.0, 2.5, 7.1, 11.1};
    Polynomials poly2(3, 5);
    arma::cube poly2Cube = poly2.calcGeneralizedLaguerre(zVals);
    for(int i = 0; i < (int)poly2Cube.n_slices; i++){
        std::cout << "[slice " << i << "]" << std::endl << poly2Cube.slice(i) << std::endl;
    }
    
    int N = 14;
    double Q = 1.3;
    Trunc trunc(N,Q);
    std::cout << "mMax for N = 14, Q = 1.3 is : "<< trunc.calc_mMax() << std::endl;
    for(int i = 0; i < 14; i++){
        std::cout << " For m = " << i << ", nMax is : " << trunc.calc_nMax(i) << std::endl;
    }
    
    arma::vec z = {-10.1, -8.4, -1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    arma::vec r = {3.1, 2.3, 1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    b_z = 2.829683956491218;
    b_ortho = 1.935801664793151;

    Basis basis0(8,2,15,z,r);

    std::cout << "m, n = 0, R = " << basis0.calcR(0,0) << std::endl;
    std::cout << "m = 8, n = 2, R = " << basis0.calcR(8,2) << std::endl;
    std::cout << "n_z = 0, Z = " << basis0.calcZ(0) << std::endl;
    std::cout << "n_z = 15, Z = " << basis0.calcZ(15) << std::endl;

    return 0;
}
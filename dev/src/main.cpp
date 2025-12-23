#include <iostream>
#include <armadillo>
#include "../hdr/constants.h"
#include "../hdr/utils.h"
#include "../hdr/rho.h"

int main(int argc, char* argv[])
{
    int N = 14;
    double Q = 1.3;

    std::string exePath = Utils::getWrkDir();

    arma::vec z = {-10.1, -8.4, -1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    arma::vec r = {3.1, 2.3, 1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    b_z = 2.829683956491218;
    b_ortho = 1.935801664793151;
    rho_ab.load(exePath + "../rho.arma", arma::arma_ascii);

    Rho rho(N, Q);

    arma::wall_clock wclock;

    wclock.tic();
    arma::mat res = rho.calcNaive(r, z);
    double length = wclock.toc();
    std::cout << res << std::endl;
    std::cout << "Computing duration : " << length << " [s]." << std::endl;

    wclock.tic();
    arma::mat res2 = rho.calcOpti(r, z);
    length = wclock.toc();
    std::cout << res2 << std::endl;
    std::cout << "Computing duration : " << length << " [s]." << std::endl;

    wclock.tic();
    arma::mat res3 = rho.calcOptiPlus(r, z);
    length = wclock.toc();
    std::cout << res3 << std::endl;
    std::cout << "Computing duration : " << length << " [s]." << std::endl;

    wclock.tic();
    arma::mat res4 = rho.calcOptiPlusBis(r, z);
    length = wclock.toc();
    std::cout << res4 << std::endl;
    std::cout << "Computing duration : " << length << " [s]." << std::endl;

    arma::vec x_3d(xyNbPoints);
    arma::vec y_3d(xyNbPoints);
    arma::vec z_3d(zNbPoints);

    arma::cube res_3d = arma::cube(xyNbPoints, zNbPoints, xyNbPoints, arma::fill::zeros);
    
    for(int i = 0; i < xyNbPoints; i++)
    {
        x_3d(i) = xyVal_min + (xyVal_max - xyVal_min)*i/(xyNbPoints - 1);
        y_3d(i) = xyVal_min + (xyVal_max - xyVal_min)*i/(xyNbPoints - 1);
    }

    for(int i = 0; i < zNbPoints; i++)
    {
        z_3d(i) = zVal_min + (zVal_max - zVal_min)*i/(zNbPoints - 1);
    }

    arma::vec r_3d = arma::vec(xyNbPoints);
    x_3d.transform([] (double val) { return(val*val);});

    for(int i = 0; i < xyNbPoints; i++)
    {
        r_3d = y_3d(i)*y_3d(i) + x_3d;
        r_3d.transform([] (double val) { return(sqrt(val));});

        res_3d.slice(i) = rho.calcOptiPlusBis(r_3d, z_3d);
    }

    std::string input = Utils::cubeToDf3(res_3d);
    std::ofstream out(exePath + "sphere.df3");
    out << input;
    out.close();

    return 0;
}
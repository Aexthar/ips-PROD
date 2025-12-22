#include "../hdr/rho.h"
#include <iostream>
#include "../hdr/basis.h"
#include "../hdr/polynomials.h"

Rho::Rho(uint N, double Q) : trunc(N, Q)
{
    int m_max = trunc.calc_mMax();
    int n_max = trunc.calc_nMax(0);
    int n_z_max = trunc.calc_nzMax(0,0);
    rhoIdx.zeros(m_max, n_max, n_z_max);
    uint i = 0;

    for(int m = 0; m < m_max; m++)
    {
        for(int n = 0; n < trunc.calc_nMax(m); n++)
        {
            for(int n_z = 0; n_z < trunc.calc_nzMax(m,n); n_z++)
            {
                rhoIdx(m, n, n_z) = i;
                i++;
            }
        }
    }
}

arma::mat Rho::calcNaive(arma::vec r, arma::vec z)
{
    arma::mat rho_ab;
    rho_ab.load("/home/aexthar/ips-PROD/dev/src/rho.arma", arma::arma_ascii);
    arma::mat result = arma::zeros(r.n_rows, z.n_rows);

    arma::wall_clock wclock;
    wclock.tic();

    for(int m_a = 0; m_a < trunc.calc_mMax(); m_a++)
    {
        for(int n_a = 0; n_a < trunc.calc_nMax(m_a); n_a++)
        {
            for(int n_z_a = 0; n_z_a < trunc.calc_nzMax(m_a, n_a); n_z_a++)
            {
                for(int m_b = 0; m_b < trunc.calc_mMax(); m_b++)
                {
                    for(int n_b = 0; n_b < trunc.calc_nMax(m_b); n_b++)
                    {
                        for(int n_z_b = 0; n_z_b < trunc.calc_nzMax(m_b, n_b); n_z_b++)
                        {
                            Basis basisFuncA(m_a, n_a, n_z_a, z, r);
                            Basis basisFuncB(m_b, n_b, n_z_b, z, r);

                            arma::vec R_a = basisFuncA.calcR(m_a, n_a);
                            arma::vec Z_a = basisFuncA.calcZ(n_z_a);
                            arma::vec R_b = basisFuncB.calcR(m_b, n_b);
                            arma::vec Z_b = basisFuncB.calcZ(n_z_b);

                            arma::mat psiA = R_a*Z_a.t();
                            arma::mat psiB = R_b*Z_b.t();

                            result += rho_ab(rhoIdx(m_a, n_a, n_z_a), rhoIdx(m_b, n_b, n_z_b))*psiA % psiB;
                        }
                    }
                }
            }
        }
    }
    double length = wclock.toc();
    std::cout << "Computing duration : " << length << " [s]." << std::endl;
    return result;
}

arma::mat Rho::calcOpti(arma::vec r, arma::vec z)
{
    arma::mat rho_ab;
    rho_ab.load("/home/aexthar/ips-PROD/dev/src/rho.arma", arma::arma_ascii);
    arma::mat result = arma::zeros(r.n_rows, z.n_rows);

    arma::wall_clock wclock;
    wclock.tic();

    for(int m_a = 0; m_a < trunc.calc_mMax(); m_a++)
    {
        for(int n_a = 0; n_a < trunc.calc_nMax(m_a); n_a++)
        {
            Basis basisFuncA_R(m_a, n_a, z, r);
            arma::vec R_a = basisFuncA_R.calcR(m_a, n_a);

            for(int n_z_a = 0; n_z_a < trunc.calc_nzMax(m_a, n_a); n_z_a++)
            {
                Basis basisFuncA_Z(n_z_a, z, r);
                arma::vec Z_a = basisFuncA_Z.calcZ(n_z_a);
                arma::mat psiA = R_a*Z_a.t();

                arma::mat tmp = arma::zeros(r.n_rows, z.n_rows);
                for(int n_b = 0; n_b < trunc.calc_nMax(m_a); n_b++)
                {
                    Basis basisFuncB_R(m_a, n_b, z, r);
                    arma::vec R_b = basisFuncB_R.calcR(m_a, n_b);

                    for(int n_z_b = 0; n_z_b < trunc.calc_nzMax(m_a, n_b); n_z_b++)
                    {
                        Basis basisFuncB_Z(n_z_b, z, r);
                        arma::vec Z_b = basisFuncB_Z.calcZ(n_z_b);
                        arma::mat psiB = R_b*Z_b.t();
                        tmp += rho_ab(rhoIdx(m_a, n_a, n_z_a), rhoIdx(m_a, n_b, n_z_b))* psiB;
                    }
                }
                result += psiA % tmp;
            }
        }
    }
    double length = wclock.toc();
    std::cout << "Computing duration : " << length << " [s]." << std::endl;
    return result;
}

arma::mat Rho::calcOptiPlus(arma::vec r, arma::vec z)
{
    arma::mat rho_ab;
    rho_ab.load("/home/aexthar/ips-PROD/dev/src/rho.arma", arma::arma_ascii);
    arma::mat result = arma::zeros(r.n_rows, z.n_rows);

    arma::wall_clock wclock;
    wclock.tic();

    for(int m_a = 0; m_a < trunc.calc_mMax(); m_a++)
    {
        for(int n_a = 0; n_a < trunc.calc_nMax(m_a); n_a++)
        {
            Basis basisFuncA_R(m_a, n_a, z, r);
            arma::vec R_a = basisFuncA_R.calcR(m_a, n_a);

            for(int n_z_a = 0; n_z_a < trunc.calc_nzMax(m_a, n_a); n_z_a++)
            {
                Basis basisFuncA_Z(n_z_a, z, r);
                arma::vec Z_a = basisFuncA_Z.calcZ(n_z_a);
                arma::mat psiA = R_a*Z_a.t();

                arma::mat result_aNotb = arma::zeros(r.n_rows, z.n_rows);
                arma::mat result_aIsb = arma::zeros(r.n_rows, z.n_rows);
                for(int n_b = 0; n_b < trunc.calc_nMax(m_a); n_b++)
                {
                    Basis basisFuncB_R(m_a, n_b, z, r);
                    arma::vec R_b = basisFuncB_R.calcR(m_a, n_b);

                    for(int n_z_b = 0; n_z_b < trunc.calc_nzMax(m_a, n_b); n_z_b++)
                    {
                        if(rhoIdx(m_a, n_a, n_z_a) > rhoIdx(m_a, n_b, n_z_b))
                        {
                            Basis basisFuncB_Z(n_z_b, z, r);
                            arma::vec Z_b = basisFuncB_Z.calcZ(n_z_b);
                            arma::mat psiB = R_b*Z_b.t();

                            result_aNotb += 2*rho_ab(rhoIdx(m_a, n_a, n_z_a), rhoIdx(m_a, n_b, n_z_b))*psiB;
                        }
                        else if(rhoIdx(m_a, n_a, n_z_a) == rhoIdx(m_a, n_b, n_z_b))
                        {
                            Basis basisFuncB_Z(n_z_b, z, r);
                            arma::vec Z_b = basisFuncB_Z.calcZ(n_z_b);
                            arma::mat psiB = R_b*Z_b.t();

                            result_aIsb += rho_ab(rhoIdx(m_a, n_a, n_z_a), rhoIdx(m_a, n_b, n_z_b))* psiB;
                        }
                        
                    }
                }
                result += (result_aIsb + result_aNotb) % psiA;
            }
        }
    }
    double length = wclock.toc();
    std::cout << "Computing duration : " << length << " [s]." << std::endl;
    return result;
}

arma::mat Rho::calcOptiPlusBis(arma::vec r, arma::vec z)
{
    arma::mat rho_ab;
    rho_ab.load("/home/aexthar/ips-PROD/dev/src/rho.arma", arma::arma_ascii);

    arma::mat result = arma::zeros(r.n_rows, z.n_rows);
    arma::mat result_aNotb = arma::zeros(r.n_rows, z.n_rows);
    arma::mat result_aIsb = arma::zeros(r.n_rows, z.n_rows);

    arma::wall_clock wclock;
    wclock.tic();

    for(int m_a = 0; m_a < trunc.calc_mMax(); m_a++)
    {
        for(int n_a = 0; n_a < trunc.calc_nMax(m_a); n_a++)
        {
            Basis basisFuncA_R(m_a, n_a, z, r);
            arma::vec R_a = basisFuncA_R.calcR(m_a, n_a);

            for(int n_z_a = 0; n_z_a < trunc.calc_nzMax(m_a, n_a); n_z_a++)
            {
                Basis basisFuncA_Z(n_z_a, z, r);
                arma::vec Z_a = basisFuncA_Z.calcZ(n_z_a);
                arma::mat psiA = R_a*Z_a.t();

                for(int n_b = 0; n_b < trunc.calc_nMax(m_a); n_b++)
                {
                    Basis basisFuncB_R(m_a, n_b, z, r);
                    arma::vec R_b = basisFuncB_R.calcR(m_a, n_b);

                    for(int n_z_b = 0; n_z_b < trunc.calc_nzMax(m_a, n_b); n_z_b++)
                    {
                        if(rhoIdx(m_a, n_a, n_z_a) > rhoIdx(m_a, n_b, n_z_b))
                        {
                            Basis basisFuncB_Z(n_z_b, z, r);
                            arma::vec Z_b = basisFuncB_Z.calcZ(n_z_b);
                            arma::mat psiB = R_b*Z_b.t();

                            result_aNotb += rho_ab(rhoIdx(m_a, n_a, n_z_a), rhoIdx(m_a, n_b, n_z_b))*psiA % psiB;
                        }
                        else if(rhoIdx(m_a, n_a, n_z_a) == rhoIdx(m_a, n_b, n_z_b))
                        {
                            Basis basisFuncB_Z(n_z_b, z, r);
                            arma::vec Z_b = basisFuncB_Z.calcZ(n_z_b);
                            arma::mat psiB = R_b*Z_b.t();

                            result_aIsb += rho_ab(rhoIdx(m_a, n_a, n_z_a), rhoIdx(m_a, n_b, n_z_b))*psiA % psiB;
                        }
                        
                    }
                }
            }
        }
    }
    result += 2*result_aIsb + result_aNotb; 
    double length = wclock.toc();
    std::cout << "Computing duration : " << length << " [s]." << std::endl;
    return result;
}
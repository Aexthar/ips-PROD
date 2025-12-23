#include <cxxtest/TestSuite.h>
#include <armadillo>
#include "../dev/hdr/polynomials.h"

class TestPolynomial : public CxxTest::TestSuite
{
    public:
        void testHermit( void )
        {
            arma::vec zVals, targetVals;
            arma::mat calcValsMat;
            zVals = {-3.1, -2.3, -1.0, -0.3, 0.1, 4.3, 9.2, 13.7};

            Polynomials poly(5);
            calcValsMat = poly.calcHermit(zVals); //compute Hermit polynomials for n in [|0,5|]

            targetVals = {1.02835360e+03,  2.05825600e+02, -2.00000000e+01,  7.80960000e+00,
                          1.15216000e+01,  4.59456160e+03,  1.10572154e+05,  5.54643458e+05};

            TS_ASSERT_DELTA(arma::norm(calcValsMat.col(4) / targetVals - 1.0), 0.0, 1e-08); //n=4

            targetVals = { -4.76676832e+03, -3.88909760e+02,  8.00000000e+00, -3.17577600e+01,
                           1.18403200e+01,  3.48375818e+04,  1.98557479e+06,  1.50339793e+07};
            
            TS_ASSERT_DELTA(arma::norm(calcValsMat.col(5) / targetVals - 1.0), 0.0, 1e-08); //n=5
        }

        void testLaguerre( void )
        {
            arma::vec zVals, targetVals;
            arma::cube calcValsCub;
            zVals = {0.1, 0.3, 1.2, 1.8, 2.0, 2.5, 7.1, 11.1};

            Polynomials poly(3,5);
            calcValsCub = poly.calcGeneralizedLaguerre(zVals); //compute Hermit polynomials for n x m in [|0,3|] x [|0,5|]

            targetVals = {14.405,  13.245,  8.52 ,  5.82 ,  5.,  3.125,  -2.395,  10.005};

            TS_ASSERT_DELTA(arma::norm(calcValsCub.slice(4).col(2) / targetVals - 1.0), 0.0, 1e-08); //m,n = 2,4

            targetVals = {53.23983333,  47.95550000,  27.87200000,  17.5880,
                          14.66666667,   8.39583333,  -0.81183333,  10.1015};

            TS_ASSERT_DELTA(arma::norm(calcValsCub.slice(5).col(3) / targetVals - 1.0), 0.0, 1e-08); //m,n = 3,5
        }
};
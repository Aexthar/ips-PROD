#include <cxxtest/TestSuite.h>
#include <armadillo>
#include "../dev/hdr/trunc.h"

class TestTrunc : public CxxTest::TestSuite
{
    public:
        void testMMax( void )
        {
            Trunc trunc(14, 1.3);
            TS_ASSERT_EQUALS(trunc.calc_mMax(), 14);
        }

        void testNMax( void )
        {
            Trunc trunc(14, 1.3);
            arma::vec calcNMaxVec(trunc.calc_mMax(), arma::fill::zeros);

            for(int i = 0; i < calcNMaxVec.n_rows; i++)
            {
                calcNMaxVec(i) = trunc.calc_nMax(i);
            }
            arma::ivec nMax = {7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1}; //nMax values for m in [|0, mMax - 1|]
            TS_ASSERT((calcNMaxVec - nMax).is_zero());
        }

        void testNzMax( void )
        {
            Trunc trunc(14, 1.3);
            arma::mat calcNzMaxMat(14, 7, arma::fill::zeros);
            arma::ivec nMax = {7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1};

            for(int i = 0; i < trunc.calc_mMax(); i++)
            {
                for(int j = 0; j < nMax(i); j++)
                {
                    calcNzMaxMat(i,j) = trunc.calc_nzMax(i, j);
                }
            }
            arma::imat n_zMax = {{18, 15, 13, 10, 7, 5, 2}, 
                                 {16, 14, 11,  9, 6, 3, 1}, 
                                 {15, 13, 10,  7, 5, 2, 0}, 
                                 {14, 11,  9,  6, 3, 1, 0}, 
                                 {13, 10,  7,  5, 2, 0, 0}, 
                                 {11,  9,  6,  3, 1, 0, 0}, 
                                 {10,  7,  5,  2, 0, 0, 0}, 
                                 { 9,  6,  3,  1, 0, 0, 0}, 
                                 { 7,  5,  2,  0, 0, 0, 0}, 
                                 { 6,  3,  1,  0, 0, 0, 0}, 
                                 { 5,  2,  0,  0, 0, 0, 0}, 
                                 { 3,  1,  0,  0, 0, 0, 0}, 
                                 { 2,  0,  0,  0, 0, 0, 0}, //n_zMax values for n in [|0, nMax(m) - 1|]
                                 { 1,  0,  0,  0, 0, 0, 0}};//with m in [|0, mMax - 1|]
            // check if matrices are equal
            TS_ASSERT((calcNzMaxMat - n_zMax).is_zero());
        }
};
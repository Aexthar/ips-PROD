#ifndef TRUNC_H
#define TRUNC_H

class Trunc
{
    private:
        unsigned int N;
        double Q;
        int m_max;

    public:
        Trunc(unsigned int N, double Q);

        double mu(double i);

        int calc_mMax();

        int calc_nMax(int m);

        int calc_nzMax(int m, int n);
};

#endif // TRUNC_H
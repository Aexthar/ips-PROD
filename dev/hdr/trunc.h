#ifndef TRUNC_H
#define TRUNC_H

class Trunc
{
    private:
        unsigned int N;
        double Q;
        double m_max;


    public:
        Trunc(unsigned int N, double Q);

        double mu(double i);

        double calc_mMax();

        double calc_nMax(int m);

        double calc_nzMax(int m, int n);
};

#endif // TRUNC_H
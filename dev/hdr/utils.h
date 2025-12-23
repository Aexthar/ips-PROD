#ifndef UTILS_H
#define UTILS_H

#include <armadillo>

class Utils
{   
    public:
        static std::string cubeToDf3(const arma::cube &m);

        static std::string getWrkDir();
};

#endif // UTILS_H
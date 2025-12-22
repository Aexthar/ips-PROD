#ifndef UTILS_H
#define UTILS_H

#include <armadillo>

class Utils
{   
    public:
        static std::string cubeToDf3(const arma::cube &m);
};

#endif // UTILS_H
#include "../hdr/constants.h"
#include <armadillo>

const double h = 6.62607015e-34;

const double hbar = h/(2*arma::datum::pi);

double b_z;

double b_ortho;

const double xyVal_min = -10.0;
 
const double xyVal_max = 10.0;

const double zVal_min = -20.0;

const double zVal_max = 20.0;

const int xyNbPoints = 32;

const  int zNbPoints = 64;
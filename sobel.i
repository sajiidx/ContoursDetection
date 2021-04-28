%module sobel
%{
#include "sobel.h"
%}
%include "std_vector.i"
namespace std {

  /* On a side note, the names VecDouble and VecVecdouble can be changed, but the order of first the inner vector matters! */
  %template(VecDouble) vector<double>;
  %template(VecVecDouble) vector< vector<double> >;
}
%include "sobel.h"
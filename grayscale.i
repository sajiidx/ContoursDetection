%module grayscale
%{
#include "grayscale.h"
%}
%include "std_vector.i"
namespace std {

  /* On a side note, the names VecDouble and VecVecdouble can be changed, but the order of first the inner vector matters! */
  %template(VecDouble) vector<double>;
  %template(VecVecDouble) vector< vector<double> >;
  %template(VecVecVecDouble) vector< vector< vector< double> > >;
}
%include "grayscale.h"
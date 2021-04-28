#ifndef _gaussianBlur
#define _gaussianBlur

#include<vector>

std::vector<std::vector< std::vector<double> > > GaussianBlur(std::vector< std::vector< std::vector<double> > > image, int kernel = 1);

#endif
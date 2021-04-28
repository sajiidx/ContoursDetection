#include<iostream>
#include<omp.h>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
typedef vector<vector<double> > vec2d;
typedef vector<vector<vector<double> > > vec3d;

double** FilterCreation(int radius){
    // intialising standard deviation to 1.0
    double sigma = 1.0;
    double r, s = radius * sigma * sigma;
  
    double sum = 0.0;
    
    double** GKernel;
    int n = 2*radius + 1;
    GKernel = new double*[n];
    for(int i=0;i<n;i++){
        GKernel[i] = new double[n];
    }

  
    // generating 5x5 kernel
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            r = sqrt(x * x + y * y);
            GKernel[x + radius][y + radius] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += GKernel[x + radius][y + radius];
        }
    }
  
    // normalising the Kernel
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            GKernel[i][j] /= sum;

    return (double**) GKernel;
}
vec3d GaussianBlur(vec3d image, int radius = 1){
    int rows = image.size();
    int columns = image[0].size();
    int channels = image[0][0].size();
    vector< vector< vector<double> > >  blurred = image;
    double** GKernel = FilterCreation(radius);
    #pragma omp parallel for
    for(int i=0;i<rows;i++){    //iterating each row

        #pragma omp parallel for
        for(int j=0;j<columns;j++){     //iterating each column

            int channel = 0;
            #pragma omp parallel for reduction(+:channel)
            for(int k = 0;k < channels;k++){     //iterating each channel

                int a = 0;
                for (int x = i-radius; x <= i+radius; x++){
                    int b = 0;
                    for (int y = j-radius; y <= j+radius; y++){
                        if(x>=0 && y>=0 && x<rows && y<columns){
                            channel += image[x][y][k] * GKernel[a][b];
                        }
                        b++;
                    }
                    a++;
                }
                #pragma omp critical
                {
                    blurred[i][j][k] = channel;
                    channel = 0;
                }
            }
        }
    }
    return blurred;
}
extern "C"{
    vec3d ApplyGaussianBlur(vec3d image, int kernel = 1){
        return GaussianBlur(image, kernel);
    }
}
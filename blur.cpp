#include<iostream>
#include<omp.h>
#include<vector>
#include <cmath>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;


double** FilterCreation(){
    
    // intialising standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;
  
    double sum = 0.0;
    double** GKernel;
    int n = 3;
    GKernel = new double*[n];
    for(int i=0;i<n;i++){
        GKernel[i] = new double[n];
    }

  
    // generating 3x3 kernel
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            r = sqrt(x * x + y * y);
            GKernel[x + 1][y + 1] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += GKernel[x + 1][y + 1];
        }
    }
  
    // normalising the Kernel
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            GKernel[i][j] /= sum;

    return (double**) GKernel;
}

vector< vector< vector<double> > > blur(vector<vector<vector<double> > > img){

    time_t start, end;
    
    vector< vector< vector<double> > >  blurred = img;
    int r = img.size();
    int c = img[0].size();
    int ch = img[0][0].size();

    double** GKernal = FilterCreation();
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << GKernal[i][j] << "\t";
        }
        cout << endl;
    }

    time(&start);

    #pragma omp parallel for
    for(int i=0;i < img.size(); i++){
        #pragma omp parallel for
        for(int j=0;j<img[i].size();j++){
            int channel = 0;
            #pragma omp parallel for reduction(+:channel)
            for(int k=0;k<img[i][j].size();k++){
                // upper row
                if(i-1 >= 0 && j-1 >=0){
                    channel += img[i-1][j-1][k] * GKernal[0][0];
                }
                if(i-1 >= 0){
                    channel += img[i-1][j][k] * GKernal[0][1];
                }
                if(i-1 >= 0 && j+1 < c){
                    channel += img[i-1][j+1][k] * GKernal[0][2];
                }

                // middle row
                if(j-1 >= 0){
                    channel += img[i][j-1][k] * GKernal[1][0];
                }
                if(j+1 < c){
                    channel += img[i][j+1][k] * GKernal[1][1];
                }
                channel += img[i][j][k] * GKernal[1][2];

                // lower row
                if(i+1 < r && j-1 >=0){
                    channel += img[i+1][j-1][k] * GKernal[2][0];
                }
                if(i+1 < r){
                    channel += img[i+1][j][k] * GKernal[2][1];
                }
                if(i+1 < r && j+1 < c){
                    channel += img[i+1][j+1][k] * GKernal[2][2];
                }
                #pragma omp critical
                {
                    blurred[i][j][k] = channel;
                    channel = 0;
                }
            }
        }
    }
    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by Gaussian Blur : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;
    
    return blurred;
}
extern "C"{
    vector< vector< vector<double> > >  blur_image(vector< vector< vector<double> > >  image){
        return blur(image);
    }
}
#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include <bits/stdc++.h>
using namespace std;

vector<vector<double> > SobelOperator(vector<vector<double> > img){
    time_t start, end;
    int radius = 1;
    vector<vector<double> > G = img;
    
    int gx_kernel[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} };
    int gy_kernel[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };

    vector<vector<double> > Gx = img;
    vector<vector<double> > Gy = img;
    vector<vector<double> > theta = img;
    time(&start);
    #pragma omp parallel for
    for(int i=0;i<img.size();i++){
        double gx = 0;
        double gy = 0;
        #pragma omp parallel for reduction(+:gx) reduction(+:gy)
        for(int j=0;j<img[i].size();j++){
            
            int a = 0;
            for (int x = i-radius; x <= i+radius; x++){
                int b = 0;
                for (int y = j-radius; y <= j+radius; y++){
                    if(x>=0 && y>=0 && x<img.size() && y<img[i].size()){
                        gx += gx_kernel[a][b] * img[x][y];
                        gy += gy_kernel[a][b] * img[x][y];
                    }
                    b++;
                }
                a++;
            }
            #pragma omp critical
            {
                Gx[i][j] = gx;
                Gy[i][j] = gy;
                G[i][j] = sqrt( (Gx[i][j]*Gx[i][j]) + (Gy[i][j]*Gy[i][j]));
                theta[i][j] = atan2(Gy[i][j], Gx[i][j]);
                gx = gy = 0;
                
            }
        }
    }
    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by Sobel Operator : " << time_taken << setprecision(20);
    cout << " sec " << endl;
    for(int i=0;i<theta.size();i++){
        G.push_back(theta[i]);
    }
    return G;
}
extern "C"{
    vector<vector<double> > Apply_SobelOperator(vector<vector<double> > image){
        return SobelOperator(image);
    }
}
// http://www.adeveloperdiary.com/data-science/computer-vision/how-to-implement-sobel-edge-detection-using-python-from-scratch/
// https://www.projectrhea.org/rhea/index.php/An_Implementation_of_Sobel_Edge_Detection
#include<iostream>
#include<omp.h>
#include<vector>
using namespace std;

vector< vector< vector<double> > > blur(vector<vector<vector<double> > > img){
    vector< vector< vector<double> > >  blurred = img;
    int r = img.size();
    int c = img[0].size();
    int ch = img[0][0].size();
    #pragma omp parallel for
    for(int i=0;i < img.size(); i++){
        #pragma omp parallel for
        for(int j=0;j<img[i].size();j++){
            int channel = 0;
            #pragma omp parallel for reduction(+:channel)
            for(int k=0;k<img[i][j].size();k++){
                // upper row
                if(i-1 >= 0 && j-1 >=0){
                    channel += img[i-1][j-1][k];
                }
                if(i-1 >= 0){
                    channel += img[i-1][j][k];
                }
                if(i-1 >= 0 && j+1 < c){
                    channel += img[i-1][j+1][k];
                }

                // middle row
                if(j-1 >= 0){
                    channel += img[i][j-1][k];
                }
                if(j+1 < c){
                    channel += img[i][j+1][k];
                }
                channel += img[i][j][k];

                // lower row
                if(i+1 < r && j-1 >=0){
                    channel += img[i+1][j-1][k];
                }
                if(i+1 < r){
                    channel += img[i+1][j][k];
                }
                if(i+1 < r && j+1 < c){
                    channel += img[i+1][j+1][k];
                }
                #pragma omp critical
                {
                    blurred[i][j][k] = channel/ch/ch;
                    channel = 0;
                }
            }
        }
    }
    return blurred;
}
extern "C"{
    vector< vector< vector<double> > >  blur_image(vector< vector< vector<double> > >  image){
        return blur(image);
    }
}
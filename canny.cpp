#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
typedef vector<double> vec;
typedef vector<vector<double> > vec2d;
typedef vector<vector<vector<double> > > vec3d;

vec2d NonMaximumSuppression(vec2d img, vec2d D){
    int M = img.size();
    int N = img[0].size();
    vec2d Z(M, vec(N)); // Defaults to zero initial value Z = np.zeros((M,N), dtype=np.int32)
    vec2d angle(M, vec(N));
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            angle[i][j] = D[i][j] * 180.0 / M_PI;
            if(angle[i][j] < 0){
                angle[i][j] += 180;
            }
        }
    }

    
    for(int i=1;i<M-1;i++)
        for(int j=1;j<N-1;j++){
            try{
                int q = 255;
                int r = 255;

                //angle 0
                if( (angle[i][j] >= 0 && angle[i][j] < 22.5) || (angle[i][j] >= 157.5 && angle[i][j] <= 180) ){
                    q = img[i][j+1];
                    r = img[i][j-1];
                }
                else if(angle[i][j] >= 22.5 && angle[i][j] < 67.5){ //angle 45
                    q = img[i+1][j-1];
                    r = img[i-1][j+1];
                }
                else if(angle[i][j] >= 67.5 && angle[i][j] < 112.5){ //angle 90
                    q = img[i+1][j];
                    r = img[i-1][j];
                }
                else if(angle[i][j] >= 112.5 && angle[i][j] < 157.5){ //angle 135
                    q = img[i-1][j-1];
                    r = img[i+1][j+1];
                }

                if(img[i][j] >= q && img[i][j] >= r){
                    Z[i][j] = img[i][j];
                }
                else{
                    Z[i][j] = 0;
                }
            }
            catch(...){
                continue;
            }
        }
    return Z;
}
extern "C"{
    vector<vector<double> > Apply_NonMaximumSuppression(vec2d image, vec2d D){
        return NonMaximumSuppression(image, D);
    }
}





// https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;
typedef vector<double> vec;
typedef vector<vector<double> > vec2d;
typedef vector<vector<vector<double> > > vec3d;

vector<vector<double> > SobelOperator(vector<vector<double> > img){
    int radius = 1;
    vector<vector<double> > G = img;
    
    int gx_kernel[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} };
    int gy_kernel[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };

    vector<vector<double> > Gx = img;
    vector<vector<double> > Gy = img;
    
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
                gx = gy = 0;
            }
        }
    }
    return G;
}
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
int main(){
    vec2d img({  
        {110, 121, 212, 233} ,
        {44, 215, 166, 187} ,
        {89, 119, 103, 111}
    });
    for(int i=0;i<img.size();i++){
        for(int j=0;j<img[i].size();j++){
            cout << img[i][j] << "\t";
        }
        cout << endl;
    }

    auto D = SobelOperator(img);
    auto Z = NonMaximumSuppression(img, D);

    for(int i=0;i<Z.size();i++){
        for(int j=0;j<Z[i].size();j++){
            cout << Z[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}





// https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
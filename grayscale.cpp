#include<iostream>
#include<vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<double> > grayscale(vector<vector<vector<double> > > img){
    time_t start, end;
    vector<double> vect(img[0].size(), 0);
    vector<vector<double> > gray(img.size(), vect);
    time(&start);
    #pragma omp parallel for
    for(int i=0;i < img.size(); i++){
        #pragma omp parallel for
        for(int j=0;j<img[i].size();j++){
            gray[i][j] = 0.299*img[i][j][0] + 0.587*img[i][j][1] + 0.114*img[i][j][2];
        }
    }
    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by Grayscale : " << time_taken << setprecision(20);
    cout << " sec " << endl;
    return gray;
}
extern "C"{
    vector<vector<double> > to_grayscale(vector<vector<vector<double> > > image){
        return grayscale(image);
    }
}
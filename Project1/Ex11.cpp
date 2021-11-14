#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;


double SNR(const Mat &Img1, const Mat &Img2){
    Mat s1;
    absdiff(Img1, Img2, s1);
    s1.convertTo(s1, CV_32F);
    s1 = s1.mul(s1);

    Scalar s = sum(s1);
    double sse = s.val[0] + s.val[1] + s.val[2];

    if(sse <= 1e-10){
        return 0;
    }
    double mse = sse / (double)(Img1.channels() * Img1.total());
    double snr = 10*log10((255*255)/mse);
    return snr;
}

int main(int argc, char* argv[]){
    Mat img1 = imread(argv[1]);
    Mat img2 = imread(argv[2]);
    double snr = SNR(img1,img2);
    printf("SNR betwen %s and %s is %0.5f", argv[1], argv[2], snr);
    return 0;
}
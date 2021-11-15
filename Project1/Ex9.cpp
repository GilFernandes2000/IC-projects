#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <assert.h>

using namespace cv;
using namespace std;

// redução implementada
inline uchar reduceVal(const uchar val){
    if(val > 64){
        return val/2;
    }
    if(val < 128){
        return val/3;
    }
    return 255;   
}

// reduz o numero de bits de cada pixel
void reduceBits(Mat& img){
    uchar* pixel = img.data;
    for(int i = 0; i < img.rows; i++){
        for (int j = 0; j < img.cols; j++){
            const int pi = i*img.cols*3 + j*3;
            pixel[pi + 0] = reduceVal(pixel[pi + 0]);
            pixel[pi + 1] = reduceVal(pixel[pi + 1]);
            pixel[pi + 2] = reduceVal(pixel[pi + 2]);
        }
    }
}

int main(int argc, char* argv[]) {
    assert(argc == 2);
    Mat img = imread(argv[1]);
    
    if(!img.data){
        printf("No image data \n");
        return -1;
    }
    namedWindow("Before Image", WINDOW_AUTOSIZE);
    imshow("Before Image", img);

    reduceBits(img);
    namedWindow("After Image", WINDOW_AUTOSIZE);
    imshow("After Image", img);
    waitKey(0);
    return 0;
}
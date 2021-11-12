#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("imagens-PPM/baboon.ppm");
    
    if(!img.data){
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", img);
    waitKey(0);
    return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <assert.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    assert(argc == 2);
    Mat img = imread(argv[1]);
    
    if(!img.data){
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", img);
    imwrite("Copy_of_" + argv[1],  img);
    waitKey(0);
    return 0;
}
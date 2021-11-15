#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <assert.h>

using namespace cv;
using namespace std;


// reduz o numero de bits de cada pixel
void reduceBits(Mat& img){
    int nl = img.rows;                    // number of lines
    int nc = img.cols * img.channels(); // number of elements per line
    int div = 128;
    for (int j = 0; j < nl; j++)
    {
        uchar* data = img.ptr<uchar>(j);
        for (int i = 0; i < nc; i++)
        {
            data[i] = data[i] / div * div + div / 2;
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
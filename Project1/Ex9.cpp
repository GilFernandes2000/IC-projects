#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <assert.h>
#include <cstdio>

using namespace cv;
using namespace std;


// reduz o numero de bits de cada pixel
void reduceBits(Mat& img, int div){
    int nl = img.rows;                    // number of lines
    int nc = img.cols * img.channels(); // number of elements per line
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
    assert(argc == 3);
    Mat img = imread(argv[1]);
    string s2 = argv[2];
    int div;
    if(sscanf(s2.c_str(),"%d",&div) != 1){
        return EXIT_FAILURE;
    }
    if(!img.data){
        printf("No image data \n");
        return -1;
    }
    namedWindow("Before Image", WINDOW_AUTOSIZE);
    imshow("Before Image", img);

    reduceBits(img, div);
    namedWindow("After Image", WINDOW_AUTOSIZE);
    imshow("After Image", img);
    waitKey(0);
    return 0;
}
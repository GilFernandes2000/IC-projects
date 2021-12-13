#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "../include/BitStream.h"
#include "../include/Golomb.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    Mat img = imread("imagens-PPM/airplane.ppm");
    imwrite("airplane.jpg", img);
    Mat imgJPG = imread("airplane.jpg");
    for(int r = 0; r < imgJPG.rows; r++){
        for(int c = 0; c < imgJPG.cols; c++){
            Vec3b bgrPixel = imgJPG.at<Vec3b>(r,c);
            cout << bgrPixel[0] << endl;
        }
    }
    return EXIT_SUCCESS;
}
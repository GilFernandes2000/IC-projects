#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImagePredictor.h"
#include <iostream>
#include <assert.h>
#include <fstream>
#include <string.h>
#include <math.h>
//#include "..\include\BitStream.h"
#include "..\include\Golomb.h"

using namespace std;
using namespace cv;



ImagePredictor::ImagePredictor(Mat& img){
    this->img = img;
}

int ImagePredictor::getRows(){
    return this->imgRead.rows();
}

int ImagePredictor::getCols(){
    return this->imgRead.cols();
}

// Linear predictor
Vec3b ImagePredictor::LinearPre(int mode, Vec3b Px, Vec3b Pa, Vec3b Pb, Vec3b Pc){

//            __|______|______|__
//              |      |      |
//              |  Pc  |  Pb  |
//            __|______|______|__
//              |      |      |
//              |  Pa  |  Px  |
//            __|______|______|__
//              |      |      |                          

    Vec3b result;

    // R = Px - Pa
    if (mode == 1){
        result[0] = Px[0] - Pa[0];
        result[1] = Px[1] - Pa[1];
        result[2] = Px[2] - Pa[2];
    }

    // R = Px - Pb
    if (mode == 2){
        result[0] = Px[0] - Pb[0];
        result[1] = Px[1] - Pb[1];
        result[2] = Px[2] - Pb[2];
    }
    
    // R = Px - Pc
    if (mode == 3){
        result[0] = Px[0] - Pc[0];
        result[1] = Px[1] - Pc[1];
        result[2] = Px[2] - Pc[2];
    }

    // R = Px - (Pa + Pb - Pc)
    if (mode == 4){
        result[0] = Px[0] - (Pa[0] + Pb[0] - Pc[0]);
        result[1] = Px[1] - (Pa[1] + Pb[1] - Pc[1]);
        result[2] = Px[2] - (Pa[2] + Pb[2] - Pc[2]);
    }
    
    // R = Px - (Pa + (Pb - Pc)/2)
    if (mode == 5){
        result[0] = Px[0] - (Pa[0] + (Pb[0] - Pc[0])/2);
        result[1] = Px[1] - (Pa[1] + (Pb[1] - Pc[1])/2);
        result[2] = Px[2] - (Pa[2] + (Pb[2] - Pc[2])/2);
    }

    // R = Px - (Pb + (Pa - Pc)/2)
    if (mode == 6){
        result[0] = Px[0] - (Pb[0] + (Pa[0] - Pc[0])/2);
        result[1] = Px[1] - (Pb[1] + (Pa[1] - Pc[1])/2);
        result[2] = Px[2] - (Pb[2] + (Pa[2] - Pc[2])/2);
    }

    // R = Px - ((Pa + Pb)/2)
    if (mode == 7){
        result[0] = Px[0] - ((Pa[0] + Pb[0])/2);
        result[1] = Px[1] - ((Pa[1] + Pb[1])/2);
        result[2] = Px[2] - ((Pa[2] + Pb[2])/2);
    }

    return result;
}

// Non Linear Predictor
Vec3b ImagePredictor::NonLinearPre(Vec3b Px, Vec3b Pa, Vec3b Pb, Vec3b Pc){
    Vec3b result;
    if(Pc[0] >= max(Pa[0], Pb[0])){
        result[0] = Px[0] - min(Pa[0], Pb[0]);
    }

    else if(Pc[0] <= min(Pa[0], Pb[0])){
        result[0] = Px[0] - max(Pa[0], Pb[0]);
    }

    else{
        result[0] = Px[0] - (Pa[0] + Pb[0] - Pc[0]);
    }

    if(Pc[1] >= max(Pa[1], Pb[1])){
        result[1] = min(Pa[1], Pb[1]);
    }

    else if(Pc[1] <= min(Pa[1], Pb[1])){
        result[1] = max(Pa[1], Pb[1]);
    }

    else{
        result[1] = Px[1] - (Pa[1] + Pb[1] - Pc[1]);
    }

    if(Pc[2] >= max(Pa[2], Pb[2])){
        result[2] = min(Pa[2], Pb[2]);
    }

    else if(Pc[2] <= min(Pa[2], Pb[2])){
        result[2] = max(Pa[2], Pb[2]);
    }

    else{
        result[2] = Px[2] - (Pa[2] + Pb[2] - Pc[2]);
    }
    return result;
}

// processamento de cada pixel
// se a coluna ou a linha for de valor negativo o RGB do pixel fica a 0
Vec3b ImagePredictor::pixelHand(int c, int r){
    Vec3b pixel;
    if (r < 0){
        pixel[0] = 0;
        pixel[1] = 0;
        pixel[2] = 0;
    }

    else if (c < 0){
        pixel[0] = 0;
        pixel[1] = 0;
        pixel[2] = 0;
    }

    else{
        pixel = this->imgRead.at<Vec3b>(r,c);
    }
    return pixel;
}

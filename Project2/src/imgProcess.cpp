#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <string.h>
#include <math.h>
//#include "..\include\BitStream.h"
#include "..\include\Golomb.h"

using namespace std;
using namespace cv;


string imgEncoder(int i, int m){
    Golomb g(m);
    string encoded = g.encoding(i);
    return encoded;
}

// Linear predictor
Vec3b LinearPre(int mode, Vec3b Px, Vec3b Pa, Vec3b Pb, Vec3b Pc){
    Vec3b result;

    if (mode == 1){
        result[0] = Px[0] - Pa[0];
        result[1] = Px[1] - Pa[1];
        result[2] = Px[2] - Pa[2];
    }

    if (mode == 2){
        result[0] = Px[0] - Pb[0];
        result[1] = Px[1] - Pb[1];
        result[2] = Px[2] - Pb[2];
    }

    if (mode == 3){
        result[0] = Px[0] - Pc[0];
        result[1] = Px[1] - Pc[1];
        result[2] = Px[2] - Pc[2];
    }

    if (mode == 4){
        result[0] = Px[0] - (Pa[0] + Pb[0] - Pc[0]);
        result[1] = Px[1] - (Pa[1] + Pb[1] - Pc[1]);
        result[2] = Px[2] - (Pa[2] + Pb[2] - Pc[2]);
    }

    if (mode == 5){
        result[0] = Px[0] - (Pa[0] + (Pb[0] - Pc[0])/2);
        result[1] = Px[1] - (Pa[1] + (Pb[1] - Pc[1])/2);
        result[2] = Px[2] - (Pa[2] + (Pb[2] - Pc[2])/2);
    }

    if (mode == 6){
        result[0] = Px[0] - (Pb[0] + (Pa[0] - Pc[0])/2);
        result[1] = Px[1] - (Pb[1] + (Pa[1] - Pc[1])/2);
        result[2] = Px[2] - (Pb[2] + (Pa[2] - Pc[2])/2);
    }

    if (mode == 7){
        result[0] = Px[0] - ((Pa[0] + Pb[0])/2);
        result[1] = Px[1] - ((Pa[1] + Pb[1])/2);
        result[2] = Px[2] - ((Pa[2] + Pb[2])/2);
    }

    return result;
}

// Non Linear Predictor
Vec3b NonLinearPre(Vec3b Px, Vec3b Pa, Vec3b Pb, Vec3b Pc){
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

// lossless encoding
void Lossless (Vec3b Pixel){
    ofstream ofs("golomb.txt");
    int mean = (Pixel[0] + Pixel[1] + Pixel[2])/3;
    int m = (int)((-1)/(log2((mean)/(mean + 1.0))));
    ofs << imgEncoder(Pixel[0], m);
    ofs << imgEncoder(Pixel[1], m);         // usa o codificador de Golomb
    ofs << imgEncoder(Pixel[2], m);         // codifica o RGB separado em cada pixel
}

// lossy encoding
void Lossy (Vec3b Pixel, int M){
    
}

Vec3b pixelHand (Mat& img, int c, int r){
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
        pixel = img.at<Vec3b>(r,c);
    }
    return pixel;
}

int main(int argc, char* argv[]){
    assert(argc == 2);
    string s = (string)(argv[1]);
    //Mat img = imread("../../Project2/imagens-PPM/airplane.ppm");
    //imwrite("airplane.jpg", img);
    //size_t pos = s.find('.');
    Mat imgJPG = imread(argv[1]);
    ofstream ofs("golomb.txt");
    int width = imgJPG.rows;            // dimensoes do ficheiro
    int height = imgJPG.cols;
    
    //string format = s.substr(pos, s.length() - 1);  // formato do ficheiro

    //ofs << format << endl;
    int count = 0;
    cout << width << endl;
    cout << height << endl;

    for(int r = 0; r < imgJPG.rows; r++){
        for(int c = 0; c < imgJPG.cols; c++){

            Vec3b pixelX = pixelHand(imgJPG, c, r);     // pixeis separados
            Vec3b pixelA = pixelHand(imgJPG, c-1, r);     // pixeis separados
            Vec3b pixelB = pixelHand(imgJPG, c, r-1);     // pixeis separados
            Vec3b pixelC = pixelHand(imgJPG, c-1, r-1);     // pixeis separados
            
            //cout << pixelX << endl;

            Vec3b R = LinearPre(4, pixelX, pixelA, pixelB, pixelC);
            
            int mean = (R[0] + R[1] + R[2])/3;
            int m = (int)((-1)/(log2((mean)/(mean + 1.0))));
            cout << imgEncoder(R[0], m);
            cout << imgEncoder(R[1], m);         // usa o codificador de Golomb
            cout << imgEncoder(R[2], m);         // codifica o RGB separado em cada pixel 
            count++;    
            cout << c << endl;
            cout << r << endl;         
        }
    }
    cout << count;
    return EXIT_SUCCESS;
}
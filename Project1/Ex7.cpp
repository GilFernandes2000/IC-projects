#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>

using namespace std;
using namespace cv;

int main(){
    string img = "newImg.png";
    Mat src = imread(img, IMREAD_GRAYSCALE);
    if(src.empty()){
        return EXIT_FAILURE;
    }

    // só há 256 valores de cinzento (0-255)
    int tamHist = 256;

    float tam[] = {0, 256};
    const float* distHist[] = {tam};

    // criar um histograma a partir do opencv
    Mat gray_hist;
    bool uniform = true, accumulate = false;

    calcHist(&src, 1, 0, Mat(), gray_hist, 1, &tamHist, distHist, uniform, accumulate);
    
    // cria a interface para mostrar o histograma
    int histHeight = 400;
    int hisWidth = 512;

    int bin_w = cvRound((double) 512/tamHist);
    Mat histImage (histHeight, hisWidth, CV_8UC3, Scalar(0,0,0));

    // normaliza o histograma
    normalize(gray_hist, gray_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // colocar os valores do histograma na interface
    for(int i = 1; i < tamHist; i++){
        line(histImage, Point(bin_w*(i-1), 400 - cvRound(gray_hist.at<float>(i-1))), Point(bin_w*(i), histHeight - cvRound(gray_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
    }

    //mostrar o histograma
    imshow("Gray Histogram of " + img, histImage);
    waitKey(0);
    return EXIT_SUCCESS;
}
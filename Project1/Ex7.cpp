#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <assert.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    assert(argc == 2);
    string img = argv[1];
    Mat src = imread(img, IMREAD_GRAYSCALE);
    Mat rgb = imread(img, IMREAD_COLOR);
    if(src.empty()){
        return EXIT_FAILURE;
    }

    // só há 256 valores para cor(0-255)
    int tamHist = 256;
    vector<Mat> rgb_plan;
    split(rgb, rgb_plan);

    float tam[] = {0, 256};
    const float* distHist[] = {tam};

    // criar um histograma a partir do opencv
    Mat gray_hist, b_hist, g_hist, r_hist;
    bool uniform = true, accumulate = false;

    calcHist(&src, 1, 0, Mat(), gray_hist, 1, &tamHist, distHist, uniform, accumulate);
    calcHist(&rgb_plan[0], 1, 0, Mat(), b_hist, 1, &tamHist, distHist, uniform, accumulate);
    calcHist(&rgb_plan[1], 1, 0, Mat(), g_hist, 1, &tamHist, distHist, uniform, accumulate);
    calcHist(&rgb_plan[2], 1, 0, Mat(), r_hist, 1, &tamHist, distHist, uniform, accumulate);
    
    // cria a interface para mostrar o histograma
    int histHeight = 400;
    int histWidth = 512;

    int bin_w = cvRound((double) 512/tamHist);
    Mat histImage (histHeight, histWidth, CV_8UC3, Scalar(0,0,0));
    Mat histRGB (histHeight, histWidth, CV_8UC3, Scalar(0,0,0));

    // normaliza o histograma
    normalize(gray_hist, gray_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(b_hist, b_hist, 0, histRGB.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histRGB.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histRGB.rows, NORM_MINMAX, -1, Mat());
    
    // colocar os valores do histograma na interface
    for(int i = 1; i < tamHist; i++){
        line(histImage, Point(bin_w*(i-1), 400 - cvRound(gray_hist.at<float>(i-1))), Point(bin_w*(i), histHeight - cvRound(gray_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
        line(histRGB, Point(bin_w*(i-1), 400 - cvRound(b_hist.at<float>(i-1))), Point(bin_w*(i), histHeight - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
        line(histRGB, Point(bin_w*(i-1), 400 - cvRound(g_hist.at<float>(i-1))), Point(bin_w*(i), histHeight - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
        line(histRGB, Point(bin_w*(i-1), 400 - cvRound(r_hist.at<float>(i-1))), Point(bin_w*(i), histHeight - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
    }

    //mostrar o histograma
    imshow("Gray Histogram of " + img, histImage);
    imshow("RGB Histogram of " + img, histRGB);
    waitKey(0);
    return EXIT_SUCCESS;
}
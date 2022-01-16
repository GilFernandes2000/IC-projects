
#ifndef PROJECT2_IMAGEPREDICTOR_H
#define PROJECT2_IMAGEPREDICTOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<string.h>

using namespace std;
using namespace cv;

/**
 * @brief 
 * 
 */
class ImagePredictor{
public:
    /**
     *
     * @param img image to encode
     */
    ImagePredictor(Mat img);
    ImagePredictor(const ImagePredictor &ip);

    /**
     * @brief given 4 pixels and the mode calculation the pixel linear prediction of Px
     *  
     * 
     * @param mode linear predictor has 7 modes
     * @param Px pixel in position X
     * @param Pa pixel in position a
     * @param Pb pixel in position b
     * @param Pc pixel in position c
     * 
     * @return Vec3b pixel result
     */

    Vec3b LinearPre(int mode, Vec3b Px, Vec3b Pa, Vec3b Pb, Vec3b Pc);

    /**
     * @brief given 4 pixels, calculates the non-linear prediction of PX
     * 
     * @param Px pixel in position X
     * @param Pa pixel in position a
     * @param Pb pixel in position b
     * @param Pc pixel in position c
     * 
     * @return Vec3b pixel result
     */
    Vec3b NonLinearPre(Vec3b Px, Vec3b Pa, Vec3b Pb, Vec3b Pc);

    /**
     * @brief creates a pixel given a collum and a row
     * @if pixel is out of bounds it is give the value of 0
     * 
     * @param c pixel collum
     * @param r pixel row
     * 
     * @return Vec3b 
     */
    Vec3b pixelHand(int c, int r);

    /**
     * @brief Get the number of rows in the image
     * 
     * @return number of rowns 
     */
    int getRows();

    /**
     * @brief Get the number of collums in the image
     * 
     * @return number of collums
     */
    int getCols();

private:
    Mat img;
};

#endif //PROJECT2_IMAGEPREDICTOR_H
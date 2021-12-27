#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImagePredictor.h"
#include "ImageEncoder.h"
#include <iostream>
#include <assert.h>
#include <fstream>
#include <string.h>
#include <math.h>
//#include "..\include\BitStream.h"
#include "..\include\Golomb.h"
using namespace std;

int getM(Vec3b Pixel){
    int mean = (Pixel[0] + Pixel[1] + Pixel[2])/3;
    int m = (int)((-1)/(log2((mean)/(mean + 1.0))));
}

// usa o algoritmo de Golomb para codificar o umero dado
string imgEncoder(int i, int m){
    Golomb g(m);                        // cria o Golomb e da-lhe o melhor valor de M obtido pela formula
    string encoded = g.encoding(i);     // codifica os valores dados
    return encoded;                     // devolve uma string em codigo Golomb (0001101)
}

// converte de RGB para YUV
void RGB_2_YUV(Vec3b p){
    p[0] = 0.299*p[2] + 0.587*p[1] + 0.114*p[0];
    p[1] = 0.492*(p[1]-p[0]);
    p[2] = 0.877*(p[2]-p[0]);
}

// usado em lossy encoding (compressão com perdas)
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

// image encoder
int ImageEncoder::encode(string img, string fileOut, string encodFormat, string predictor, int mode=1, int quant=1){
    
    ofstream ofs(fileOut);

    // garantir que não há valores impossiveis
    assert(encodFormat == 'lossy' || encodFormat == 'lossless', 'Only lossy or lossless allowed');
    assert(predictor == 'linear' || predictor == 'nonLinear', 'Only linear or nonLinear allowed');
    assert(mode >= 1 && mode <= 7, 'Mode only has 1-7');

    Mat imgRead = imread(img);
    if(encodFormat == 'lossy'){
        reduceBits(imgRead, quant);
    }

    ImagePredictor imgPre(imgRead);
    int rows = imgPre.getRows();
    int cols = imgPre.getCols();

    Vec3b R;

    Vec3b pixelX;
    Vec3b pixelA;
    Vec3b pixelB;
    Vec3b pixelC;

    for(int r = 0; r < cols; r++){
        for(int c = 0; c < rows; c++){
                pixelX = imgPre.pixelHand(c, r);           // pixeis separados
                pixelA = imgPre.pixelHand(c-1, r);         // pixeis separados
                pixelB = imgPre.pixelHand(c, r-1);         // pixeis separados
                pixelC = imgPre.pixelHand(c-1, r-1);       // pixeis separados

                RGB_2_YUV(pixelX);
                RGB_2_YUV(pixelA);
                RGB_2_YUV(pixelB);
                RGB_2_YUV(pixelC);

                int M = getM(R);

                if(predictor == 'linear'){
                    R = imgPre.LinearPre(mode, pixelX, pixelA, pixelB, pixelC);
                }

                if(predictor == 'nonLinear'){
                    R = imgPre.NonLinearPre(pixelX, pixelA, pixelB, pixelC);
                }
            if(encodFormat == 'lossless'){
                ofs << imgEncoder(R[0], m);
                ofs << imgEncoder(R[1], m);         // usa o codificador de Golomb
                ofs << imgEncoder(R[2], m); 
            }

            if(encodFormat == 'lossy'){               
                Vec3b residual = pixelX - R;

                ofs << imgEncoder(R[0], m);
                ofs << imgEncoder(R[1], m);         // usa o codificador de Golomb
                ofs << imgEncoder(R[2], m);
            }
        }
    }
    ofs.close();
    return 0;
}

// void Lossy(Vec3b Pixel, Vec3b resto, int shift, int quant){
//     Vec3b residual = Pixel - resto;
//     resto[0] = resto[0] >> shift;
//     resto[1] = resto[1] >> shift;
//     resto[2] = resto[2] >> shift;

//     resto[0] = resto[0] << shift;
//     resto[1] = resto[1] << shift;
//     resto[2] = resto[2] << shift;

//     int mean = (resto[0] + resto[1] + resto[2])/3;
//     int m = (int)((-1)/(log2((mean)/(mean + 1))));

//     ofs << imgEncoder(resto[0], m);
//     ofs << imgEncoder(resto[1], m);
//     ofs << imgEncoder(resto[2], m);
// }
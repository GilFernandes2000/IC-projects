#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <assert.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    assert(argc == 2);
    Mat img = imread(argv[1]); // carregar o ficheiro
    
    if(!img.data){ // verificar se um ficheiro foi carregado
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", img); // mostrar o ficheiro 
    imwrite("Copy_of_" + argv[2],  img); // guarda o ficheiro
    waitKey(0); // necessario para a janela com a imagem nao fechar instantaneamente
    return 0;
}
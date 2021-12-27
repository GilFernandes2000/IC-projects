#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

#include "AudioEncoder.h"
#include "..\include\BitStream.h"
#include "..\include\GolombSgd.h"
#include "..\include\Golomb.h"
#include "ImageEncoder.h"


int main(int argc, char *argv[]) {
    if (argc <=1 ){
        printf("Needs to suply arguments!\n");
    }
    std::string function = argv[1];

    if( function == "audio")
    {
        if(argc < 5) {
            printf("ERROR: invalid number of arguments!\n");
        }
        std::string command = argv[2];

        if(command=="encode") {
            // hard coded cause whne reading path from argv segfaults
            std::string finpath = argv[3];// "../../wav-files/sample01.wav";
            std::string foutpath = argv[4];// "../sample01.ewav";

            AudioEncoder::encode(finpath, foutpath);
            return 0;
        }

        else if (command == "decode") {
            std::string finpath = argv[3];// "../wav-files/sample01.wav";
            std::string foutpath = argv[4];// "../sample01.cwav";

            AudioEncoder::decode(finpath, foutpath);
            return 0;
        }

        else if(command == "both") {
            std::string finpath = argv[3];// "../../wav-files/sample01.wav";
            std::string midpath = "../middle.cwav";
            std::string foutpath = argv[4];// "../sample01.wav";

            AudioEncoder::encode(finpath, midpath);
            AudioEncoder::decode(midpath, foutpath);

            return 0;
        }

        return 3; //command not available
    }

    else if (function == "image") {
        if(argc < 7){
            printf("ERROR: invalid number of arguments!\n");
        }
        std::string command = argv[2];

        if(command == "encode"){
            std::string img = argv[3];
            std::string fileOut = argv[4];
            std::string encodFormat = argv[5];
            std::string predictor = argv[6];
            std::int mod = 1;
            std::int Qt = 1;

            if(argc == 8){
                if(predictor == "linear"){
                    mode = argv[7];
                }
                if(encodFormat == "lossy"){
                    quant = argv[7];
                }
                if(predictor == "linear" && encodFormat == "lossy"){
                    printf("ERROR: invalid number of arguments!\n");
                }
            }
            if(argc == 9){
                std::int mode = argv[7];
                std::int quant = argv[8];
            }
            ImageEncoder::encode(img, fileOut, encodFormat, predictor, mode, quant);

            return 0;
        }
        return 1; // not imlpemented
    }

    else if(function == "test") {
        std::string uut = argv[2];
        if(uut == "golombsgd") {
            testgolombsgd();
            return 0;
        } else if(uut == "bitstream") {
            test_bitstream_write();
            return 0;
        }
    }
    else
    {
        printf("function is not supprted!\n");
        return 2;
    }

    return 1;
}
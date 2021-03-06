#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

#include "AudioEncoder.h"
#include "ImageEncoder.h"
#include "TestBitStream.h"
#include "TestGolombSgd.h"
#include "Golomb.h"


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
            AudioCodec::enc_options OPT;
            OPT.quantization_factor = 10;

            AudioCodec::encode(finpath, foutpath, OPT);
            return 0;
        }

        else if (command == "decode") {
            std::string finpath = argv[3];// "../wav-files/sample01.wav";
            std::string foutpath = argv[4];// "../sample01.cwav";

            AudioCodec::enc_options OPT;
            OPT.quantization_factor = 10;

            AudioCodec::decode(finpath, foutpath);
            return 0;
        }

        else if(command == "both") {
            std::string finpath = argv[3];// "../../wav-files/sample01.wav";
            std::string midpath = "../middle.cwav";
            std::string foutpath = argv[4];// "../sample01.wav";

            AudioCodec::encode(finpath, midpath);
            AudioCodec::decode(midpath, foutpath);

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
            int mode = 1;
            int shift = 0;

            if(argc == 8){
                if(predictor == "linear"){
                    mode = atoi(argv[7]);
                }
                if(encodFormat == "lossy"){
                    shift = atoi(argv[7]);
                }
                if(predictor == "linear" && encodFormat == "lossy"){
                    printf("ERROR: invalid number of arguments!\n");
                }
            }
            if(argc == 9){
                int mode = atoi(argv[7]);
                int shift = atoi(argv[8]);
            }
            ImageEncoder::encode(img, fileOut, encodFormat, predictor, mode, shift);

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
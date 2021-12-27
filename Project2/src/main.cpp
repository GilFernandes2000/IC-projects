#include <iostream>
#include <string>

#include "AudioEncoder.h"
#include "TestBitStream.h"
#include "TestGolombSgd.h"


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
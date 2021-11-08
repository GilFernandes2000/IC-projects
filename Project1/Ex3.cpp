#include "AudioFile.h"
#include <iostream>
#include <cmath>

using namespace std;


int main(int argc, char *argv[]){
    if(argc == 2){
        AudioFile<float> audio;
        bool loaded = audio.load(argv[0]);

        assert(loaded);

        audio.save(argv[1], AudioFileFormat::Wave);
        return 0;
    }
    cout << "Need two arguments" << endl;
    return 0;
}

// compilar com -lsndfile
// g++ audio.cpp -o audio -lsndfile
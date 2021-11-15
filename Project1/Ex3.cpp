#include "AudioFile.h"
#include <iostream>
#include <cmath>
#include <assert.h>

using namespace std;


int main(int argc, char *argv[]){
    assert(argc == 3);
    if(argc == 2){
        AudioFile<float> audio;
        bool loaded = audio.load(argv[1]);

        assert(loaded);

        audio.save(argv[2], AudioFileFormat::Wave);
        return 0;
    }
    cout << "Need two arguments" << endl;
    return 0;
}

// compilar com -lsndfile
// g++ audio.cpp -o audio -lsndfile
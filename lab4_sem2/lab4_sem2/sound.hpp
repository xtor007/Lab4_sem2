//
//  sound.hpp
//  lab4_sem2
//
//  Created by Берлинский Ярослав Владленович on 19.04.2021.
//

#ifndef sound_hpp
#define sound_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef struct{
    int32_t chunkId;
    int32_t chunkSize;
                       
                       
    int32_t format;
} RIFFHEADER;

typedef struct{
    int32_t subchunk1Id;
    int32_t subchunk1Size;
    int16_t audioFormat;
    int16_t numChannels;
    int32_t sampleRate;
    int32_t byteRate;
    int16_t blockAlign;
    int16_t bitsPerSample;
} SUBCHUNK1;

typedef struct{
    int32_t subchunk2Id;
    int32_t subchunk2Size;
    //int8_t[] data;
} SUBCHUNK2;

class waveReader{
private:
    friend class sound;
    FILE *audiofile;
    waveReader(string path){
        audiofile = fopen(path.c_str(), "rb");
        cout<<"Your path is: "<<path<<endl;
        if (!audiofile) {
            cout<<"We cannot open it!\n";
            exit(1);
        }
    }
    RIFFHEADER getHeader();

};



class sound{
private:
public:
    // fields
    friend class reader;
    RIFFHEADER header;
    SUBCHUNK1 info;
    SUBCHUNK2 dataInfo;
};



#endif /* sound_hpp */

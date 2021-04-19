//
//  sound.cpp
//  lab4_sem2
//
//  Created by Берлинский Ярослав Владленович on 19.04.2021.
//

#include "sound.hpp"

waveReader::waveReader(){
        string path;
        cout<<"Enter a path to your file: \n";
        getline(cin, path);
        audiofile = fopen(path.c_str(), "rb");
        cout<<"Your path is: "<<path<<endl;
        if (!audiofile) {
            cout<<"We cannot open it!\n";
            exit(1);
        }
}

RIFFHEADER waveReader::getHeader(){
    RIFFHEADER riffHead;
    fread(&riffHead, sizeof(riffHead), 1, audiofile);
    if (riffHead.chunkId != 1179011410) {   // decimal FOURCC-code of "RIFF"-note in .wav
        cout<<"The file format doesn't match.\n";
        exit(9);
    }
    if (riffHead.format != 1163280727){     // decimal WAVE-identifier in .wav
        cout<<"The file audioformat doesn't match.\n";
        exit(9);
    };
    return riffHead;
}

SUBCHUNK1 waveReader::getFMTdescription(){
    SUBCHUNK1 formatDescription;
    fread(&formatDescription, sizeof(formatDescription), 1, audiofile);
    return formatDescription;
}

SUBCHUNK2 waveReader::getData(){
    SUBCHUNK2 data;
    fread(&data, sizeof(data), 1, audiofile);
    return data;
}

template <typename int_size> int_size waveReader::*getSampleSet(int16_t bitsPerSample, int numberOfSamples){
    int_size *result = new int_size[numberOfSamples];
        for (int i = 0; i < numberOfSamples; i++) {
            fread(&result, bitsPerSample/8, 1, audiofile);
            cout<<i<<endl;
        }
    return result;
}

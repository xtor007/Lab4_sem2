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


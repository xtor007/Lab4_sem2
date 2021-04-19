//
//  sound.cpp
//  lab4_sem2
//
//  Created by Берлинский Ярослав Владленович on 19.04.2021.
//

#include "sound.hpp"

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

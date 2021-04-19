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
    waveReader();
    RIFFHEADER getHeader();
    SUBCHUNK1 getFMTdescription();
    SUBCHUNK2 getData();
};




class sound{
private:
public:
    // fields
    friend class reader;
    int sizeOfSample;
    int numberOfSamples;
    RIFFHEADER riffHeader;
    SUBCHUNK1 fmtChunk;
    SUBCHUNK2 dataChunk;
    
    void read(){
        waveReader readResult;
        riffHeader = readResult.getHeader();
        fmtChunk = readResult.getFMTdescription();
        dataChunk = readResult.getData();
        sizeOfSample = fmtChunk.byteRate/(fmtChunk.sampleRate*fmtChunk.numChannels);
        numberOfSamples = dataChunk.subchunk2Size / sizeOfSample;
    }
    void print(){
        cout<<"\n\t===Reading RIFF-header===\n";
        cout<<"ChunkID: "<<riffHeader.chunkId<<endl;
        cout<<"Size of file(chunkSize+chunkSize&chunkID statements sizes): "<<riffHeader.chunkSize + sizeof(riffHeader.chunkSize) + sizeof(riffHeader.chunkId)<<endl;
        cout<<"FormatID: "<<riffHeader.format<<endl;
        cout<<"\n\t===Reading FMT-subchunk===\n";
        cout<<"SubChunk1ID: "<<fmtChunk.subchunk1Id<<endl;
        cout<<"SubChunk1 Size: "<<fmtChunk.subchunk1Size<<endl;
        cout<<"Byterate: "<<fmtChunk.byteRate<<endl;
        cout<<"SizeOfSample: "<<sizeOfSample<<endl;
        cout<<"NumberOfSamples: "<<numberOfSamples<<endl;
    }
};



#endif /* sound_hpp */

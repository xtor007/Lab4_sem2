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

// class for reading a track
class waveReader{
    friend class sound;  // being incapsulated, only class sound has permissoin to work with waveReader class
    FILE *audiofile;
    waveReader();
    RIFFHEADER getHeader();  // getting RIFF-statements
    SUBCHUNK1 getFMTdescription(); // getting FMT-descriptions
    SUBCHUNK2 getData(); // getting data
    template <typename int_size> int_size *getSampleSet(int16_t bitsPerSample, int numberOfSamples); // getting samples
};



// class for track
class sound{
public:
    // === Fields ===
    int sizeOfSample;  // size of 1 sample (commonly, 1 or 2 bytes)
    int numberOfSamples; // number of samples in a track
    int8_t* sampleSet8b; // for case if bytes per 1 sample is equal to 8 -> array of samples
    int16_t* sampleSet16b;  // for 16 -> array of samples
    RIFFHEADER riffHeader; // riff is put here
    SUBCHUNK1 fmtChunk; // fmt is here
    SUBCHUNK2 dataChunk; // data is here
    
    //=== METHODS ===
    
    // reading audiofile
    void read(){
        waveReader readResult;
        riffHeader = readResult.getHeader();
        fmtChunk = readResult.getFMTdescription();
        dataChunk = readResult.getData();
        sizeOfSample = fmtChunk.byteRate/(fmtChunk.sampleRate*fmtChunk.numChannels);
        numberOfSamples = dataChunk.subchunk2Size / sizeOfSample;
        if (fmtChunk.bitsPerSample == 8)
                sampleSet8b = readResult.getSampleSet<int8_t>(fmtChunk.bitsPerSample, numberOfSamples);
        if (fmtChunk.bitsPerSample == 16)
                sampleSet16b = readResult.getSampleSet<int16_t>(fmtChunk.bitsPerSample, numberOfSamples);
    }
    // here, you can insert <void print()> method
};





//    void print(){
//        cout<<"\n\t===Reading RIFF-header===\n";
//        cout<<"ChunkID: "<<riffHeader.chunkId<<endl;
//        cout<<"Size of file(chunkSize+chunkSize&chunkID statements sizes): "<<riffHeader.chunkSize + sizeof(riffHeader.chunkSize) + sizeof(riffHeader.chunkId)<<endl;
//        cout<<"FormatID: "<<riffHeader.format<<endl;
//        cout<<"\n\t===Reading FMT-subchunk===\n";
//        cout<<"SubChunk1ID: "<<fmtChunk.subchunk1Id<<endl;
//        cout<<"SubChunk1 Size: "<<fmtChunk.subchunk1Size<<endl;
//        cout<<"Byterate: "<<fmtChunk.byteRate<<endl;
//        cout<<"SizeOfSample: "<<sizeOfSample<<endl;
//        cout<<"NumberOfSamples: "<<numberOfSamples<<endl;
//    }


#endif /* sound_hpp */

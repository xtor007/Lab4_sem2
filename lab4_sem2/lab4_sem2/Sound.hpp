
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
class WaveReader{
    friend class Sound;  // being incapsulated, only class sound has permissoin to work with waveReader class
    
    FILE *audiofile; // out binary file
    string directoryPath;
    
    WaveReader(string path);
    
    RIFFHEADER getHeader();  // getting RIFF-statements
    SUBCHUNK1 getFMTdescription(); // getting FMT-descriptions
    SUBCHUNK2 getData(); // getting data
    template <typename int_size> vector<int_size> getSampleSet(int16_t bitsPerSample, int numberOfSamples); // getting samples
};



// class for track

class Sound{
    // === Fields ===
    friend class Interface;
    string path;
    int sizeOfSample;  // size of 1 sample (commonly, 1 or 2 bytes)
    int numberOfSamples; // number of samples in a track
    vector<int8_t> sampleSet8b; // for case if bytes per 1 sample is equal to 8 -> array of samples
    vector<int16_t> sampleSet16b;  // for 16 -> array of samples
    RIFFHEADER riffHeader; // riff is put here
    SUBCHUNK1 fmtChunk; // fmt is here
    SUBCHUNK2 dataChunk; // data is here
    
    //=== METHODS ===

    template <typename intn_t>
    void writeFile(vector<intn_t> sampleSetN_t, string pathFolder, string outFile);
    
    // reading audiofile
    void read(string pathFolder, string inFile);
    // here, you can insert <void print()> method
    void write(string pathFolder, string outFileName);
    
    // rewriting external vector with samples(after linear interpolation)
    template <typename intn_t>
    void swapVectors(vector<intn_t> vector){
        switch (sizeOfSample) {
            case 1: // size of each sample is equal to 1(8 bit)
                sampleSet8b.resize(vector.size()); // setting vector size equal to vector with samples
                for (int i = 0; i < vector.size(); i++) {
                    sampleSet8b[i] = vector[i]; // rewriting
                }
                break;
            case 2: // 16 bit -> analogically
                sampleSet16b.resize(vector.size());
                for (int i = 0; i < vector.size(); i++) {
                    sampleSet16b[i] = vector[i];
                }
                break;
            default:
                cout<<"Error! Size of sample is: "<<sizeOfSample<<endl;
                exit(1);
                break;
        }
    }

};



#endif /* sound_hpp */


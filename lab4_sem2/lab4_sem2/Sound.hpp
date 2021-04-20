
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
    
    //Interface message;
    FILE *audiofile;
    string directoryPath;
    
    WaveReader(string path);
    
    RIFFHEADER getHeader();  // getting RIFF-statements
    SUBCHUNK1 getFMTdescription(); // getting FMT-descriptions
    SUBCHUNK2 getData(); // getting data
    template <typename int_size> vector<int_size> getSampleSet(int16_t bitsPerSample, int numberOfSamples); // getting samples
};



// class for track
class Sound{
public:
    // === Fields ===
    string path;
    int sizeOfSample;  // size of 1 sample (commonly, 1 or 2 bytes)
    int numberOfSamples; // number of samples in a track
    vector<int8_t> sampleSet8b; // for case if bytes per 1 sample is equal to 8 -> array of samples
    vector<int16_t> sampleSet16b;  // for 16 -> array of samples
    RIFFHEADER riffHeader; // riff is put here
    SUBCHUNK1 fmtChunk; // fmt is here
    SUBCHUNK2 dataChunk; // data is here
    
    //=== METHODS ===
    
    // reading audiofile
    void read(string pathFolder, string inFile);
    // here, you can insert <void print()> method
    void write();
    
    template <typename intn_t>
    void writeFile(vector<intn_t> sampleSetN_t, string pathFolder, string outFile);
};



#endif /* sound_hpp */

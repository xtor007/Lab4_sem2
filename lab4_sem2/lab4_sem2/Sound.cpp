#include "Sound.hpp"

WaveReader::WaveReader(string path){
        audiofile = fopen((path).c_str(), "rb");
        if (!audiofile) {
            cout<<"File cannot be opened"<<endl;
            exit(1);
        }
}

RIFFHEADER WaveReader::getHeader(){
    RIFFHEADER riffHead;
    fread(&riffHead, sizeof(riffHead), 1, audiofile);
    if (riffHead.chunkId != 1179011410) {   // decimal FOURCC-code of "RIFF"-note in .wav (little-endian)
        cout<<"The file format doesn't match.\n";
        exit(9);
    }
    if (riffHead.format != 1163280727){     // decimal WAVE-identifier in .wav (little-endian)
        cout<<"The file audioformat doesn't match.\n";
        exit(9);
    };
    return riffHead;
}

SUBCHUNK1 WaveReader::getFMTdescription(){
    SUBCHUNK1 formatDescription;
    fread(&formatDescription, sizeof(formatDescription), 1, audiofile);
    if (formatDescription.subchunk1Id != 544501094) {  // 544501094 is int32_t for little-endian 0x666d7420("fmt"-letters)
        cout<<"Wrong subchunk ID\n"<<endl;
        exit(9);
    }
    return formatDescription;
}

// reading subchunk2
SUBCHUNK2 WaveReader::getData(){
    SUBCHUNK2 data;
    fread(&data, sizeof(data), 1, audiofile);
    return data;
}

template <typename int_size> vector<int_size> WaveReader::getSampleSet(int16_t bitsPerSample, int numberOfSamples){
    vector <int_size> result;
    result.resize(numberOfSamples);
    for (int i = 0; i < numberOfSamples; i++) {
        fread(&result[i], bitsPerSample/8, 1, audiofile);
    }
    return result;
}

void Sound::read(string pathFolder, string inFile){
    path = pathFolder + inFile;
    WaveReader readResult(path);
    riffHeader = readResult.getHeader();  // getting RIFF(ChunkID) + ChunkSize + Format
    fmtChunk = readResult.getFMTdescription();  // getting information with subchunk1
    dataChunk = readResult.getData();           // getting information with subchunk2
    sizeOfSample = fmtChunk.bitsPerSample/8;   // size of sample may equal in this case to 8 or 16 bits
    numberOfSamples = dataChunk.subchunk2Size / sizeOfSample;
    if (fmtChunk.bitsPerSample == 8)
            // getting 8-bit samples
            sampleSet8b = readResult.getSampleSet<int8_t>(fmtChunk.bitsPerSample, numberOfSamples);
    if (fmtChunk.bitsPerSample == 16)
            // 16-bit
            sampleSet16b = readResult.getSampleSet<int16_t>(fmtChunk.bitsPerSample, numberOfSamples);
}

void Sound::write(string pathFolder, string outFileName){
    if (sizeOfSample == 1) writeFile(sampleSet8b, pathFolder, outFileName);  // for 8 bit
    else if (sizeOfSample == 2) writeFile(sampleSet16b,pathFolder, outFileName);  // for 16 bit
    else cout<<"We cannot write samples into file because the size of each sample is wrong\n";
}

template <typename intn_t>
void Sound::writeFile(vector<intn_t> sampleSetN_t, string pathFolder, string outFileName){
    FILE* outFile;
    path = pathFolder + outFileName;    // path to our folder + name of the file == full path
    outFile = fopen(path.c_str(), "wb");
    dataChunk.subchunk2Size = (sampleSetN_t.size() * sampleSetN_t.size() * fmtChunk.bitsPerSample/8);
    riffHeader.chunkSize = 4 + (8 + dataChunk.subchunk2Size) + (8 + fmtChunk.subchunk1Size);
    fwrite(&riffHeader, sizeof(riffHeader), 1, outFile);  // putting riff into .wav
    fwrite(&fmtChunk, sizeof(fmtChunk), 1, outFile);      // putting fmt into .wav
    fwrite(&dataChunk, sizeof(dataChunk), 1, outFile);    // putting data info into .wav
    for (int i = 0; i < sampleSetN_t.size(); i++) {
        fwrite(&sampleSetN_t[i], sizeOfSample, 1, outFile);  // writing each sample to a newly created .wav
    }
    fclose(outFile);
}

#include "Sound.hpp"

WaveReader::WaveReader(string path){
//        cout<<"Enter a path to your file: \n";
//        getline(cin, directoryPath);
//        cout<<"Enter a name of the file to read: \n";
//        getline(cin, input);
//        cout<<"Enter a name of the file to write: \n";
//        getline(cin, output);
        audiofile = fopen((path).c_str(), "rb");
//        cout<<"Your path is: "<<(directoryPath+input)<<endl;
        if (!audiofile) {
            //message.printMessage("We cannot open it!\n");
            cout<<"Dont"<<endl;
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
    riffHeader = readResult.getHeader();
    fmtChunk = readResult.getFMTdescription();
    dataChunk = readResult.getData();
    sizeOfSample = 2;
    numberOfSamples = dataChunk.subchunk2Size / sizeOfSample;
    if (fmtChunk.bitsPerSample == 8)
            sampleSet8b = readResult.getSampleSet<int8_t>(fmtChunk.bitsPerSample, numberOfSamples);
    if (fmtChunk.bitsPerSample == 16)
            sampleSet16b = readResult.getSampleSet<int16_t>(fmtChunk.bitsPerSample, numberOfSamples);
}

void Sound::write(string pathFolder, string outFileName){
    if (sizeOfSample == 1) writeFile(sampleSet8b, pathFolder, outFileName);
    else if (sizeOfSample == 2) writeFile(sampleSet16b,pathFolder, outFileName);
    else cout<<"We cannot write samples into file because the size of each sample is wrong\n";
}

template <typename intn_t>
void Sound::writeFile(vector<intn_t> sampleSetN_t, string pathFolder, string outFileName){
    FILE* outFile;
    path = pathFolder + outFileName;
    outFile = fopen(path.c_str(), "wb");
    cout<<path<<endl;
    dataChunk.subchunk2Size = (sampleSetN_t.size() * sampleSetN_t.size() * fmtChunk.bitsPerSample/8);
    riffHeader.chunkSize = 4 + (8 + dataChunk.subchunk2Size) + (8 + fmtChunk.subchunk1Size);
    fwrite(&riffHeader, sizeof(riffHeader), 1, outFile);
    fwrite(&fmtChunk, sizeof(fmtChunk), 1, outFile);
    fwrite(&dataChunk, sizeof(dataChunk), 1, outFile);
    for (int i = 0; i < sampleSetN_t.size(); i++) {
        fwrite(&sampleSetN_t[i], sizeOfSample, 1, outFile);
    }
    fclose(outFile);
}
// /Users/yaroslav/Desktop/file/


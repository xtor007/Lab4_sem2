//
//  Interface.cpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 20.04.2021.
//

#include "Interface.hpp"


void Interface::run() {
    string path; string inFile; string outFile;
    cout << "Enter folder address:" << endl;
    getline(cin,path);
    cout << "Enter an input file name: ";
    getline(cin,inFile);
    cout << "Enter an output file name: ";
    getline(cin,outFile);
    Sound sound;
    sound.read(path, inFile);
    Samples<int8_t> samples8(sound.sampleSet8b, 8);
    Samples<int16_t> samples16(sound.sampleSet16b, 16);
    float scale;
    cout << "Enter scale: ";
    cin >> scale;
    int repetitions;
    cout << "Enter number of repetitions: ";
    cin >> repetitions;
    if (sound.sizeOfSample == 1) { //если 8байтовый размер
        samples8.changeSampl(scale);
        samples8.enlargeSampl(repetitions);
        sound.swapVectors(samples8.getSample());
    } else if(sound.sizeOfSample == 2) { //если 16байтовый размер
        samples16.changeSampl(scale);
        samples16.enlargeSampl(repetitions);
        sound.swapVectors(samples16.getSample());
    } else {
        cout << "error" << endl;
        exit(1);
    }
    sound.write(path, outFile);
}

void Interface::printMessage(string message) {
    cout << message;
}

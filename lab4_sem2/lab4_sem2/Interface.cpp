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
    cout << "Enter scale:";
    cin >> scale;
    if (sound.sizeOfSample == 1) {
        samples8.changeSampl(scale);
        sound.writeFile<int8_t>(samples8.getSample(),path,outFile);
    } else if(sound.sizeOfSample == 2) {
        samples16.changeSampl(scale);
        sound.writeFile<int16_t>(samples16.getSample(),path,outFile);
    } else {
        cout << "error" << endl;
        exit(1);
    }
}

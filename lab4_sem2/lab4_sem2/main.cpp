//
//  main.cpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 12.04.2021.
//

#include <iostream>
#include <vector>
#include "sample.hpp"
#include "sample.cpp"
#include "sound.hpp"
using namespace std;

int main(){
    sound sound;
    sound.read();
    sound.print();
    Samples<int16_t> samples(sound.sampleSet16b, 16);
    cout << sound.sampleSet16b[0] << " " << sound.sampleSet16b[1] << endl;
    cout<<"1: "<<sound.numberOfSamples<<endl;
    samples.changeSampl(1);
    
//    cout << sound.sampleSet16b[0] << " " << sound.sampleSet16b[1] << sound.sampleSet16b[2] << " " << sound.sampleSet16b[3] << endl;
    //sound.numberOfSamples = sound.numberOfSamples*2 - 1;
    sound.writeFile(samples.getSample());
}

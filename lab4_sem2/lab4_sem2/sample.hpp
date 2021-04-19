//
//  sample.hpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 12.04.2021.
//

#ifndef semple_hpp
#define semple_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Samples {
    vector<int8_t> sampleSet8;
    vector<int16_t> sampleSet16;
    int16_t typeOfSampl;
public:

    Samples (T newSampleSet, int numberOfSampls, int16_t bitsPerSample);
    Samples () {}
    
    void getSample(T fileSamlesSet);
    
    void changeSampl(float n);
};


#endif /* semple_hpp */

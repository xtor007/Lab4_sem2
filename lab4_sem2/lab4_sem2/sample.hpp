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
    vector<T> sampleSet8;
    vector<T> sampleSet16;
    int16_t typeOfSampl;
public:

    Samples (vector<T> newSampleSet, int16_t bitsPerSample);
    
    vector<T> getSample();
    
    void changeSampl(float n);
};


#endif /* semple_hpp */

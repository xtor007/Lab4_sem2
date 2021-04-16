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


class Samples {
    vector<int8_t> sampleSet;
public:
    Samples (int8_t *newSampleSet, int numberOfSampls);
    void getSample(int8_t *fileSamlesSet);
    void changeSampl(float n);
};


#endif /* semple_hpp */

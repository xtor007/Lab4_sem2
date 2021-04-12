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
    Samples (vector<int8_t> newSampleSet) {sampleSet = newSampleSet;}
    vector<int8_t> getSample();
    void changeSampl(float n);
};


#endif /* semple_hpp */

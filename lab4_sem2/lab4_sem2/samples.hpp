//
//  sempls.hpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 12.04.2021.
//

#ifndef sempls_hpp
#define sempls_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;


class Samples {
    vector<int8_t> sampleSet;
public:
    Samples (vector<int8_t> newSampleSet);
    vector<int8_t> getSample();
    void changeSampl(int n);
};


#endif /* sempls_hpp */

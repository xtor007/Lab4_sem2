//
//  sample.cpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 12.04.2021.
//

#include "sample.hpp"

vector<int8_t> Samples::getSample() {
    return sampleSet;
}

void Samples::changeSampl(float n) {
    n = 1/n;
    float posSimpl = 0;
    vector<int8_t> newSampleSet;
    int endOfSegment = sampleSet.size()-1;
    while (posSimpl <= endOfSegment) {
        if (posSimpl - int(posSimpl) == 0) {
            newSampleSet.push_back(sampleSet[int(posSimpl)]);
        } else {
            newSampleSet.push_back(sampleSet[int(posSimpl)] + (posSimpl-int(posSimpl))*(sampleSet[int(posSimpl)+1]-sampleSet[int(posSimpl)]));
        }
        posSimpl += n;
    }
    sampleSet = newSampleSet;
}

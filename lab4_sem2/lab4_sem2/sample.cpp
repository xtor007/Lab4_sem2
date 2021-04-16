//
//  sample.cpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 12.04.2021.
//

#include "sample.hpp"

void Samples::getSample(int8_t *fileSamlesSet) {
    for (int i=0; i<sampleSet.size(); i++) {
        fileSamlesSet[i] = sampleSet[i];
    }
}

Samples::Samples (int8_t *newSampleSet, int numberOfSampls) {
    for (int i=0; i<numberOfSampls; i++) {
        sampleSet.push_back(newSampleSet[i]);
    }
}

void Samples::changeSampl(float n) {
    n = 1/n;
    float posSimpl = 0;
    vector<int8_t> newSampleSet;
    int endOfSegment = int(sampleSet.size()-1);
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

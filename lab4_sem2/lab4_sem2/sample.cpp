//
//  sample.cpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 12.04.2021.
//

#include "sample.hpp"

template <typename T>
void Samples<T>::getSample(T fileSamlesSet) {
    if (typeOfSampl == 8) {
        for (int i=0; i<sampleSet8.size(); i++) {
            fileSamlesSet[i] = sampleSet8[i];
        }
    } else {
        for (int i=0; i<sampleSet16.size(); i++) {
            fileSamlesSet[i] = sampleSet16[i];
        }
    }
}

template <typename T>
Samples<T>::Samples (T newSampleSet, int numberOfSampls, int16_t bitsPerSample) {
    typeOfSampl = bitsPerSample;
    if (typeOfSampl == 8) {
        for (int i=0; i<numberOfSampls; i++) {
            sampleSet8.push_back(newSampleSet[i]);
        }
    } else {
        for (int i=0; i<numberOfSampls; i++) {
            sampleSet16.push_back(newSampleSet[i]);
        }
    }
}


template <typename T>
void Samples<T>::changeSampl(float n) {
    n = 1/n;
    float posSimpl = 0;
    vector<int8_t> newSampleSet8;
    vector<int16_t> newSampleSet16;
    if (typeOfSampl == 8) {
        int endOfSegment = int(sampleSet8.size()-1);
        while (posSimpl <= endOfSegment) {
            if (posSimpl - int(posSimpl) == 0) {
                newSampleSet8.push_back(sampleSet8[int(posSimpl)]);
            } else {
                newSampleSet8.push_back(sampleSet8[int(posSimpl)] + (posSimpl-int(posSimpl))*(sampleSet8[int(posSimpl)+1]-sampleSet8[int(posSimpl)]));
            }
            posSimpl += n;
        }
        sampleSet8 = newSampleSet8;
    } else {
        int endOfSegment = int(sampleSet16.size()-1);
        while (posSimpl <= endOfSegment) {
            if (posSimpl - int(posSimpl) == 0) {
                newSampleSet16.push_back(sampleSet16[int(posSimpl)]);
            } else {
                newSampleSet16.push_back(sampleSet16[int(posSimpl)] + (posSimpl-int(posSimpl))*(sampleSet16[int(posSimpl)+1]-sampleSet16[int(posSimpl)]));
            }
            posSimpl += n;
        }
        sampleSet16 = newSampleSet16;
    }
}

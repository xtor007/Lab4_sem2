
#include "sample.hpp"

template <typename T>
vector<T> Samples<T>::getSample() {
    if (typeOfSampl == 8) {
        return sampleSet8;
    } else {
        return sampleSet16;
    }
}

template <typename T>
Samples<T>::Samples (vector<T> newSampleSet, int16_t bitsPerSample) {
    typeOfSampl = bitsPerSample;
    if (typeOfSampl == 8) {
        sampleSet8.resize(newSampleSet.size());
        for (int i = 0; i < newSampleSet.size(); i++) {
            sampleSet8[i] = newSampleSet[i];
        }
    } else {
        sampleSet16.resize(newSampleSet.size());
        for (int i = 0; i < newSampleSet.size(); i++) {
            sampleSet16[i] = newSampleSet[i];
        }
    }
}


template <typename T>
void Samples<T>::changeSampl(float n) {
    n = 1/n; //что-бы увеличивало
    float posSimpl = 0;
    vector<T> newSampleSet;
    if (typeOfSampl == 8) {
        int endOfSegment = int(sampleSet8.size()-1);
        while (posSimpl <= endOfSegment) {
            if (posSimpl - int(posSimpl) == 0) {
                newSampleSet.push_back(sampleSet8[int(posSimpl)]); //если значение целое, то записываем его
            } else {
                newSampleSet.push_back(sampleSet8[int(posSimpl)] + (posSimpl-int(posSimpl))*(sampleSet8[int(posSimpl)+1]-sampleSet8[int(posSimpl)])); //формула для линейной интерполяции
            }
            posSimpl += n; //идем с шагом
        }
        sampleSet8 = newSampleSet;
    } else {
        int endOfSegment = int(sampleSet16.size()-1);
        while (posSimpl <= endOfSegment) {
            if (posSimpl - int(posSimpl) == 0) {
                newSampleSet.push_back(sampleSet16[int(posSimpl)]);
            } else {
                newSampleSet.push_back(sampleSet16[int(posSimpl)] + (posSimpl-int(posSimpl))*(sampleSet16[int(posSimpl)+1]-sampleSet16[int(posSimpl)]));
            }
            posSimpl += n;
        }
        sampleSet16 = newSampleSet;
    }
}


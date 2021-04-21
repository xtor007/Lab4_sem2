
#ifndef semple_hpp
#define semple_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Samples {
    friend class Interface;
    vector<T> sampleSet8;
    vector<T> sampleSet16;
    int16_t typeOfSampl; // 8 или 16
    
    Samples (vector<T> newSampleSet, int16_t bitsPerSample);
    
    vector<T> getSample(); //возвращает семплы
    
    void changeSampl(float n); //интерполяция
    
    void enlargeSampl(int n);
};


#endif /* semple_hpp */

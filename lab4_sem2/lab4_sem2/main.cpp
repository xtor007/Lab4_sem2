//
//  main.cpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 12.04.2021.
//

#include <iostream>
#include <vector>
#include "sample.hpp"
#include "sample.cpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    int8_t t1[4] = {1, 3, 2, 6};
    int16_t t2[4] = {1, 3, 2, 6};
    Samples<int8_t *> s1(t1, 4, 8);
    Samples<int16_t*> s2(t2, 4, 16);
    s1.changeSampl(2);
    s2.changeSampl(2);
    int8_t r1[9]; s1.getSample(r1);
    int16_t r2[9]; s2.getSample(r2);
    //s2.getSample(r2);
 
    return 0;
}

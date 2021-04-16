//
//  main.cpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 12.04.2021.
//

#include <iostream>
#include <vector>
#include "sample.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    int8_t k[3] = {'\x02','\x04','\x03'};
    Samples kk = Samples(k, 3);
    kk.changeSampl(2);
    int8_t kkk[5];
    kk.getSample(kkk);
    
    return 0;
}

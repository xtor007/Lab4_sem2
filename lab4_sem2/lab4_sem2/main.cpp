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
    vector<int8_t> k;
    k.push_back(2);
    k.push_back(3);
    k.push_back(4);
    k.push_back(4);
    Samples kk = Samples(k);
    kk.changeSampl(2);
    vector<int8_t> kkk = kk.getSample();
    
    return 0;
}

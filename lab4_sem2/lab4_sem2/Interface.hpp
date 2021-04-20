//
//  Interface.hpp
//  lab4_sem2
//
//  Created by Anatoliy Khramchenko on 20.04.2021.
//

#ifndef Interface_hpp
#define Interface_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "sample.hpp"
#include "sample.cpp"
#include "Sound.hpp"
using namespace std;

class Interface {
public:
    void run();
    void printMessage(string message);
};

#endif /* Interface_hpp */

//
//  PointEarthMoon.h
//  PointEarthMoon
//
//  Created by Seth on 01/21/2016
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef POINTEARTHMOON_H
#define POINTEARTHMOON_H

#include <iostream>

enum PointEarthMoon{
    PEM_NA = -1,
    PEM_Earth = 1,
    PEM_Moon = 2
};

static void printEarthMoon(PointEarthMoon pem) {
    if (pem == PEM_NA) {
        std::cout << "Point at N/A" << std::endl;
    } else if (pem == PEM_Earth) {
        std::cout << "Point at Earth" << std::endl;
    } else if (pem == PEM_Moon) {
        std::cout << "Point at Moon" << std::endl;
    } else {
        std::cerr << "Point is undefined value" << std::endl;
    }
}

#endif

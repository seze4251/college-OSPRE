//
//  PointEarthMoon.h
//  PointEarthMoon
//
//  Created by Seth on 01/21/2016
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef POINTEARTHMOON_H
#define POINTEARTHMOON_H

#include <stdio.h>

enum PointEarthMoon{
    PEM_NA = -1,
    PEM_Earth = 1,
    PEM_Moon = 2
};

static void printEarthMoon(PointEarthMoon pem, FILE* logFile) {
    fprintf(logFile, "Printing Point Earth Moon Enumeration:\n");
    if (pem == PEM_NA) {
        fprintf(logFile, "Point at N/A\n");
    } else if (pem == PEM_Earth) {
        fprintf(logFile, "Point at Earth\n");
    } else if (pem == PEM_Moon) {
        fprintf(logFile, "Point at Moon\n");
    } else {
        fprintf(logFile, "Point is undefined value\n");
        throw "Pointing at an undefined value (Not Part of ENUM)\n";
    }
}

#endif

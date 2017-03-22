//
//  ProcessErrorStructure.h
//  ProcessErrorStructure
//
//  Created by Seth on 02/11/2017.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef PROCESSERRORSTRUCTURE_H
#define PROCESSERRORSTRUCTURE_H

#include <iostream>

#include "ProcessError.h"
#include "ProcessID.h"

class ProcessErrorStructure {
public:
    ProcessErrorStructure() {}
    
    void print(FILE* logFile) {
        fprintf(logFile, "Printing Processed Error Structure\n");
        printProcessError(error, logFile);
        printProcessID(iden, logFile);
    }
    
    // Members
    ProcessID iden;
    ProcessError error;
    
};

#endif

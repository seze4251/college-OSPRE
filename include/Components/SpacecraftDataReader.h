//
//  SpacecraftDataReader
//  SpacecraftDataReader.h
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

// ToDO: Implement in future when OSPRE gets Camera Functionality

#ifndef SPACECRAFTDATAREADER_H
#define SPACECRAFTDATAREADER_H

#include <vector>
#include <string>

#include "External_DataMessage.h"

class SpacecraftDataReader {
public:
    SpacecraftDataReader(unsigned int applicationProcessID);
    
    void readDataFile(std::string);
    External_DataMessage* getNextDataMessage();
    
private:
    unsigned int applicationProcessID;
    std::vector<External_DataMessage> data;
    int messageNum;
};

#endif
